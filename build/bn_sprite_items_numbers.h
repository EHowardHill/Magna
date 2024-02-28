#ifndef BN_SPRITE_ITEMS_NUMBERS_H
#define BN_SPRITE_ITEMS_NUMBERS_H

#include "bn_sprite_item.h"

//{{BLOCK(numbers_bn_gfx)

//======================================================================
//
//	numbers_bn_gfx, 8x96@4, 
//	+ palette 16 entries, not compressed
//	+ 12 tiles not compressed
//	Total size: 32 + 384 = 416
//
//	Time-stamp: 2024-02-28, 12:40:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NUMBERS_BN_GFX_H
#define GRIT_NUMBERS_BN_GFX_H

#define numbers_bn_gfxTilesLen 384
extern const bn::tile numbers_bn_gfxTiles[12];

#define numbers_bn_gfxPalLen 32
extern const bn::color numbers_bn_gfxPal[16];

#endif // GRIT_NUMBERS_BN_GFX_H

//}}BLOCK(numbers_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item numbers(sprite_shape_size(sprite_shape::SQUARE, sprite_size::SMALL), 
            sprite_tiles_item(span<const tile>(numbers_bn_gfxTiles, 12), bpp_mode::BPP_4, compression_type::NONE, 12), 
            sprite_palette_item(span<const color>(numbers_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

