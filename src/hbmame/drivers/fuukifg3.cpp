// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/fuukifg3.cpp"

ROM_START( asurablds01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE( "s01_3.u1", 0x000000, 0x80000, CRC(d895969b) SHA1(e7846fffd5fb16e47edb48d0adf80d42b6a5d58d) )
	ROM_LOAD32_BYTE( "s01_2.u2", 0x000001, 0x80000, CRC(3dfde713) SHA1(c4fbfb9c608256c576ec5f28f2147562e44a7463) )
	ROM_LOAD32_BYTE( "s01_1.u3", 0x000002, 0x80000, CRC(90715f6f) SHA1(b776ffb5d962936b499c52eef1015e657a06687a) )
	ROM_LOAD32_BYTE( "s01_0.u4", 0x000003, 0x80000, CRC(2d51018b) SHA1(f12b3091bbdec3d46800bad383adfb1ccd523c3a) )

	ROM_REGION( 0x080000, "soundcpu", 0 )
	ROM_LOAD( "srom.u7", 0x00000, 0x80000, CRC(bb1deb89) SHA1(b1c70abddc0b9a88beb69a592376ff69a7e091eb) )

	ROM_REGION( 0x2000000, "fuukivid", 0 )
	ROM_LOAD16_WORD_SWAP( "sp23.u14", 0x0400000, 0x400000, CRC(7df492eb) SHA1(30b88a3cd025ffc8c28fef06e0784755be37ef8e) )
	ROM_LOAD16_WORD_SWAP( "sp45.u15", 0x0800000, 0x400000, CRC(1890f42a) SHA1(22254fe38fd83f4602a25e1ccba32df16edaf3f9) )
	ROM_LOAD16_WORD_SWAP( "sp67.u16", 0x0c00000, 0x400000, CRC(a48f1ef0) SHA1(bf8787f293793291a503af662d3738c007654726) )
	ROM_LOAD16_WORD_SWAP( "sp89.u17", 0x1000000, 0x400000, CRC(6b024362) SHA1(8be5cc3c7306d28b75acd970bb3be6d3c9825367) )
	ROM_LOAD16_WORD_SWAP( "spab.u18", 0x1400000, 0x400000, CRC(803d2d8c) SHA1(25df30689e576a0620656c721d92bcc3fbd84844) )
	ROM_LOAD16_WORD_SWAP( "spcd.u19", 0x1800000, 0x400000, CRC(42e5c26e) SHA1(b68875d353bdc5d49113bbac02fd83508bce66a5) )

	ROM_REGION( 0x0800000, "gfx2", 0 )
	ROM_LOAD32_WORD_SWAP( "bg1012.u22", 0x0000002, 0x400000, CRC(d717a0a1) SHA1(007df309dc0650ca07e077b983a2b05730349d0b) )
	ROM_LOAD32_WORD_SWAP( "bg1113.u23", 0x0000000, 0x400000, CRC(94338267) SHA1(7848bc57cb0eac216100a508763451eb57a0a082) )

	ROM_REGION( 0x0800000, "gfx3", 0 )
	ROM_LOAD32_WORD_SWAP( "bg2022.u25", 0x0000002, 0x400000, CRC(ee312cd3) SHA1(2ef9d51928d80375daf8e6b204bb66a8b9cbaee7) )
	ROM_LOAD32_WORD_SWAP( "bg2123.u24", 0x0000000, 0x400000, CRC(4acfc469) SHA1(a98d06b967ebb3fa3b4c8aa3d7a05063ec981fb2) )

	ROM_REGION( 0x200000, "gfx4", 0 )
	ROM_LOAD16_WORD_SWAP( "map.u5", 0x00000, 0x200000, CRC(e681155e) SHA1(458845b9c86df72685d92d0d4052aacc2fa7d1bd) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "pcm.u6", 0x00000, 0x400000, CRC(ac72225a) SHA1(8d16399ed34ac5bd69dbf43b2de2b0db9ac1c610) )
ROM_END

ROM_START( asurablds02 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE( "s02_3.u1", 0x000000, 0x80000, CRC(e65f2f19) SHA1(d2d9735842010fb3f9cb85a9255172db3a93937d) )
	ROM_LOAD32_BYTE( "s02_2.u2", 0x000001, 0x80000, CRC(67e608d3) SHA1(0bc7b9e9fefb0d0f35afb5dae40b25300a00b543) )
	ROM_LOAD32_BYTE( "s02_1.u3", 0x000002, 0x80000, CRC(85ec63ae) SHA1(768e4f1da9e126f94873a2e6c6a304643143faea) )
	ROM_LOAD32_BYTE( "s02_0.u4", 0x000003, 0x80000, CRC(a9a90415) SHA1(7445ad491a1f6c7733f0ee79e912fd186f8ae222) )

	ROM_REGION( 0x080000, "soundcpu", 0 )
	ROM_LOAD( "srom.u7", 0x00000, 0x80000, CRC(bb1deb89) SHA1(b1c70abddc0b9a88beb69a592376ff69a7e091eb) )

	ROM_REGION( 0x2000000, "fuukivid", 0 )
	ROM_LOAD16_WORD_SWAP( "sp23.u14", 0x0400000, 0x400000, CRC(7df492eb) SHA1(30b88a3cd025ffc8c28fef06e0784755be37ef8e) )
	ROM_LOAD16_WORD_SWAP( "sp45.u15", 0x0800000, 0x400000, CRC(1890f42a) SHA1(22254fe38fd83f4602a25e1ccba32df16edaf3f9) )
	ROM_LOAD16_WORD_SWAP( "sp67.u16", 0x0c00000, 0x400000, CRC(a48f1ef0) SHA1(bf8787f293793291a503af662d3738c007654726) )
	ROM_LOAD16_WORD_SWAP( "sp89.u17", 0x1000000, 0x400000, CRC(6b024362) SHA1(8be5cc3c7306d28b75acd970bb3be6d3c9825367) )
	ROM_LOAD16_WORD_SWAP( "spab.u18", 0x1400000, 0x400000, CRC(803d2d8c) SHA1(25df30689e576a0620656c721d92bcc3fbd84844) )
	ROM_LOAD16_WORD_SWAP( "spcd.u19", 0x1800000, 0x400000, CRC(42e5c26e) SHA1(b68875d353bdc5d49113bbac02fd83508bce66a5) )

	ROM_REGION( 0x0800000, "gfx2", 0 )
	ROM_LOAD32_WORD_SWAP( "bg1012.u22", 0x0000002, 0x400000, CRC(d717a0a1) SHA1(007df309dc0650ca07e077b983a2b05730349d0b) )
	ROM_LOAD32_WORD_SWAP( "bg1113.u23", 0x0000000, 0x400000, CRC(94338267) SHA1(7848bc57cb0eac216100a508763451eb57a0a082) )

	ROM_REGION( 0x0800000, "gfx3", 0 )
	ROM_LOAD32_WORD_SWAP( "bg2022.u25", 0x0000002, 0x400000, CRC(ee312cd3) SHA1(2ef9d51928d80375daf8e6b204bb66a8b9cbaee7) )
	ROM_LOAD32_WORD_SWAP( "bg2123.u24", 0x0000000, 0x400000, CRC(4acfc469) SHA1(a98d06b967ebb3fa3b4c8aa3d7a05063ec981fb2) )

	ROM_REGION( 0x200000, "gfx4", 0 )
	ROM_LOAD16_WORD_SWAP( "map.u5", 0x00000, 0x200000, CRC(e681155e) SHA1(458845b9c86df72685d92d0d4052aacc2fa7d1bd) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "pcm.u6", 0x00000, 0x400000, CRC(ac72225a) SHA1(8d16399ed34ac5bd69dbf43b2de2b0db9ac1c610) )
ROM_END

ROM_START( asurablds03 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE( "s03_3.u1", 0x000000, 0x80000, CRC(3bf42eda) SHA1(4f6447d149618593c25353b54b64aff8d00e402e) )
	ROM_LOAD32_BYTE( "s03_2.u2", 0x000001, 0x80000, CRC(4cadb90a) SHA1(15a91eeae818368d5757e6891da7e295eb74ba87) )
	ROM_LOAD32_BYTE( "s03_1.u3", 0x000002, 0x80000, CRC(208d7893) SHA1(80fd9a3e9be1ea920fc9ec760b325fccb0d29b0f) )
	ROM_LOAD32_BYTE( "s03_0.u4", 0x000003, 0x80000, CRC(ec995109) SHA1(1485e5eee2c72121b36f8d3ce04c5cbec7469169) )

	ROM_REGION( 0x080000, "soundcpu", 0 )
	ROM_LOAD( "srom.u7", 0x00000, 0x80000, CRC(bb1deb89) SHA1(b1c70abddc0b9a88beb69a592376ff69a7e091eb) )

	ROM_REGION( 0x2000000, "fuukivid", 0 )
	ROM_LOAD16_WORD_SWAP( "sp23.u14", 0x0400000, 0x400000, CRC(7df492eb) SHA1(30b88a3cd025ffc8c28fef06e0784755be37ef8e) )
	ROM_LOAD16_WORD_SWAP( "sp45.u15", 0x0800000, 0x400000, CRC(1890f42a) SHA1(22254fe38fd83f4602a25e1ccba32df16edaf3f9) )
	ROM_LOAD16_WORD_SWAP( "sp67.u16", 0x0c00000, 0x400000, CRC(a48f1ef0) SHA1(bf8787f293793291a503af662d3738c007654726) )
	ROM_LOAD16_WORD_SWAP( "sp89.u17", 0x1000000, 0x400000, CRC(6b024362) SHA1(8be5cc3c7306d28b75acd970bb3be6d3c9825367) )
	ROM_LOAD16_WORD_SWAP( "spab.u18", 0x1400000, 0x400000, CRC(803d2d8c) SHA1(25df30689e576a0620656c721d92bcc3fbd84844) )
	ROM_LOAD16_WORD_SWAP( "spcd.u19", 0x1800000, 0x400000, CRC(42e5c26e) SHA1(b68875d353bdc5d49113bbac02fd83508bce66a5) )

	ROM_REGION( 0x0800000, "gfx2", 0 )
	ROM_LOAD32_WORD_SWAP( "bg1012.u22", 0x0000002, 0x400000, CRC(d717a0a1) SHA1(007df309dc0650ca07e077b983a2b05730349d0b) )
	ROM_LOAD32_WORD_SWAP( "bg1113.u23", 0x0000000, 0x400000, CRC(94338267) SHA1(7848bc57cb0eac216100a508763451eb57a0a082) )

	ROM_REGION( 0x0800000, "gfx3", 0 )
	ROM_LOAD32_WORD_SWAP( "bg2022.u25", 0x0000002, 0x400000, CRC(ee312cd3) SHA1(2ef9d51928d80375daf8e6b204bb66a8b9cbaee7) )
	ROM_LOAD32_WORD_SWAP( "bg2123.u24", 0x0000000, 0x400000, CRC(4acfc469) SHA1(a98d06b967ebb3fa3b4c8aa3d7a05063ec981fb2) )

	ROM_REGION( 0x200000, "gfx4", 0 )
	ROM_LOAD16_WORD_SWAP( "map.u5", 0x00000, 0x200000, CRC(e681155e) SHA1(458845b9c86df72685d92d0d4052aacc2fa7d1bd) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "pcm.u6", 0x00000, 0x400000, CRC(ac72225a) SHA1(8d16399ed34ac5bd69dbf43b2de2b0db9ac1c610) )
ROM_END

ROM_START( asurablds04 ) //asurabldl
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE( "s04_3.u1", 0x000000, 0x80000, CRC(65331e9b) SHA1(e7bc5636a4ffd5abef68b38ff1cbb58fd821e2aa) )
	ROM_LOAD32_BYTE( "s03_2.u2", 0x000001, 0x80000, CRC(4cadb90a) SHA1(15a91eeae818368d5757e6891da7e295eb74ba87) )
	ROM_LOAD32_BYTE( "s03_1.u3", 0x000002, 0x80000, CRC(208d7893) SHA1(80fd9a3e9be1ea920fc9ec760b325fccb0d29b0f) )
	ROM_LOAD32_BYTE( "s04_0.u4", 0x000003, 0x80000, CRC(1657a971) SHA1(c838de7c45e9ed3b5809c52e792b8a70cf1378c2) )

	ROM_REGION( 0x080000, "soundcpu", 0 )
	ROM_LOAD( "srom.u7", 0x00000, 0x80000, CRC(bb1deb89) SHA1(b1c70abddc0b9a88beb69a592376ff69a7e091eb) )

	ROM_REGION( 0x2000000, "fuukivid", 0 )
	ROM_LOAD16_WORD_SWAP( "sp23.u14", 0x0400000, 0x400000, CRC(7df492eb) SHA1(30b88a3cd025ffc8c28fef06e0784755be37ef8e) )
	ROM_LOAD16_WORD_SWAP( "sp45.u15", 0x0800000, 0x400000, CRC(1890f42a) SHA1(22254fe38fd83f4602a25e1ccba32df16edaf3f9) )
	ROM_LOAD16_WORD_SWAP( "sp67.u16", 0x0c00000, 0x400000, CRC(a48f1ef0) SHA1(bf8787f293793291a503af662d3738c007654726) )
	ROM_LOAD16_WORD_SWAP( "sp89.u17", 0x1000000, 0x400000, CRC(6b024362) SHA1(8be5cc3c7306d28b75acd970bb3be6d3c9825367) )
	ROM_LOAD16_WORD_SWAP( "spab.u18", 0x1400000, 0x400000, CRC(803d2d8c) SHA1(25df30689e576a0620656c721d92bcc3fbd84844) )
	ROM_LOAD16_WORD_SWAP( "spcd.u19", 0x1800000, 0x400000, CRC(42e5c26e) SHA1(b68875d353bdc5d49113bbac02fd83508bce66a5) )

	ROM_REGION( 0x0800000, "gfx2", 0 )
	ROM_LOAD32_WORD_SWAP( "bg1012.u22", 0x0000002, 0x400000, CRC(d717a0a1) SHA1(007df309dc0650ca07e077b983a2b05730349d0b) )
	ROM_LOAD32_WORD_SWAP( "bg1113.u23", 0x0000000, 0x400000, CRC(94338267) SHA1(7848bc57cb0eac216100a508763451eb57a0a082) )

	ROM_REGION( 0x0800000, "gfx3", 0 )
	ROM_LOAD32_WORD_SWAP( "bg2022.u25", 0x0000002, 0x400000, CRC(ee312cd3) SHA1(2ef9d51928d80375daf8e6b204bb66a8b9cbaee7) )
	ROM_LOAD32_WORD_SWAP( "bg2123.u24", 0x0000000, 0x400000, CRC(4acfc469) SHA1(a98d06b967ebb3fa3b4c8aa3d7a05063ec981fb2) )

	ROM_REGION( 0x200000, "gfx4", 0 )
	ROM_LOAD16_WORD_SWAP( "map.u5", 0x00000, 0x200000, CRC(e681155e) SHA1(458845b9c86df72685d92d0d4052aacc2fa7d1bd) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "pcm.u6", 0x00000, 0x400000, CRC(ac72225a) SHA1(8d16399ed34ac5bd69dbf43b2de2b0db9ac1c610) )
ROM_END

ROM_START( asurabuss01 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE( "s01_3.u1", 0x000000, 0x80000, CRC(dd9df251) SHA1(8ed4ddaefe7b4f6760d884963bd593ce88c991d9) )
	ROM_LOAD32_BYTE( "s01_2.u2", 0x000001, 0x80000, CRC(2e360db2) SHA1(f9489cac523109aada2fa58f0e43130d9c537bd2) )
	ROM_LOAD32_BYTE( "s01_1.u3", 0x000002, 0x80000, CRC(71c4fcfc) SHA1(b0ed5302393b196f11f042e4b0964495e799bb6e) )
	ROM_LOAD32_BYTE( "s01_0.u4", 0x000003, 0x80000, CRC(44a33fcb) SHA1(97a0bc3922049a99ae3c71bd9dcea04ccc7237ba) )

	ROM_REGION( 0x080000, "soundcpu", 0 )
	ROM_LOAD( "srom.u7", 0x00000, 0x80000, CRC(368da389) SHA1(1423b709da40bf3033c9032c4bd07658f1a969de) )

	ROM_REGION( 0x2000000, "fuukivid", 0 )
	ROM_LOAD16_WORD_SWAP( "sp01.u13", 0x0000000, 0x400000, CRC(5edea463) SHA1(22a780912f060bae0c9a403a7bfd4d27f25b76e3) )
	ROM_LOAD16_WORD_SWAP( "sp23.u14", 0x0400000, 0x400000, CRC(91b1b0de) SHA1(341367966559ef2027415b673eb0db704680c81f) )
	ROM_LOAD16_WORD_SWAP( "sp45.u15", 0x0800000, 0x400000, CRC(96c69aac) SHA1(cf053523026651427f884b9dd7c095af362dd24e) )
	ROM_LOAD16_WORD_SWAP( "sp67.u16", 0x0c00000, 0x400000, CRC(7c3d83bf) SHA1(7188dd923c6c7eb6aee3323e7ab54aa240c35ea3) )
	ROM_LOAD16_WORD_SWAP( "sp89.u17", 0x1000000, 0x400000, CRC(cb1e14f8) SHA1(941cea1887d7ceb52222adcf1d6913969e6163aa) )
	ROM_LOAD16_WORD_SWAP( "spab.u18", 0x1400000, 0x400000, CRC(e5a4608d) SHA1(b8e39f53e0b7ad1e16ae9c3726597776b404be1c) )
	ROM_LOAD16_WORD_SWAP( "spcd.u19", 0x1800000, 0x400000, CRC(99bfbe32) SHA1(926a8afc4a175874f22f53300e76f59331d3b9ba) )
	ROM_LOAD16_WORD_SWAP( "spef.u20", 0x1c00000, 0x400000, CRC(c9c799cc) SHA1(01373316700d8688deeea2e9e8f831d5f86c7f17) )

	ROM_REGION( 0x0800000, "gfx2", 0 )
	ROM_LOAD32_WORD_SWAP( "bg1012.u22", 0x0000002, 0x400000, CRC(e3fb9af0) SHA1(11900cc2873337692f66fb4f1eb9c574e5a967de) )
	ROM_LOAD32_WORD_SWAP( "bg1113.u23", 0x0000000, 0x400000, CRC(5f8657e6) SHA1(7c2854dc5d2d4efe55bda01e329da051350e0031) )

	ROM_REGION( 0x0800000, "gfx3", 0 )
	ROM_LOAD32_WORD_SWAP( "bg2022.u25", 0x0000002, 0x400000, CRC(f46eda52) SHA1(46530016b32a164bd76c4f53e7b53b2beb28db06) )
	ROM_LOAD32_WORD_SWAP( "bg2123.u24", 0x0000000, 0x400000, CRC(c4ebb86b) SHA1(a7093e6e02b64566d277cbbd5fa90cd430e7c8a0) )

	ROM_REGION( 0x200000, "gfx4", 0 )
	ROM_LOAD16_WORD_SWAP( "map.u5", 0x00000, 0x200000, CRC(bd179dc5) SHA1(ce3fcac573b14fd5365eb5dcec3257e439d2c129) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "opm.u6", 0x00000, 0x400000, CRC(31b05be4) SHA1(d0f4f387f84a74591224b0f42b7f5c538a3dc498) )
ROM_END

ROM_START( asurabuss02 )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD32_BYTE( "s02_3.u1", 0x000000, 0x80000, CRC(2201d9cb) SHA1(fdcd916b5749dc1fd21c13a24bfd6c031036a295) )
	ROM_LOAD32_BYTE( "s02_2.u2", 0x000001, 0x80000, CRC(09530179) SHA1(5b6b6d43c93b43948f1ab726cf5ea59420c43e2e) )
	ROM_LOAD32_BYTE( "s01_1.u3", 0x000002, 0x80000, CRC(71c4fcfc) SHA1(b0ed5302393b196f11f042e4b0964495e799bb6e) )
	ROM_LOAD32_BYTE( "s02_0.u4", 0x000003, 0x80000, CRC(1e040613) SHA1(db7fe4199025b6f67e86611e99043ae80a008527) )

	ROM_REGION( 0x080000, "soundcpu", 0 )
	ROM_LOAD( "srom.u7", 0x00000, 0x80000, CRC(368da389) SHA1(1423b709da40bf3033c9032c4bd07658f1a969de) )

	ROM_REGION( 0x2000000, "fuukivid", 0 )
	ROM_LOAD16_WORD_SWAP( "sp01.u13", 0x0000000, 0x400000, CRC(5edea463) SHA1(22a780912f060bae0c9a403a7bfd4d27f25b76e3) )
	ROM_LOAD16_WORD_SWAP( "sp23.u14", 0x0400000, 0x400000, CRC(91b1b0de) SHA1(341367966559ef2027415b673eb0db704680c81f) )
	ROM_LOAD16_WORD_SWAP( "sp45.u15", 0x0800000, 0x400000, CRC(96c69aac) SHA1(cf053523026651427f884b9dd7c095af362dd24e) )
	ROM_LOAD16_WORD_SWAP( "sp67.u16", 0x0c00000, 0x400000, CRC(7c3d83bf) SHA1(7188dd923c6c7eb6aee3323e7ab54aa240c35ea3) )
	ROM_LOAD16_WORD_SWAP( "sp89.u17", 0x1000000, 0x400000, CRC(cb1e14f8) SHA1(941cea1887d7ceb52222adcf1d6913969e6163aa) )
	ROM_LOAD16_WORD_SWAP( "spab.u18", 0x1400000, 0x400000, CRC(e5a4608d) SHA1(b8e39f53e0b7ad1e16ae9c3726597776b404be1c) )
	ROM_LOAD16_WORD_SWAP( "spcd.u19", 0x1800000, 0x400000, CRC(99bfbe32) SHA1(926a8afc4a175874f22f53300e76f59331d3b9ba) )
	ROM_LOAD16_WORD_SWAP( "spef.u20", 0x1c00000, 0x400000, CRC(c9c799cc) SHA1(01373316700d8688deeea2e9e8f831d5f86c7f17) )

	ROM_REGION( 0x0800000, "gfx2", 0 )
	ROM_LOAD32_WORD_SWAP( "bg1012.u22", 0x0000002, 0x400000, CRC(e3fb9af0) SHA1(11900cc2873337692f66fb4f1eb9c574e5a967de) )
	ROM_LOAD32_WORD_SWAP( "bg1113.u23", 0x0000000, 0x400000, CRC(5f8657e6) SHA1(7c2854dc5d2d4efe55bda01e329da051350e0031) )

	ROM_REGION( 0x0800000, "gfx3", 0 )
	ROM_LOAD32_WORD_SWAP( "bg2022.u25", 0x0000002, 0x400000, CRC(f46eda52) SHA1(46530016b32a164bd76c4f53e7b53b2beb28db06) )
	ROM_LOAD32_WORD_SWAP( "bg2123.u24", 0x0000000, 0x400000, CRC(c4ebb86b) SHA1(a7093e6e02b64566d277cbbd5fa90cd430e7c8a0) )

	ROM_REGION( 0x200000, "gfx4", 0 )
	ROM_LOAD16_WORD_SWAP( "map.u5", 0x00000, 0x200000, CRC(bd179dc5) SHA1(ce3fcac573b14fd5365eb5dcec3257e439d2c129) )

	ROM_REGION( 0x400000, "ymf", 0 )
	ROM_LOAD( "opm.u6", 0x00000, 0x400000, CRC(31b05be4) SHA1(d0f4f387f84a74591224b0f42b7f5c538a3dc498) )
ROM_END


GAME( 2009, asurablds01, asurabld, fuuki32, asurabld, fuuki32_state, empty_init, ROT0, "pipi899", "Asura Blade - Sword of Dynasty (Energy Mode Max 2009-11-21)", MACHINE_SUPPORTS_SAVE )
GAME( 1998, asurablds02, asurabld, fuuki32, asurabld, fuuki32_state, empty_init, ROT0, "yumeji", "Asura Blade - Sword of Dynasty (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, asurablds03, asurabld, fuuki32, asurabld, fuuki32_state, empty_init, ROT0, "hack", "Asura Blade - Sword of Dynasty (Enhanced Edition 1.0)", MACHINE_SUPPORTS_SAVE )
GAME( 2018, asurablds04, asurabld, fuuki32, asurabld, fuuki32_state, empty_init, ROT0, "hack", "Asura Blade - Sword of Dynasty (Simplified Edition 2018-06-04)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, asurabuss01, asurabus, fuuki32, asurabusa,fuuki32_state, empty_init, ROT0, "yumeji", "Asura Buster (Enable Hidden Characters)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, asurabuss02, asurabus, fuuki32, asurabusa,fuuki32_state, empty_init, ROT0, "hack", "Asura Buster (Super Remix Edition 1.0)", MACHINE_SUPPORTS_SAVE )

