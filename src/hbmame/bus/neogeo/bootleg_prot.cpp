// license:BSD-3-Clause
// copyright-holders:S. Smith,David Haywood

#include "emu.h"
#include "bootleg_prot.h"
#include "screen.h"



extern const device_type NGBOOTLEG_PROT = device_creator<ngbootleg_prot_device>;


ngbootleg_prot_device::ngbootleg_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, NGBOOTLEG_PROT, "NeoGeo Protection (Bootleg)", tag, owner, clock, "ngbootleg_prot", __FILE__),
	kof2k3_overlay(0),
	m_mainrom(nullptr),
	m_fixedrom(nullptr),
	m_bankdev(nullptr)
{
}


void ngbootleg_prot_device::device_start()
{
	memset(m_cartridge_ram, 0x00, 0x2000);

	save_item(NAME(m_cartridge_ram));
}

void ngbootleg_prot_device::device_reset()
{
}



/***************************************************************************

    Neo-Geo hardware encryption and protection used on bootleg cartridges

    Many of the NeoGeo bootlegs use their own form of encryption and
    protection, presumably to make them harder for other bootleggers to
    copy.  This encryption often involves non-trivial scrambling of the
    program roms and the games are protected using an Altera chip which
    provides some kind of rom overlay, patching parts of the code.
    The graphics roms are usually scrambled in a different way to the
    official SNK cartridges too.

***************************************************************************/

#include "emu.h"
#include "includes/neogeo.h"


/* General Bootleg Functions - used by more than 1 game */


void ngbootleg_prot_device::neogeo_bootleg_cx_decrypt(uint8_t*sprrom, uint32_t sprrom_size)
{
	int i;
	int cx_size = sprrom_size;
	uint8_t *rom = sprrom;
	std::vector<uint8_t> buf( cx_size );

	memcpy( &buf[0], rom, cx_size );

	for( i = 0; i < cx_size / 0x40; i++ ){
		memcpy( &rom[ i * 0x40 ], &buf[ (i ^ 1) * 0x40 ], 0x40 );
	}
}


void ngbootleg_prot_device::neogeo_bootleg_sx_decrypt(uint8_t* fixed, uint32_t fixed_size, int value )
{
	int sx_size = fixed_size;
	uint8_t *rom = fixed;
	int i;

	if (value == 1)
	{
		std::vector<uint8_t> buf( sx_size );
		memcpy( &buf[0], rom, sx_size );

		for( i = 0; i < sx_size; i += 0x10 )
		{
			memcpy( &rom[ i ], &buf[ i + 8 ], 8 );
			memcpy( &rom[ i + 8 ], &buf[ i ], 8 );
		}
	}
	else if (value == 2)
	{
		for( i = 0; i < sx_size; i++ )
			rom[ i ] = BITSWAP8( rom[ i ], 7, 6, 0, 4, 3, 2, 1, 5 );
	}
}



/* The King of Fighters '97 Oroshi Plus 2003 (bootleg) */

void ngbootleg_prot_device::kof97oro_px_decode(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i;
	std::vector<uint16_t> tmp( 0x500000 );
	uint16_t *src = (uint16_t*)cpurom;

	for (i = 0; i < 0x500000/2; i++) {
		tmp[i] = src[i ^ 0x7ffef];
	}

	memcpy (src, &tmp[0], 0x500000);
}


/* The King of Fighters 10th Anniversary (The King of Fighters 2002 bootleg) */


/* this uses RAM based tiles for the text layer, however the implementation
  is incomplete, at the moment the S data is copied from the program rom on
  start-up instead */

void ngbootleg_prot_device::kof10thBankswitch(address_space &space, uint16_t nBank)
{
	uint32_t bank = 0x100000 + ((nBank & 7) << 20);
	if (bank >= 0x700000)
		bank = 0x100000;
	m_bankdev->neogeo_set_main_cpu_bank_address(bank);
}

READ16_MEMBER( ngbootleg_prot_device::kof10th_RAMB_r )
{
	return m_cartridge_ram[offset];
}

READ16_MEMBER(ngbootleg_prot_device::kof10th_RAM2_r)
{
//  printf("kof10th_RAM2_r\n");
	return m_cartridge_ram2[offset];
}

WRITE16_MEMBER( ngbootleg_prot_device::kof10th_custom_w )
{
	if (!m_cartridge_ram[0xFFE]) { // Write to RAM bank A
		//uint16_t *prom = (uint16_t*)m_mainrom;
		COMBINE_DATA(&m_cartridge_ram2[(0x00000/2) + (offset & 0xFFFF)]);
	} else { // Write S data on-the-fly
		m_fixedrom[offset] = BITSWAP8(data,7,6,0,4,3,2,1,5);
	}
}

WRITE16_MEMBER( ngbootleg_prot_device::kof10th_bankswitch_w )
{
	if (offset >= 0x5F000) {
		if (offset == 0x5FFF8) { // Standard bankswitch
			kof10thBankswitch(space, data);
		} else if (offset == 0x5FFFC && m_cartridge_ram[0xFFC] != data) { // Special bankswitch
			uint8_t *src = m_mainrom;
			memcpy (src + 0x10000,  src + ((data & 1) ? 0x810000 : 0x710000), 0xcffff);
		}
		COMBINE_DATA(&m_cartridge_ram[offset & 0xFFF]);
	}
}

