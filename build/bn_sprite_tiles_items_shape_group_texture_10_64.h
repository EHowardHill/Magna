#ifndef BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_10_64_H
#define BN_SPRITE_TILES_ITEMS_SHAPE_GROUP_TEXTURE_10_64_H

#include "bn_sprite_tiles_item.h"
#include "bn_sprite_shape_size.h"

//{{BLOCK(shape_group_texture_10_64_bn_gfx)

//======================================================================
//
//	shape_group_texture_10_64_bn_gfx, 64x64@4, 
//	+ 64 tiles not compressed
//	Total size: 2048 = 2048
//
//	Time-stamp: 2024-02-28, 16:25:12
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SHAPE_GROUP_TEXTURE_10_64_BN_GFX_H
#define GRIT_SHAPE_GROUP_TEXTURE_10_64_BN_GFX_H

#define shape_group_texture_10_64_bn_gfxTilesLen 2048
extern const bn::tile shape_group_texture_10_64_bn_gfxTiles[64];

#endif // GRIT_SHAPE_GROUP_TEXTURE_10_64_BN_GFX_H

//}}BLOCK(shape_group_texture_10_64_bn_gfx)

namespace bn::sprite_tiles_items
{
    constexpr inline sprite_tiles_item shape_group_texture_10_64(span<const tile>(shape_group_texture_10_64_bn_gfxTiles, 64), 
            bpp_mode::BPP_4, compression_type::NONE, 1);

    constexpr inline sprite_shape_size shape_group_texture_10_64_shape_size(sprite_shape::SQUARE, sprite_size::HUGE);
}

#endif

