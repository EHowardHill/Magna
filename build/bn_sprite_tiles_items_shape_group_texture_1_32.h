#ifndef BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_1_32_H
#define BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_1_32_H

#include "bn_sprite_tiles_item.h"
#include "bn_sprite_shape_size.h"

//{{BLOCK(shape_group_texture_1_32_bn_gfx)

//======================================================================
//
//	shape_group_texture_1_32_bn_gfx, 32x32@4, 
//	+ 16 tiles not compressed
//	Total size: 512 = 512
//
//	Time-stamp: 2024-02-28, 12:40:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SHAPE_GROUP_TEXTURE_1_32_BN_GFX_H
#define GRIT_SHAPE_GROUP_TEXTURE_1_32_BN_GFX_H

#define shape_group_texture_1_32_bn_gfxTilesLen 512
extern const bn::tile shape_group_texture_1_32_bn_gfxTiles[16];

#endif // GRIT_SHAPE_GROUP_TEXTURE_1_32_BN_GFX_H

//}}BLOCK(shape_group_texture_1_32_bn_gfx)

namespace bn::sprite_tiles_items
{
    constexpr inline sprite_tiles_item shape_group_texture_1_32(span<const tile>(shape_group_texture_1_32_bn_gfxTiles, 16), 
            bpp_mode::BPP_4, compression_type::NONE, 1);

    constexpr inline sprite_shape_size shape_group_texture_1_32_shape_size(sprite_shape::SQUARE, sprite_size::BIG);
}

#endif