void ngbootleg_prot_device::install_kof10th_protection (cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size, uint8_t* fixedrom, uint32_t fixedrom_size)
{
	m_mainrom = cpurom;
	m_fixedrom = fixedrom;
	m_bankdev = bankdev;

	maincpu->space(AS_PROGRAM).install_read_handler(0x0e0000, 0x0fffff, read16_delegate(FUNC(ngbootleg_prot_device::kof10th_RAM2_r),this));

	maincpu->space(AS_PROGRAM).install_read_handler(0x2fe000, 0x2fffff, read16_delegate(FUNC(ngbootleg_prot_device::kof10th_RAMB_r),this));
	maincpu->space(AS_PROGRAM).install_write_handler(0x200000, 0x23ffff, write16_delegate(FUNC(ngbootleg_prot_device::kof10th_custom_w),this));
	maincpu->space(AS_PROGRAM).install_write_handler(0x240000, 0x2fffff, write16_delegate(FUNC(ngbootleg_prot_device::kof10th_bankswitch_w),this));
	memcpy(m_cartridge_ram2, cpurom + 0xe0000, 0x20000);

	// HACK: only save this at device_start (not allowed later)
	if (machine().phase() <= MACHINE_PHASE_INIT)
		save_pointer(NAME(m_fixedrom), 0x40000);
}

void ngbootleg_prot_device::decrypt_kof10th(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i, j;
	std::vector<uint8_t> dst(0x900000);
	uint8_t *src = cpurom;

	memcpy(&dst[0x000000], src + 0x700000, 0x100000); // Correct (Verified in Uni-bios)
	memcpy(&dst[0x100000], src + 0x000000, 0x800000);

	for (i = 0; i < 0x900000; i++) {
		j = BITSWAP24(i,23,22,21,20,19,18,17,16,15,14,13,12,11,2,9,8,7,1,5,4,3,10,6,0);
		src[j] = dst[i];
	}

	// Altera protection chip patches these over P ROM
	((uint16_t*)src)[0x0124/2] = 0x000d; // Enables XOR for RAM moves, forces SoftDIPs, and USA region
	((uint16_t*)src)[0x0126/2] = 0xf7a8;

	((uint16_t*)src)[0x8bf4/2] = 0x4ef9; // Run code to change "S" data
	((uint16_t*)src)[0x8bf6/2] = 0x000d;
	((uint16_t*)src)[0x8bf8/2] = 0xf980;

}


/* The King of Fighters 10th Anniversary Extra Plus (The King of Fighters 2002 bootleg) */


void ngbootleg_prot_device::kf10thep_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	uint16_t *rom = (uint16_t*)cpurom;
	std::vector<uint16_t> buf(0x100000/2);

	memcpy(&buf[0x000000/2], &rom[0x060000/2], 0x20000);
	memcpy(&buf[0x020000/2], &rom[0x100000/2], 0x20000);
	memcpy(&buf[0x040000/2], &rom[0x0e0000/2], 0x20000);
	memcpy(&buf[0x060000/2], &rom[0x180000/2], 0x20000);
	memcpy(&buf[0x080000/2], &rom[0x020000/2], 0x20000);
	memcpy(&buf[0x0a0000/2], &rom[0x140000/2], 0x20000);
	memcpy(&buf[0x0c0000/2], &rom[0x0c0000/2], 0x20000);
	memcpy(&buf[0x0e0000/2], &rom[0x1a0000/2], 0x20000);
	memcpy(&buf[0x0002e0/2], &rom[0x0402e0/2], 0x6a);  // copy banked code to a new memory region
	memcpy(&buf[0x0f92bc/2], &rom[0x0492bc/2], 0xb9e); // copy banked code to a new memory region
	memcpy(rom, &buf[0], 0x100000);

	for (int i = 0xf92bc/2; i < 0xf9e58/2; i++)
	{
		if (rom[i+0] == 0x4eb9 && rom[i+1] == 0x0000) rom[i+1] = 0x000F; // correct JSR in moved code
		if (rom[i+0] == 0x4ef9 && rom[i+1] == 0x0000) rom[i+1] = 0x000F; // correct JMP in moved code
	}
	rom[0x00342/2] = 0x000f;

	memmove(&rom[0x100000/2], &rom[0x200000/2], 0x600000);
}


/* The King of Fighters 10th Anniversary 2005 Unique (The King of Fighters 2002 bootleg) */


void ngbootleg_prot_device::kf2k5uni_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i, j, ofst;
	uint8_t *src = cpurom;
	uint8_t dst[0x80];

	for (i = 0; i < 0x800000; i+=0x80)
	{
		for (j = 0; j < 0x80; j+=2)
		{
			ofst = BITSWAP8(j, 0, 3, 4, 5, 6, 1, 2, 7);
			memcpy(&dst[j], src + i + ofst, 2);
		}
		memcpy(src + i, &dst[0], 0x80);
	}

	memcpy(src, src + 0x600000, 0x100000); // Seems to be the same as kof10th
}

void ngbootleg_prot_device::kf2k5uni_sx_decrypt(uint8_t* fixedrom, uint32_t fixedrom_size)
{
	int i;
	uint8_t *srom = fixedrom;

	for (i = 0; i < 0x20000; i++)
		srom[i] = BITSWAP8(srom[i], 4, 5, 6, 7, 0, 1, 2, 3);
}

