// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
// thanks-to:Fuzz

/***************************************************************************

Special decryption used on svcpcb and kf2k3pcb.

***************************************************************************/

#include "emu.h"
#include "includes/neogeo.h"




/* ms5pcb and svcpcb have an additional scramble on top of the standard CMC scrambling */
void neogeo_noslot_state::svcpcb_gfx_decrypt()
{
	static const uint8_t xorval[ 4 ] = { 0x34, 0x21, 0xc4, 0xe9 };
	int i;
	int ofst;
	int rom_size = memregion( "sprites" )->bytes();
	uint8_t *rom = memregion( "sprites" )->base();
	std::vector<uint8_t> buf( rom_size );

	for( i = 0; i < rom_size; i++ )
	{
		rom[ i ] ^= xorval[ (i % 4) ];
	}
	for( i = 0; i < rom_size; i += 4 )
	{
		uint32_t rom32 = rom[i] | rom[i+1]<<8 | rom[i+2]<<16 | rom[i+3]<<24;
		rom32 = BITSWAP32( rom32, 0x09, 0x0d, 0x13, 0x00, 0x17, 0x0f, 0x03, 0x05, 0x04, 0x0c, 0x11, 0x1e, 0x12, 0x15, 0x0b, 0x06, 0x1b, 0x0a, 0x1a, 0x1c, 0x14, 0x02, 0x0e, 0x1d, 0x18, 0x08, 0x01, 0x10, 0x19, 0x1f, 0x07, 0x16 );
		buf[i]   = rom32       & 0xff;
		buf[i+1] = (rom32>>8)  & 0xff;
		buf[i+2] = (rom32>>16) & 0xff;
		buf[i+3] = (rom32>>24) & 0xff;
	}
	for( i = 0; i < rom_size / 4; i++ )
	{
		ofst =  BITSWAP24( (i & 0x1fffff), 0x17, 0x16, 0x15, 0x04, 0x0b, 0x0e, 0x08, 0x0c, 0x10, 0x00, 0x0a, 0x13, 0x03, 0x06, 0x02, 0x07, 0x0d, 0x01, 0x11, 0x09, 0x14, 0x0f, 0x12, 0x05 );
		ofst ^= 0x0c8923;
		ofst += (i & 0xffe00000);
		memcpy( &rom[ i * 4 ], &buf[ ofst * 4 ], 0x04 );
	}
}


/* and a further swap on the s1 data */
void neogeo_noslot_state::svcpcb_s1data_decrypt()
{
	int i;
	uint8_t *s1 = memregion( "fixed" )->base();
	size_t s1_size = memregion( "fixed" )->bytes();

	for( i = 0; i < s1_size; i++ ) // Decrypt S
	{
		s1[ i ] = BITSWAP8( s1[ i ] ^ 0xd2, 4, 0, 7, 2, 5, 1, 6, 3 );
	}
}


/* kf2k3pcb has an additional scramble on top of the standard CMC scrambling */
/* Thanks to Razoola & Halrin for the info */
void neogeo_noslot_state::kf2k3pcb_gfx_decrypt()
{
	static const uint8_t xorval[ 4 ] = { 0x34, 0x21, 0xc4, 0xe9 };
	int i;
	int ofst;
	int rom_size = memregion( "sprites" )->bytes();
	uint8_t *rom = memregion( "sprites" )->base();
	std::vector<uint8_t> buf( rom_size );

	for ( i = 0; i < rom_size; i++ )
	{
		rom[ i ] ^= xorval[ (i % 4) ];
	}
	for ( i = 0; i < rom_size; i +=4 )
	{
		uint32_t rom32 = rom[i] | rom[i+1]<<8 | rom[i+2]<<16 | rom[i+3]<<24;
		rom32 = BITSWAP32( rom32, 0x09, 0x0d, 0x13, 0x00, 0x17, 0x0f, 0x03, 0x05, 0x04, 0x0c, 0x11, 0x1e, 0x12, 0x15, 0x0b, 0x06, 0x1b, 0x0a, 0x1a, 0x1c, 0x14, 0x02, 0x0e, 0x1d, 0x18, 0x08, 0x01, 0x10, 0x19, 0x1f, 0x07, 0x16 );
		buf[i]   =  rom32      & 0xff;
		buf[i+1] = (rom32>>8)  & 0xff;
		buf[i+2] = (rom32>>16) & 0xff;
		buf[i+3] = (rom32>>24) & 0xff;
	}
	for ( i = 0; i < rom_size; i+=4 )
	{
		ofst = BITSWAP24( (i & 0x7fffff), 0x17, 0x15, 0x0a, 0x14, 0x13, 0x16, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00 );
		ofst ^= 0x000000;
		ofst += (i & 0xff800000);
		memcpy( &rom[ ofst ], &buf[ i ], 0x04 );
	}
}


