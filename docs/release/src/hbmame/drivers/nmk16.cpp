// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/nmk16.cpp"

// http://daifukkat.su/hacks/tdpract/  describes all about this hack, however nothing on that page works.
// The patch-bytes below get it to start up, but inputs don't work, and practice mode is unobtainable.
ROM_START( tdragonp )
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD16_BYTE( "91070_68k.8p",  0x00000, 0x20000, BAD_DUMP CRC(6930fffc) SHA1(571cc735dca654b77cd759b6cc52a74c24d88865) )
	ROM_LOAD16_BYTE( "91070_68k.7p",  0x00001, 0x20000, BAD_DUMP CRC(c2d90c90) SHA1(d6c3dd955e516e9dc5efbb7aebc6dee9c49a8c98) )
	ROM_FILL(0, 1, 0) // fix stack
	ROM_FILL(2, 2, 0)
	ROM_FILL(0x9320,1,0x42) // fix corruption
	ROM_FILL(0x9321,1,0x79)
	ROM_FILL(0x9322,1,0x00)
	ROM_FILL(0x9323,1,0x0b)
	ROM_FILL(0x9324,1,0x90)
	ROM_FILL(0x9325,1,0x08)
	ROM_FILL(0x8f8e,1,0x48) // fix another corruption
	ROM_FILL(0x8f8f,1,0x41)
	ROM_FILL(0x8f90,1,0x42)
	ROM_FILL(0x8f91,1,0x41)
	ROM_FILL(0x8f92,1,0xe2)
	ROM_FILL(0x8f93,1,0x81)

	ROM_REGION( 0x020000, "fgtile", 0 )
	ROM_LOAD( "91070.6",        0x000000, 0x20000, CRC(fe365920) SHA1(7581931cb95cd5a8ed40e4f5385b533e3d19af22) )

	ROM_REGION( 0x100000, "bgtile", 0 )
	ROM_LOAD( "91070.5",        0x000000, 0x100000, CRC(d0bde826) SHA1(3b74d5fc88a4a9329e101ee72f393608d327d816) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD16_WORD_SWAP( "91070.4",    0x000000, 0x100000, CRC(3eedc2fe) SHA1(9f48986c231a8fbc07f2b39b2017d1e967b2ed3c) )

	ROM_REGION( 0x010000, "audiocpu", 0 )
	ROM_LOAD( "91070.1",      0x00000, 0x10000, CRC(bf493d74) SHA1(6f8f5eff4b71fb6cabda10075cfa88a3f607859e) )

	ROM_REGION( 0x080000, "oki1", 0 )
	ROM_LOAD( "91070.3",     0x00000, 0x80000, CRC(ae6875a8) SHA1(bfdb350b3d3fce2bead1ac60875beafe427765ed) )

	ROM_REGION( 0x080000, "oki2", 0 )
	ROM_LOAD( "91070.2",     0x00000, 0x80000, CRC(ecfea43e) SHA1(d664dfa6698fec8e602523bdae16068f1ff6547b) )

	ROM_REGION( 0x0200, "proms", 0 )
	ROM_LOAD( "91070.9",  0x0000, 0x0100, CRC(cfdbb86c) SHA1(588822f6308a860937349c9106c2b4b1a75823ec) )
	ROM_LOAD( "91070.10", 0x0100, 0x0100, CRC(e6ead349) SHA1(6d81b1c0233580aa48f9718bade42d640e5ef3dd) )
ROM_END


// http://daifukkat.su/hacks/td2pract/  describes all about this hack.
ROM_START( tdragon2p )
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "6p.rom",      0x00000, 0x80000, CRC(f99f4bf8) SHA1(34dfc188d94b89efdaa61cfc40af88868d7f22db) )

	ROM_REGION( 0x20000, "audiocpu", 0 )
	ROM_LOAD( "5.bin",    0x00000, 0x20000, CRC(b870be61) SHA1(ea5d45c3a3ab805e55806967f00167cf6366212e) )

	ROM_REGION( 0x020000, "fgtile", 0 )
	ROM_LOAD( "1.bin",    0x000000, 0x020000, CRC(d488aafa) SHA1(4d05e7ca075b638dd90ae4c9f224817a8a3ae9f3) )

	ROM_REGION( 0x200000, "bgtile", 0 )
	ROM_LOAD( "ww930914.2", 0x000000, 0x200000, CRC(f968c65d) SHA1(fd6d21bba53f945b1597d7d0735bc62dd44d5498) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD16_WORD_SWAP( "ww930917.7", 0x000000, 0x200000, CRC(b98873cb) SHA1(cc19200865176e940ff68e12de81f029b51c2084) )
	ROM_LOAD16_WORD_SWAP( "ww930918.8", 0x200000, 0x200000, CRC(baee84b2) SHA1(b325b00e6147266dbdc840e03556004531dc2038) )

	ROM_REGION( 0x240000, "oki1", 0 )
	ROM_LOAD( "ww930916.4", 0x040000, 0x200000, CRC(07c35fe6) SHA1(33547bd88764704310f2ef8cf3bfe21ceb56d5b7) )

	ROM_REGION( 0x240000, "oki2", 0 )
	ROM_LOAD( "ww930915.3", 0x040000, 0x200000, CRC(82025bab) SHA1(ac6053700326ea730d00ec08193e2c8a2a019f0b) )

	ROM_REGION( 0x0200, "proms", 0 )
	ROM_LOAD( "9.bpr",  0x0000, 0x0100, CRC(435653a2) SHA1(575b4a46ea65179de3042614da438d2f6d8b572e) )
	ROM_LOAD( "10.bpr", 0x0100, 0x0100, CRC(e6ead349) SHA1(6d81b1c0233580aa48f9718bade42d640e5ef3dd) )
ROM_END

GAME( 1991, tdragonp, tdragon,  tdragon,  tdragon,  nmk16_state, empty_init,            ROT270, "Trap15", "Thunder Dragon (Practice Mode)", MACHINE_NOT_WORKING | MACHINE_IMPERFECT_SOUND | MACHINE_IMPERFECT_GRAPHICS )
GAME( 1993, tdragon2p,tdragon2, tdragon2, tdragon2, nmk16_state, init_banked_audiocpu,  ROT270, "Trap15", "Thunder Dragon 2 (Practice Mode)", MACHINE_NO_COCKTAIL | MACHINE_IMPERFECT_GRAPHICS )