void ngbootleg_prot_device::kf2k5uni_mx_decrypt(uint8_t* audiorom, uint32_t audiorom_size)
{
	int i;
	uint8_t *mrom = audiorom;

	for (i = 0; i < 0x30000; i++)
		mrom[i] = BITSWAP8(mrom[i], 4, 5, 6, 7, 0, 1, 2, 3);
}

void ngbootleg_prot_device::decrypt_kf2k5uni(uint8_t* cpurom, uint32_t cpurom_size, uint8_t* audiorom, uint32_t audiorom_size, uint8_t* fixedrom, uint32_t fixedrom_size)
{
	kf2k5uni_px_decrypt(cpurom, cpurom_size);
	kf2k5uni_sx_decrypt(fixedrom, fixedrom_size);
	kf2k5uni_mx_decrypt(audiorom, audiorom_size);
}


/* The King of Fighters 2002 (bootleg) */


void ngbootleg_prot_device::kof2002b_gfx_decrypt(uint8_t *src, int size)
{
	int i, j;
	static const uint8_t t[ 8 ][ 6 ] =
	{
		{ 0, 8, 7, 6, 2, 1 },
		{ 1, 0, 8, 7, 6, 2 },
		{ 2, 1, 0, 8, 7, 6 },
		{ 6, 2, 1, 0, 8, 7 },
		{ 7, 6, 2, 1, 0, 8 },
		{ 0, 1, 2, 6, 7, 8 },
		{ 2, 1, 0, 6, 7, 8 },
		{ 8, 0, 7, 6, 2, 1 },
	};

	std::vector<uint8_t> dst( 0x10000 );

	for ( i = 0; i < size; i+=0x10000 )
	{
		memcpy( &dst[0], src+i, 0x10000 );

		for ( j = 0; j < 0x200; j++ )
		{
			int n = (j & 0x38) >> 3;
			int ofst = BITSWAP16(j, 15, 14, 13, 12, 11, 10, 9, t[n][0], t[n][1], t[n][2], 5, 4, 3, t[n][3], t[n][4], t[n][5]);
			memcpy( src+i+ofst*128, &dst[j*128], 128 );
		}
	}
}


/* The King of Fighters 2002 Magic Plus (bootleg) */


void ngbootleg_prot_device::kf2k2mp_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i,j;

	uint8_t *src = cpurom;
	uint8_t dst[0x80];

	memmove(src, src + 0x300000, 0x500000);

	for (i = 0; i < 0x800000; i+=0x80)
	{
		for (j = 0; j < 0x80 / 2; j++)
		{
			int ofst = BITSWAP8( j, 6, 7, 2, 3, 4, 5, 0, 1 );
			memcpy(dst + j * 2, src + i + ofst * 2, 2);
		}
		memcpy(src + i, dst, 0x80);
	}
}


/* The King of Fighters 2002 Magic Plus II (bootleg) */


void ngbootleg_prot_device::kf2k2mp2_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst(0x600000);

	memcpy (&dst[0x000000], &src[0x1C0000], 0x040000);
	memcpy (&dst[0x040000], &src[0x140000], 0x080000);
	memcpy (&dst[0x0C0000], &src[0x100000], 0x040000);
	memcpy (&dst[0x100000], &src[0x200000], 0x400000);
	memcpy (&src[0x000000], &dst[0x000000], 0x600000);
}


/* Crouching Tiger Hidden Dragon 2003 (bootleg of King of Fighters 2001) */


/* descrambling information from razoola */
void ngbootleg_prot_device::cthd2003_neogeo_gfx_address_fix_do(uint8_t* sprrom, uint32_t sprrom_size, int start, int end, int bit3shift, int bit2shift, int bit1shift, int bit0shift)
{
	int i,j;
	int tilesize=128;

	std::vector<uint8_t> rom(16*tilesize); // 16 tiles buffer
	uint8_t* realrom = sprrom + start*tilesize;

	for (i = 0; i < (end-start)/16; i++) {
		for (j = 0; j < 16; j++) {
			int offset = (((j&1)>>0)<<bit0shift)
					+(((j&2)>>1)<<bit1shift)
					+(((j&4)>>2)<<bit2shift)
					+(((j&8)>>3)<<bit3shift);

			memcpy(&rom[j*tilesize], realrom+offset*tilesize, tilesize);
		}
		memcpy(realrom,&rom[0],tilesize*16);
		realrom+=16*tilesize;
	}
}

void ngbootleg_prot_device::cthd2003_neogeo_gfx_address_fix(uint8_t* sprrom, uint32_t sprrom_size, int start, int end)
{
	cthd2003_neogeo_gfx_address_fix_do(sprrom, sprrom_size, start+512*0, end+512*0, 0,3,2,1);
	cthd2003_neogeo_gfx_address_fix_do(sprrom, sprrom_size, start+512*1, end+512*1, 1,0,3,2);
	cthd2003_neogeo_gfx_address_fix_do(sprrom, sprrom_size, start+512*2, end+512*2, 2,1,0,3);
	// skip 3 & 4
	cthd2003_neogeo_gfx_address_fix_do(sprrom, sprrom_size, start+512*5, end+512*5, 0,1,2,3);
	cthd2003_neogeo_gfx_address_fix_do(sprrom, sprrom_size, start+512*6, end+512*6, 0,1,2,3);
	cthd2003_neogeo_gfx_address_fix_do(sprrom, sprrom_size, start+512*7, end+512*7, 0,2,3,1);
}