/* and a further swap on the s1 data */
void neogeo_noslot_state::kf2k3pcb_decrypt_s1data()
{
	uint8_t *src;
	uint8_t *dst;
	int i;
	int tx_size = memregion( "fixed" )->bytes();
	int srom_size = memregion( "sprites" )->bytes();

	src = memregion( "sprites" )->base() + srom_size - 0x1000000 - 0x80000; // Decrypt S
	dst = memregion( "fixed" )->base();

	for( i = 0; i < tx_size / 2; i++ )
	{
		dst[ i ] = src[ (i & ~0x1f) + ((i & 7) << 2) + ((~i & 8) >> 2) + ((i & 0x10) >> 4) ];
	}

	src = memregion( "sprites" )->base() + srom_size - 0x80000;
	dst = memregion( "fixed" )->base() + 0x80000;

	for( i = 0; i < tx_size / 2; i++ )
	{
		dst[ i ] = src[ (i & ~0x1f) + ((i & 7) << 2) + ((~i & 8) >> 2) + ((i & 0x10) >> 4) ];
	}

	dst = memregion( "fixed" )->base();

	for( i = 0; i < tx_size; i++ )
	{
		dst[ i ] = BITSWAP8( dst[ i ] ^ 0xd2, 4, 0, 7, 2, 5, 1, 6, 3 );
	}
}





/***************************************************************************

NeoGeo 'SP1' (BIOS) ROM encryption

***************************************************************************/


/* only found on kf2k3pcb */
void neogeo_noslot_state::kf2k3pcb_sp1_decrypt()
{
	static const uint8_t address[0x40] = {
		0x04,0x0a,0x04,0x0a,0x04,0x0a,0x04,0x0a,
		0x0a,0x04,0x0a,0x04,0x0a,0x04,0x0a,0x04,
		0x09,0x07,0x09,0x07,0x09,0x07,0x09,0x07,
		0x09,0x09,0x04,0x04,0x09,0x09,0x04,0x04,
		0x0b,0x0d,0x0b,0x0d,0x03,0x05,0x03,0x05,
		0x0e,0x0e,0x03,0x03,0x0e,0x0e,0x03,0x03,
		0x03,0x05,0x0b,0x0d,0x03,0x05,0x0b,0x0d,
		0x04,0x00,0x04,0x00,0x0e,0x0a,0x0e,0x0a
	};

	uint16_t *rom = (uint16_t *)memregion("mainbios")->base();
	std::vector<uint16_t> buf(0x80000/2);
	int i, addr;

	for (i = 0; i < 0x80000/2; i++)
	{
		// address xor
		addr = i ^ 0x0020;
		if ( i & 0x00020) addr ^= 0x0010;
		if (~i & 0x00010) addr ^= 0x0040;
		if (~i & 0x00004) addr ^= 0x0080;
		if ( i & 0x00200) addr ^= 0x0100;
		if (~i & 0x02000) addr ^= 0x0400;
		if (~i & 0x10000) addr ^= 0x1000;
		if ( i & 0x02000) addr ^= 0x8000;
		addr ^= address[((i >> 1) & 0x38) | (i & 7)];
		buf[i] = rom[addr];

		// data xor
		if (buf[i] & 0x0004) buf[i] ^= 0x0001;
		if (buf[i] & 0x0010) buf[i] ^= 0x0002;
		if (buf[i] & 0x0020) buf[i] ^= 0x0008;
	}

	memcpy(rom, &buf[0], 0x80000);
}
