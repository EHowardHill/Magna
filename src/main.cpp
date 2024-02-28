#include "bn_core.h"
#include "bn_log.h"
#include <bn_fixed.h>
#include <bn_vector.h>
#include <bn_random.h>
#include <bn_math.h>
#include <bn_keypad.h>
#include "bn_blending.h"
#include <bn_sprite_ptr.h>
#include <bn_camera_ptr.h>
#include <bn_sprite_animate_actions.h>

#include "bn_sound_items.h"
#include "bn_sprite_items_arrow.h"
#include "bn_sprite_items_marker.h"
#include "bn_sprite_items_enoki.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_space.h"

using namespace bn;
using namespace core;
using namespace keypad;
using namespace sprite_items;
using namespace regular_bg_items;

// Reserved global memory
class global_data
{
public:
	global_data() {}
};

global_data *globals;

struct event {
    const char my_x;
    const char my_y;
    const char id;
};

struct port {
    const char my_x;
    const char my_y;
    const char to_x;
    const char to_y;
    const char to_world;
};

struct map {
    const char width;
    const char height;
    const event events[16];
    const port ports[8];
    const bool collisions[256];
};

const struct map world[1] = {
    {
        5, 5,                   // Width + Height
        {                       // Events
            {0, 0, 0}
        },
        {                       // Ports
            {2, 1, 2, 1, 0}
        },
        {                       // Collision map
            1, 1, 1, 1, 1,
            1, 0, 0, 0, 1,
            1, 0, 1, 0, 1,
            1, 0, 0, 0, 1,
            1, 1, 1, 1, 1
        }
    }
};

int coordsToNum(int x, int y, int width) {
    return (x % width) + (y * width);
}

int round32(int x) {
    return (x / 32) + (x % 32 > 16);
}

bool check_tile(int x, int y, int mapNum) {
    return !world[mapNum].collisions[coordsToNum(round32(x), round32(y), world[mapNum].width)];
}

int main() {
    init();
    globals = new global_data();

    int current_world = 0;
    int last_dir = 0;

    bn::camera_ptr cam = bn::camera_ptr::create(0,0);

    vector<sprite_ptr, 32> collids;

    auto player = enoki.create_sprite(world[current_world].ports[0].my_x * 32, world[current_world].ports[0].my_y * 32);
    auto player_anim = create_sprite_animate_action_forever(player, 4, enoki.tiles_item(), 0, 1, 0, 2);
    auto bg = bg_space.create_bg(0, 0);

    player.set_camera(cam);
    bg.set_camera(cam);

    for (int e = 0; e < world[current_world].width * world[current_world].height; e++) {
        if (world[current_world].collisions[e]) {
            auto a = arrow.create_sprite((e % world[current_world].width) * 32, (e / world[current_world].height) * 32);
            a.set_camera(cam);
            collids.push_back(a);
        }
    }

    while (true) {

        int i_x = right_held() - left_held();
        int i_y = down_held() - up_held();
        int p_x = player.x().integer();
        int p_y = player.y().integer();
        int dx = i_x != 0 && check_tile(i_x * 16 + p_x, p_y, current_world) && check_tile(i_x * 16 + p_x, -8 + p_y, current_world) && check_tile(i_x * 16 + p_x, 8 + p_y, current_world) ? i_x : 0;
        int dy = i_y != 0 && check_tile(p_x, i_y * 16 + p_y, current_world) && check_tile(-8 + p_x, i_y * 16 + p_y, current_world) && check_tile(8 + p_x, i_y * 16 + p_y, current_world) ? i_y : 0;
        player.set_position(p_x + dx, p_y + dy);
        
        if (i_x != 0 || i_y != 0) {
            if (last_dir == -1 || (last_dir == 3 && i_x <= 0) || (last_dir == 6 && i_x >= 0) || (last_dir == 0 && i_y <= 0) || (last_dir == 9 && i_y >= 0)) {
                if (i_x > 0) {
                    last_dir = 3;
                } else if (i_x < 0) {
                    last_dir = 6;
                } else if (i_y > 0) {
                    last_dir = 0;
                } else if (i_y < 0) {
                    last_dir = 9;
                }

                player_anim = create_sprite_animate_action_forever(player, 4, enoki.tiles_item(), last_dir, last_dir + 1, last_dir, last_dir + 2);
            }
            player_anim.update();
        } else if (last_dir != -1) {
            player_anim = create_sprite_animate_action_forever(player, 4, enoki.tiles_item(), last_dir, last_dir, last_dir, last_dir);
            player_anim.update();
            last_dir = -1;
        }

        cam.set_position(p_x, p_y);
        update();
    }
}