void ngbootleg_prot_device::cthd2003_c(uint8_t* sprrom, uint32_t sprrom_size, int pow)
{
	int i;

	for (i=0; i<=192; i+=8)
		cthd2003_neogeo_gfx_address_fix(sprrom, sprrom_size, i*512,i*512+512);

	for (i=200; i<=392; i+=8)
		cthd2003_neogeo_gfx_address_fix(sprrom, sprrom_size, i*512,i*512+512);

	for (i=400; i<=592; i+=8)
		cthd2003_neogeo_gfx_address_fix(sprrom, sprrom_size, i*512,i*512+512);

	for (i=600; i<=792; i+=8)
		cthd2003_neogeo_gfx_address_fix(sprrom, sprrom_size, i*512,i*512+512);

	for (i=800; i<=992; i+=8)
		cthd2003_neogeo_gfx_address_fix(sprrom, sprrom_size, i*512,i*512+512);

	for (i=1000; i<=1016; i+=8)
		cthd2003_neogeo_gfx_address_fix(sprrom, sprrom_size, i*512,i*512+512);
}

void ngbootleg_prot_device::decrypt_cthd2003(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size, uint8_t* fixedrom, uint32_t fixedrom_size)
{
	uint8_t *romdata = fixedrom;
	std::vector<uint8_t> tmp(8*128*128);

	memcpy(&tmp[8*0*128], romdata+8*0*128, 8*32*128);
	memcpy(&tmp[8*32*128], romdata+8*64*128, 8*32*128);
	memcpy(&tmp[8*64*128], romdata+8*32*128, 8*32*128);
	memcpy(&tmp[8*96*128], romdata+8*96*128, 8*32*128);
	memcpy(romdata, &tmp[0], 8*128*128);

	romdata = audiorom+0x10000;
	memcpy(&tmp[8*0*128], romdata+8*0*128, 8*32*128);
	memcpy(&tmp[8*32*128], romdata+8*64*128, 8*32*128);
	memcpy(&tmp[8*64*128], romdata+8*32*128, 8*32*128);
	memcpy(&tmp[8*96*128], romdata+8*96*128, 8*32*128);
	memcpy(romdata, &tmp[0], 8*128*128);

	memcpy(romdata-0x10000,romdata,0x10000);

	cthd2003_c(sprrom, sprrom_size, 0);
}

WRITE16_MEMBER( ngbootleg_prot_device::cthd2003_bankswitch_w )
{
	int bankaddress;
	static const int cthd2003_banks[8] =
	{
		1,0,1,0,1,0,3,2,
	};
	if (offset == 0)
	{
		bankaddress = 0x100000 + cthd2003_banks[data&7]*0x100000;
		m_bankdev->neogeo_set_main_cpu_bank_address(bankaddress);
	}
}

void ngbootleg_prot_device::patch_cthd2003(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size)
{
	/* patches thanks to razoola */
	int i;
	uint16_t *mem16 = (uint16_t *)cpurom;

	/* special ROM banking handler */
	maincpu->space(AS_PROGRAM).install_write_handler(0x2ffff0, 0x2fffff, write16_delegate(FUNC(ngbootleg_prot_device::cthd2003_bankswitch_w),this));
	m_bankdev = bankdev;

	// theres still a problem on the character select screen but it seems to be related to cpu core timing issues,
	// overclocking the 68k prevents it.

	// fix garbage on s1 layer over everything
	mem16[0xf415a/2] = 0x4ef9;
	mem16[0xf415c/2] = 0x000f;
	mem16[0xf415e/2] = 0x4cf2;
	// Fix corruption in attract mode before title screen
	for (i=0x1ae290/2;i < 0x1ae8d0/2; i=i+1)
	{
		mem16[i] = 0x0000;
	}

	// Fix for title page
	for (i=0x1f8ef0/2;i < 0x1fa1f0/2; i=i+2)
	{
		mem16[i] -= 0x7000;
		mem16[i+1] -= 0x0010;
	}

	// Fix for green dots on title page
	for (i=0xac500/2;i < 0xac520/2; i=i+1)
	{
		mem16[i] = 0xFFFF;
	}
	// Fix for blanks as screen change level end clear
	mem16[0x991d0/2] = 0xdd03;
	mem16[0x99306/2] = 0xdd03;
	mem16[0x99354/2] = 0xdd03;
	mem16[0x9943e/2] = 0xdd03;
}


/* Crouching Tiger Hidden Dragon 2003 Super Plus (bootleg of King of Fighters 2001) */


void ngbootleg_prot_device::ct2k3sp_sx_decrypt( uint8_t* fixedrom, uint32_t fixedrom_size )
{
	int rom_size = fixedrom_size;
	uint8_t *rom = fixedrom;
	std::vector<uint8_t> buf( rom_size );
	int i;
	int ofst;

	memcpy( &buf[0], rom, rom_size );

	for( i = 0; i < rom_size; i++ ){
		ofst = BITSWAP24( (i & 0x1ffff), 23, 22, 21, 20, 19, 18, 17,  3,
											0,  1,  4,  2, 13, 14, 16, 15,
											5,  6, 11, 10,  9,  8,  7, 12 );

		ofst += (i >> 17) << 17;

		rom[ i ] = buf[ ofst ];
	}

	memcpy( &buf[0], rom, rom_size );

	memcpy( &rom[ 0x08000 ], &buf[ 0x10000 ], 0x8000 );
	memcpy( &rom[ 0x10000 ], &buf[ 0x08000 ], 0x8000 );
	memcpy( &rom[ 0x28000 ], &buf[ 0x30000 ], 0x8000 );
	memcpy( &rom[ 0x30000 ], &buf[ 0x28000 ], 0x8000 );
}

