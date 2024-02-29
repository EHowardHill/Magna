#ifndef BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_10_16_H
#define BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_10_16_H

#include "bn_sprite_tiles_item.h"
#include "bn_sprite_shape_size.h"

//{{BLOCK(shape_group_texture_10_16_bn_gfx)

//======================================================================
//
//	shape_group_texture_10_16_bn_gfx, 16x16@4, 
//	+ 4 tiles not compressed
//	Total size: 128 = 128
//
//	Time-stamp: 2024-02-28, 22:06:05
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SHAPE_GROUP_TEXTURE_10_16_BN_GFX_H
#define GRIT_SHAPE_GROUP_TEXTURE_10_16_BN_GFX_H

#define shape_group_texture_10_16_bn_gfxTilesLen 128
extern const bn::tile shape_group_texture_10_16_bn_gfxTiles[4];

#endif // GRIT_SHAPE_GROUP_TEXTURE_10_16_BN_GFX_H

//}}BLOCK(shape_group_texture_10_16_bn_gfx)

namespace bn::sprite_tiles_items
{
    constexpr inline sprite_tiles_item shape_group_texture_10_16(span<const tile>(shape_group_texture_10_16_bn_gfxTiles, 4), 
            bpp_mode::BPP_4, compression_type::NONE, 1);

    constexpr inline sprite_shape_size shape_group_texture_10_16_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL);
}

#endif

