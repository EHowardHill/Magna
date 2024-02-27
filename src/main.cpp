#include "bn_core.h"
#include "bn_log.h"
#include <bn_fixed.h>
#include <bn_vector.h>
#include <bn_random.h>
#include <bn_math.h>
#include <bn_keypad.h>
#include "bn_blending.h"

#include <bn_sprite_ptr.h>
#include "bn_sound_items.h"

#include "bn_sprite_items_a_van_car.h"
#include "bn_sprite_items_arrow.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_space.h"

#include "bn_sprite_items_numbers.h"

using namespace bn;
using namespace core;
using namespace keypad;

class Map {
    public:
    int width = 8;
    int height = 8;

    int flatten(int x, int y) {
        return x + (y * width);
    }
};

// Reserved global memory
class global_data
{
public:
	int collision_map[256];
	random bn_random;

	global_data() {}
};

global_data *globals;

bool check_tile(char x, char y) {
    if (globals->collision_map[x + y] == 0) {
        return true;
    }

    return false;
}

int main() {
    init();
    globals = new global_data();

    sprite_ptr arrow = sprite_items::arrow.create_sprite(-80, 0);
    regular_bg_ptr bg_space = bn::regular_bg_items::bg_space.create_bg(0, 0);

    while (true) {

        int d_x = 0;
        int d_y = 0;
        int i_x = right_held() - left_held();
        int i_y = down_held() - up_held();

        if (i_x == 1 && check_tile(1, 0)) {
            d_x = 1;
        } else if (i_x == -1 && check_tile(-1, 0)) {
            d_x = -1;
        }

        if (i_y == 1 && check_tile(0, 1)) {
            d_y = 1;
        } else if (i_y == -1 && check_tile(0, -1)) {
            d_y = -1;
        }

        arrow.set_position(arrow.x() + d_x, arrow.y() + d_y);

        update();
    }
}