void ngbootleg_prot_device::decrypt_ct2k3sp(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size, uint8_t* fixedrom, uint32_t fixedrom_size)
{
	uint8_t *romdata = audiorom+0x10000;
	std::vector<uint8_t> tmp(8*128*128);
	memcpy(&tmp[8*0*128], romdata+8*0*128, 8*32*128);
	memcpy(&tmp[8*32*128], romdata+8*64*128, 8*32*128);
	memcpy(&tmp[8*64*128], romdata+8*32*128, 8*32*128);
	memcpy(&tmp[8*96*128], romdata+8*96*128, 8*32*128);
	memcpy(romdata, &tmp[0], 8*128*128);

	memcpy(romdata-0x10000,romdata,0x10000);
	ct2k3sp_sx_decrypt(fixedrom, fixedrom_size);
	cthd2003_c(sprrom,sprrom_size,0);
}


/* Crouching Tiger Hidden Dragon 2003 Super Plus alternate (bootleg of King of Fighters 2001) */


void ngbootleg_prot_device::decrypt_ct2k3sa(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size )
{
	uint8_t *romdata = audiorom+0x10000;
	std::vector<uint8_t> tmp(8*128*128);
	memcpy(&tmp[8*0*128], romdata+8*0*128, 8*32*128);
	memcpy(&tmp[8*32*128], romdata+8*64*128, 8*32*128);
	memcpy(&tmp[8*64*128], romdata+8*32*128, 8*32*128);
	memcpy(&tmp[8*96*128], romdata+8*96*128, 8*32*128);
	memcpy(romdata, &tmp[0], 8*128*128);

	memcpy(romdata-0x10000,romdata,0x10000);
	cthd2003_c(sprrom,sprrom_size, 0);
}

void ngbootleg_prot_device::patch_ct2k3sa(uint8_t* cpurom, uint32_t cpurom_size)
{
	/* patches thanks to razoola - same as for cthd2003*/
	int i;
	uint16_t *mem16 = (uint16_t *)cpurom;

	// theres still a problem on the character select screen but it seems to be related to cpu core timing issues,
	// overclocking the 68k prevents it.

	// fix garbage on s1 layer over everything
	mem16[0xf415a/2] = 0x4ef9;
	mem16[0xf415c/2] = 0x000f;
	mem16[0xf415e/2] = 0x4cf2;

	// Fix corruption in attract mode before title screen
	for (i=0x1ae290/2;i < 0x1ae8d0/2; i=i+1)
	{
		mem16[i] = 0x0000;
	}

	// Fix for title page
	for (i=0x1f8ef0/2;i < 0x1fa1f0/2; i=i+2)
	{
		mem16[i] -= 0x7000;
		mem16[i+1] -= 0x0010;
	}

	// Fix for green dots on title page
	for (i=0xac500/2;i < 0xac520/2; i=i+1)
	{
		mem16[i] = 0xFFFF;
	}
	// Fix for blanks as screen change level end clear
	mem16[0x991d0/2] = 0xdd03;
	mem16[0x99306/2] = 0xdd03;
	mem16[0x99354/2] = 0xdd03;
	mem16[0x9943e/2] = 0xdd03;
}


/* King of Fighters Special Edition 2004 (bootleg of King of Fighters 2002) */


void ngbootleg_prot_device::decrypt_kof2k4se_68k(uint8_t* cpurom, uint32_t cpurom_size)
{
	uint8_t *src = cpurom+0x100000;
	std::vector<uint8_t> dst(0x400000);
	int i;
	static const int sec[] = {0x300000,0x200000,0x100000,0x000000};
	memcpy(&dst[0],src,0x400000);

	for(i = 0; i < 4; ++i)
	{
		memcpy(src+i*0x100000,&dst[sec[i]],0x100000);
	}
}


/* Lansquenet 2004 (Shock Troopers - 2nd Squad bootleg) */


void ngbootleg_prot_device::lans2004_vx_decrypt(uint8_t* ymsndrom, uint32_t ymsndrom_size)
{
	int i;
	uint8_t *rom = ymsndrom;
	for (i = 0; i < 0xA00000; i++)
		rom[i] = BITSWAP8(rom[i], 0, 1, 5, 4, 3, 2, 6, 7);
}

void ngbootleg_prot_device::lans2004_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size)
{
	/* Descrambling P ROMs - Thanks to Razoola for the info */
	int i;
	uint8_t *src = cpurom;
	uint16_t *rom = (uint16_t*)cpurom;

	{
		static const int sec[] = { 0x3, 0x8, 0x7, 0xC, 0x1, 0xA, 0x6, 0xD };
		std::vector<uint8_t> dst(0x600000);

		for (i = 0; i < 8; i++)
			memcpy (&dst[i * 0x20000], src + sec[i] * 0x20000, 0x20000);

		memcpy (&dst[0x0BBB00], src + 0x045B00, 0x001710);
		memcpy (&dst[0x02FFF0], src + 0x1A92BE, 0x000010);
		memcpy (&dst[0x100000], src + 0x200000, 0x400000);
		memcpy (src, &dst[0], 0x600000);
	}

	for (i = 0xBBB00/2; i < 0xBE000/2; i++) {
		if ((((rom[i]&0xFFBF)==0x4EB9) || ((rom[i]&0xFFBF)==0x43B9)) && (rom[i+1]==0x0000)) {
			rom[i + 1] = 0x000B;
			rom[i + 2] += 0x6000;
		}
	}

	/* Patched by protection chip (Altera) ? */
	rom[0x2D15C/2] = 0x000B;
	rom[0x2D15E/2] = 0xBB00;
	rom[0x2D1E4/2] = 0x6002;
	rom[0x2EA7E/2] = 0x6002;
	rom[0xBBCD0/2] = 0x6002;
	rom[0xBBDF2/2] = 0x6002;
	rom[0xBBE42/2] = 0x6002;
}


