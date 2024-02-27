
@{{BLOCK(arrow_bn_gfx)

@=======================================================================
@
@	arrow_bn_gfx, 8x8@4, 
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2024-02-27, 14:21:38
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global arrow_bn_gfxTiles		@ 32 unsigned chars
	.hidden arrow_bn_gfxTiles
arrow_bn_gfxTiles:
	.word 0x00027000,0x00169D00,0x016AFFD0,0x148DFEB9,0x57BDFDA6,0x000BB000,0x00099000,0x00086000

	.section .rodata
	.align	2
	.global arrow_bn_gfxPal		@ 32 unsigned chars
	.hidden arrow_bn_gfxPal
arrow_bn_gfxPal:
	.hword 0x03E0,0x7AF6,0x7B17,0x7B16,0x7B37,0x7B58,0x7B7A,0x7F9B
	.hword 0x7FBC,0x7FBD,0x7FDE,0x7FDF,0x7FFE,0x7FFF,0x7FFF,0x7FFF

@}}BLOCK(arrow_bn_gfx)
