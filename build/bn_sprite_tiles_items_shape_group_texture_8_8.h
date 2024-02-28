#ifndef BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_8_8_H
#define BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_8_8_H

#include "bn_sprite_tiles_item.h"
#include "bn_sprite_shape_size.h"

//{{BLOCK(shape_group_texture_8_8_bn_gfx)

//======================================================================
//
//	shape_group_texture_8_8_bn_gfx, 8x8@4, 
//	+ 1 tiles not compressed
//	Total size: 32 = 32
//
//	Time-stamp: 2024-02-28, 16:25:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SHAPE_GROUP_TEXTURE_8_8_BN_GFX_H
#define GRIT_SHAPE_GROUP_TEXTURE_8_8_BN_GFX_H

#define shape_group_texture_8_8_bn_gfxTilesLen 32
extern const bn::tile shape_group_texture_8_8_bn_gfxTiles[1];

#endif // GRIT_SHAPE_GROUP_TEXTURE_8_8_BN_GFX_H

//}}BLOCK(shape_group_texture_8_8_bn_gfx)

namespace bn::sprite_tiles_items
{
    constexpr inline sprite_tiles_item shape_group_texture_8_8(span<const tile>(shape_group_texture_8_8_bn_gfxTiles, 1), 
            bpp_mode::BPP_4, compression_type::NONE, 1);

    constexpr inline sprite_shape_size shape_group_texture_8_8_shape_size(sprite_shape::SQUARE, sprite_size::SMALL);
}

#endif