/* Metal Slug 5 Plus (bootleg) */


READ16_MEMBER( ngbootleg_prot_device::mslug5_prot_r )
{
	logerror("PC %06x: access protected\n",space.device().safe_pc());
	return 0xa0;
}

WRITE16_MEMBER( ngbootleg_prot_device::ms5plus_bankswitch_w )
{
	int bankaddress;
	logerror("offset: %06x PC %06x: set banking %04x\n",offset,space.device().safe_pc(),data);
	if ((offset == 0)&&(data == 0xa0))
	{
		bankaddress=0xa0;
		m_bankdev->neogeo_set_main_cpu_bank_address(bankaddress);
		logerror("offset: %06x PC %06x: set banking %04x\n\n",offset,space.device().safe_pc(),bankaddress);
	}
	else if(offset == 2)
	{
		data=data>>4;
		//data=data&7;
		bankaddress=data*0x100000;
		m_bankdev->neogeo_set_main_cpu_bank_address(bankaddress);
		logerror("offset: %06x PC %06x: set banking %04x\n\n",offset,space.device().safe_pc(),bankaddress);
	}
}

void ngbootleg_prot_device::install_ms5plus_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev)
{
	// special ROM banking handler / additional protection
	maincpu->space(AS_PROGRAM).install_readwrite_handler(0x2ffff0, 0x2fffff,read16_delegate(FUNC(ngbootleg_prot_device::mslug5_prot_r),this), write16_delegate(FUNC(ngbootleg_prot_device::ms5plus_bankswitch_w),this));
	m_bankdev = bankdev;

}


/* SNK vs. CAPCOM SVC CHAOS (bootleg) */


void ngbootleg_prot_device::svcboot_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const uint8_t sec[] = {
		0x06, 0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00
	};
	int i;
	int size = cpurom_size;
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst( size );
	int ofst;
	for( i = 0; i < size / 0x100000; i++ ){
		memcpy( &dst[ i * 0x100000 ], &src[ sec[ i ] * 0x100000 ], 0x100000 );
	}
	for( i = 0; i < size / 2; i++ ){
		ofst = BITSWAP8( (i & 0x0000ff), 7, 6, 1, 0, 3, 2, 5, 4 );
		ofst += (i & 0xffff00);
		memcpy( &src[ i * 2 ], &dst[ ofst * 2 ], 0x02 );
	}
}

void ngbootleg_prot_device::svcboot_cx_decrypt(uint8_t*sprrom, uint32_t sprrom_size)
{
	static const uint8_t idx_tbl[ 0x10 ] = {
		0, 1, 0, 1, 2, 3, 2, 3, 3, 4, 3, 4, 4, 5, 4, 5,
	};
	static const uint8_t bitswap4_tbl[ 6 ][ 4 ] = {
		{ 3, 0, 1, 2 },
		{ 2, 3, 0, 1 },
		{ 1, 2, 3, 0 },
		{ 0, 1, 2, 3 },
		{ 3, 2, 1, 0 },
		{ 3, 0, 2, 1 },
	};
	int i;
	int size = sprrom_size;
	uint8_t *src = sprrom;
	std::vector<uint8_t> dst( size );
	int ofst;
	memcpy( &dst[0], src, size );
	for( i = 0; i < size / 0x80; i++ ){
		int idx = idx_tbl[ (i & 0xf00) >> 8 ];
		int bit0 = bitswap4_tbl[ idx ][ 0 ];
		int bit1 = bitswap4_tbl[ idx ][ 1 ];
		int bit2 = bitswap4_tbl[ idx ][ 2 ];
		int bit3 = bitswap4_tbl[ idx ][ 3 ];
		ofst = BITSWAP8( (i & 0x0000ff), 7, 6, 5, 4, bit3, bit2, bit1, bit0 );
		ofst += (i & 0xfffff00);
		memcpy( &src[ i * 0x80 ], &dst[ ofst * 0x80 ], 0x80 );
	}
}


/* SNK vs. CAPCOM SVC CHAOS Plus (bootleg set 1) */


void ngbootleg_prot_device::svcplus_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const int sec[] = {
		0x00, 0x03, 0x02, 0x05, 0x04, 0x01
	};
	int size = cpurom_size;
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst( size );
	int i;
	int ofst;
	memcpy( &dst[0], src, size );
	for( i = 0; i < size / 2; i++ ){
		ofst = BITSWAP24( (i & 0xfffff), 0x17, 0x16, 0x15, 0x14, 0x13, 0x00, 0x01, 0x02,
											0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08,
											0x07, 0x06, 0x05, 0x04, 0x03, 0x10, 0x11, 0x12 );
		ofst ^= 0x0f0007;
		ofst += (i & 0xff00000);
		memcpy( &src[ i * 0x02 ], &dst[ ofst * 0x02 ], 0x02 );
	}
	memcpy( &dst[0], src, size );
	for( i = 0; i < 6; i++ ){
		memcpy( &src[ i * 0x100000 ], &dst[ sec[ i ] * 0x100000 ], 0x100000 );
	}
}

void ngbootleg_prot_device::svcplus_px_hack(uint8_t* cpurom, uint32_t cpurom_size)
{
	/* patched by the protection chip? */
	uint16_t *mem16 = (uint16_t *)cpurom;
	mem16[0x0f8016/2] = 0x33c1;
}


/* SNK vs. CAPCOM SVC CHAOS Plus (bootleg set 2) */


void ngbootleg_prot_device::svcplusa_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i;
	static const int sec[] = {
		0x01, 0x02, 0x03, 0x04, 0x05, 0x00
	};
	int size = cpurom_size;
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst( size );
	memcpy( &dst[0], src, size );
	for( i = 0; i < 6; i++ ){
		memcpy( &src[ i * 0x100000 ], &dst[ sec[ i ] * 0x100000 ], 0x100000 );
	}
}


/* SNK vs. CAPCOM SVC CHAOS Super Plus (bootleg) */


void ngbootleg_prot_device::svcsplus_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const int sec[] = {
		0x06, 0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00
	};
	int size = cpurom_size;
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst( size );
	int i;
	int ofst;
	memcpy( &dst[0], src, size );
	for( i = 0; i < size / 2; i++ ){
		ofst = BITSWAP16( (i & 0x007fff), 0x0f, 0x00, 0x08, 0x09, 0x0b, 0x0a, 0x0c, 0x0d,
											0x04, 0x03, 0x01, 0x07, 0x06, 0x02, 0x05, 0x0e );

		ofst += (i & 0x078000);
		ofst += sec[ (i & 0xf80000) >> 19 ] << 19;
		memcpy( &src[ i * 2 ], &dst[ ofst * 2 ], 0x02 );
	}
}

void ngbootleg_prot_device::svcsplus_px_hack(uint8_t* cpurom, uint32_t cpurom_size)
{
	/* patched by the protection chip? */
	uint16_t *mem16 = (uint16_t *)cpurom;
	mem16[0x9e90/2] = 0x000f;
	mem16[0x9e92/2] = 0xc9c0;
	mem16[0xa10c/2] = 0x4eb9;
	mem16[0xa10e/2] = 0x000e;
	mem16[0xa110/2] = 0x9750;
}


/* The King of Fighters 2003 (bootleg set 1) */


READ16_MEMBER( ngbootleg_prot_device::kof2003_r)
{
	return m_cartridge_ram[offset];
}

READ16_MEMBER(ngbootleg_prot_device::kof2003_overlay_r) // hack?
{
	return kof2k3_overlay;
}

WRITE16_MEMBER( ngbootleg_prot_device::kof2003_w )
{
	data = COMBINE_DATA(&m_cartridge_ram[offset]);
	if (offset == 0x1ff0/2 || offset == 0x1ff2/2) {
		uint8_t* cr = (uint8_t *)m_cartridge_ram;
		uint32_t address = (cr[BYTE_XOR_LE(0x1ff3)]<<16)|(cr[BYTE_XOR_LE(0x1ff2)]<<8)|cr[BYTE_XOR_LE(0x1ff1)];
		uint8_t prt = cr[BYTE_XOR_LE(0x1ff2)];

		cr[BYTE_XOR_LE(0x1ff0)] =  0xa0;
		cr[BYTE_XOR_LE(0x1ff1)] &= 0xfe;
		cr[BYTE_XOR_LE(0x1ff3)] &= 0x7f;
		m_bankdev->neogeo_set_main_cpu_bank_address(address+0x100000);

		kof2k3_overlay = (prt & 0x00ff) | (kof2k3_overlay & 0xff00);
	}
}

WRITE16_MEMBER( ngbootleg_prot_device::kof2003p_w )
{
	data = COMBINE_DATA(&m_cartridge_ram[offset]);
	if (offset == 0x1ff0/2 || offset == 0x1ff2/2) {
		uint8_t* cr = (uint8_t *)m_cartridge_ram;
		uint32_t address = (cr[BYTE_XOR_LE(0x1ff3)]<<16)|(cr[BYTE_XOR_LE(0x1ff2)]<<8)|cr[BYTE_XOR_LE(0x1ff0)];
		uint8_t prt = cr[BYTE_XOR_LE(0x1ff2)];

		cr[BYTE_XOR_LE(0x1ff0)] &= 0xfe;
		cr[BYTE_XOR_LE(0x1ff3)] &= 0x7f;
		m_bankdev->neogeo_set_main_cpu_bank_address(address+0x100000);

		kof2k3_overlay = (prt & 0x00ff) | (kof2k3_overlay & 0xff00);
	}
}

void ngbootleg_prot_device::kf2k3bl_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i;
	static const uint8_t sec[] = {
		0x07, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06
	};

	int rom_size = 0x800000;
	uint8_t *rom = cpurom;
	std::vector<uint8_t> buf( rom_size );
	memcpy( &buf[0], rom, rom_size );

	for( i = 0; i < rom_size / 0x100000; i++ ){
		memcpy( &rom[ i * 0x100000 ], &buf[ sec[ i ] * 0x100000 ], 0x100000 );
	}
}

void ngbootleg_prot_device::kf2k3bl_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size)
{
	m_mainrom = cpurom;

	maincpu->space(AS_PROGRAM).install_read_handler(0x58196, 0x58197, read16_delegate(FUNC(ngbootleg_prot_device::kof2003_overlay_r),this) );

	maincpu->space(AS_PROGRAM).install_readwrite_handler(0x2fe000, 0x2fffff, read16_delegate(FUNC(ngbootleg_prot_device::kof2003_r),this), write16_delegate(FUNC(ngbootleg_prot_device::kof2003_w),this) );
	m_bankdev = bankdev;

}


/* The King of Fighters 2004 Plus / Hero (The King of Fighters 2003 bootleg) */


void ngbootleg_prot_device::kf2k3pl_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	std::vector<uint16_t> tmp(0x100000/2);
	uint16_t*rom16 = (uint16_t*)cpurom;
	int j;
	int i;

	for (i = 0;i < 0x700000/2;i+=0x100000/2)
	{
		memcpy(&tmp[0],&rom16[i],0x100000);
		for (j = 0;j < 0x100000/2;j++)
			rom16[i+j] = tmp[BITSWAP24(j,23,22,21,20,19,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18)];
	}

	/* patched by Altera protection chip on PCB */
	rom16[0xf38ac/2] = 0x4e75;

	kof2k3_overlay = rom16[0x58196 / 2];
}

void ngbootleg_prot_device::kf2k3pl_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size)
{
	m_mainrom = cpurom;
	maincpu->space(AS_PROGRAM).install_readwrite_handler(0x2fe000, 0x2fffff, read16_delegate(FUNC(ngbootleg_prot_device::kof2003_r),this), write16_delegate(FUNC(ngbootleg_prot_device::kof2003p_w),this) );
	m_bankdev = bankdev;
}


/* The King of Fighters 2004 Ultra Plus (The King of Fighters 2003 bootleg) */


void ngbootleg_prot_device::kf2k3upl_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	{
		uint8_t *src = cpurom;
		memmove(src+0x100000, src, 0x600000);
		memmove(src, src+0x700000, 0x100000);
	}

	{
		int ofst;
		int i;
		uint8_t *rom = cpurom + 0xfe000;
		uint8_t *buf = cpurom + 0xd0610;

		for( i = 0; i < 0x2000 / 2; i++ ){
			ofst = (i & 0xff00) + BITSWAP8( (i & 0x00ff), 7, 6, 0, 4, 3, 2, 1, 5 );
			memcpy( &rom[ i * 2 ], &buf[ ofst * 2 ], 2 );
		}
	}

	uint16_t*rom16 = (uint16_t*)cpurom;
	kof2k3_overlay = rom16[0x58196 / 2];


}


/* Samurai Shodown V / Samurai Spirits Zero (bootleg) */


void ngbootleg_prot_device::samsho5b_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	int px_size = cpurom_size;
	uint8_t *rom = cpurom;
	std::vector<uint8_t> buf( px_size );
	int ofst;
	int i;

	memcpy( &buf[0], rom, px_size );

	for( i = 0; i < px_size / 2; i++ ){
		ofst = BITSWAP8( (i & 0x000ff), 7, 6, 5, 4, 3, 0, 1, 2 );
		ofst += (i & 0xfffff00);
		ofst ^= 0x060005;

		memcpy( &rom[ i * 2 ], &buf[ ofst * 2 ], 0x02 );
	}

	memcpy( &buf[0], rom, px_size );

	memcpy( &rom[ 0x000000 ], &buf[ 0x700000 ], 0x100000 );
	memcpy( &rom[ 0x100000 ], &buf[ 0x000000 ], 0x700000 );
}


void ngbootleg_prot_device::samsho5b_vx_decrypt(uint8_t* ymsndrom, uint32_t ymsndrom_size)
{
	int vx_size = ymsndrom_size;
	uint8_t *rom = ymsndrom;
	int i;

	for( i = 0; i < vx_size; i++ )
		rom[ i ] = BITSWAP8( rom[ i ], 0, 1, 5, 4, 3, 2, 6, 7 );
}


/* Matrimelee / Shin Gouketsuji Ichizoku Toukon (bootleg) */


#define MATRIMBLZ80( i ) ( i^(BITSWAP8(i&0x3,4,3,1,2,0,7,6,5)<<8) )

void ngbootleg_prot_device::matrimbl_decrypt(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size)
{
	/* decrypt Z80 */
	uint8_t *rom = audiorom+0x10000;
	std::vector<uint8_t> buf( 0x20000 );
	int i, j;
	memcpy( &buf[0], rom, 0x20000 );
	for( i=0x00000; i<0x20000; i++ )
	{
		if ( i&0x10000 )
		{
			if ( i&0x800 )
			{
				j=MATRIMBLZ80( i );
				j=j^0x10000;
			}
			else
			{
				j=MATRIMBLZ80(( i^0x01 ));
			}
		}
		else
		{
			if ( i&0x800 )
			{
				j=MATRIMBLZ80(( i^0x01 ));
				j=j^0x10000;
			}
			else
			{
				j=MATRIMBLZ80( i );
			}
		}
		rom[ j ]=buf[ i ];
	}
	memcpy( rom-0x10000, rom, 0x10000 );

	/* decrypt gfx */
	cthd2003_c(sprrom,sprrom_size, 0 );
}
