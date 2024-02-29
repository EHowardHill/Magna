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
#include <bn_sprite_text_generator.h>
#include <bn_sprite_font.h>
#include "bn_music.h"
#include "bn_music_actions.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include <bn_string.h>

#include "bn_sprite_items_font_01.h"

#include "bn_sprite_items_arrow.h"
#include "bn_sprite_items_enoki.h"

#include "bn_sprite_items_chat_enoki01.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_space.h"
#include "bn_regular_bg_items_bg_grass.h"
#include "bn_regular_bg_items_bg_grass_marked.h"

using namespace bn;
using namespace core;
using namespace keypad;
using namespace sprite_items;
using namespace regular_bg_items;

#define WEST 0
#define EAST 1

const sprite_font font = sprite_font(font_01);

fixed_t<12> lerp(fixed a, int b, fixed_t<12> t)
{
	return a * (1 - t) + b * t;
}

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

const map world[1] = {
    {
        5, 5,                   // Width + Height
        {                       // Events
            {0, 0, 0}
        },
        {                       // Ports
            {2, 1, 2, 1, 0}
        },
        {                       // Collision map
            0, 0, 1, 1, 1,
            0, 0, 0, 0, 1,
            1, 0, 1, 0, 1,
            1, 0, 0, 0, 1,
            1, 1, 1, 1, 1
        }
    }
};



#define END -1
#define C_NULL  0
#define C_ENOKI 1

struct option {
    const int ref;
    const bn::string<64> text;
};

struct line {
    const int ref;
    const int reply;
    const int speaker;
    const int frame;
    const int side;
    const string<64> main;
};

const option replies[1][5] = {
    {
        {3, "Texas"}, 
        {5, "Louisiana"}, 
        {7, "Arkansas"}, 
        {9, "Oklahoma"}, 
        {11, "New Mexico"}
    }
};

const line chat[1][13] = {
    {
        {0, END, C_ENOKI, 0, WEST, "Is this working?"},
        {1, END, C_ENOKI, 1, EAST, "This ought to be working."},
        {2, 0},
        {3, END, C_ENOKI, 1, WEST, "Welcome to Texas!"},
        {4, END, END},
        {5, END, C_ENOKI, 1, WEST, "Welcome to Louisiana!"},
        {6, END, END},
        {7, END, C_ENOKI, 1, WEST, "Welcome to Arkansas!"},
        {8, END, END},
        {9, END, C_ENOKI, 1, WEST, "Welcome to Oklahoma!"},
        {10, END, END},
        {11, END, C_ENOKI, 1, WEST, "Welcome to New Mexico!"},
        {12, END, END},
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

void overworld(int current_world) {
    bn::camera_ptr cam = bn::camera_ptr::create(0,0);
    int last_dir = 0;

    vector<sprite_ptr, 32> collids;

    for (int e = 0; e < world[current_world].width * world[current_world].height; e++) {
        if (world[current_world].collisions[e]) {
            auto a = arrow.create_sprite((e % world[current_world].width) * 32, (e / world[current_world].height) * 32);
            a.set_camera(cam);
            collids.push_back(a);
        }
    }

    auto player = enoki.create_sprite(world[current_world].ports[0].my_x * 32, world[current_world].ports[0].my_y * 32);
    auto player_anim = create_sprite_animate_action_forever(player, 4, enoki.tiles_item(), 0, 1, 0, 2);
    auto bg = bg_grass_marked.create_bg(-144, -144);

    player.set_camera(cam);
    bg.set_camera(cam);

    while (true) {

        int i_x = right_held() - left_held();
        int i_y = down_held() - up_held();
        int p_x = player.x().integer();
        int p_y = player.y().integer();

        int dx = i_x != 0 && check_tile(i_x * 16 + p_x, -12 + p_y, current_world) && check_tile(i_x * 16 + p_x, 12 + p_y, current_world) ? i_x : 0;
        int dy = i_y != 0 && check_tile(-12 + p_x, i_y * 16 + p_y, current_world) && check_tile(12 + p_x, i_y * 16 + p_y, current_world) ? i_y : 0;
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

int dialogue(int conversation) {

    sprite_text_generator text_line(font);
    vector<sprite_ptr, 24> text_vector[5];
    string<28> text_cache[5];

    auto bg = bg_space.create_bg(-144, -144);
    auto w_chat = chat_enoki01.create_sprite(-160, 48, 0);
    auto e_chat = chat_enoki01.create_sprite(160, 48, 0);
    auto spr_arrow = arrow.create_sprite(-112, -64);
    bool w_active = false;
    bool e_active = false;
    bool trigger_option = false;
    int pos = 0;
    int a_pos = 0;
    int w_char = -1;
    int e_char = -1;
    int span = 0;

    while (true) {

        bg.set_position(span, span);
        span = (span + 1) % 256;
        auto state = &chat[conversation][pos];

        if (spr_arrow.visible()) {
            if (down_pressed()) {
                sound_items::sfx_poolball.play();
                a_pos = (a_pos + 1) % 5;
            }

            if (up_pressed()) {
                sound_items::sfx_poolball.play();
                a_pos--;
                if (a_pos < 0) a_pos = 4;
            }

            spr_arrow.set_y(lerp(spr_arrow.y(), -64 + (a_pos * 16), 0.5));
        }

        if (a_pressed() || pos == 0) {

            sound_items::sfx_blip.play();

            int x_pos = 0;
            int y_pos = 0;

            for (int t = 0; t < 5; t++) {
                text_cache[t].clear();
                text_vector[t].clear();
            }

            if (state->speaker == END) return 0;

            if (spr_arrow.visible()) {
                pos = replies[state->reply][a_pos].ref;
                state = &chat[conversation][pos];
            }

            if (state->reply != END && !spr_arrow.visible()) {

                for (int t = 0; t < 5; t++) {
                    text_cache[t] = replies[state->reply][t].text;
                }

                spr_arrow.set_visible(true);

            } else {

                int x_offset = -96;
                sprite_ptr* a_chat;

                if (state->side == WEST) {
                    a_chat = &w_chat;
                    w_active = true;
                    w_char = state->speaker;
                    if (w_char == state->speaker) x_offset = -84;
                } else {
                    a_chat = &e_chat;
                    x_offset = 96;
                    e_active = true;
                    e_char = state->speaker;
                    if (e_char == state->speaker) x_offset = 84;
                }

                switch (state->speaker) {
                    case C_ENOKI:
                        *a_chat = chat_enoki01.create_sprite(x_offset, 48, state->frame);
                        break;
                }

                if (state->side == EAST) a_chat->set_horizontal_flip(true);

                for (int t = 0; t < state->main.length(); t++) {
                    if (x_pos > 20 && state->main.at(t) == ' ') {
                        x_pos = 0;
                        y_pos++;
                    } else {
                        text_cache[y_pos].push_back(state->main.at(t));
                    }
                    x_pos++;
                }

                pos++;
                spr_arrow.set_visible(false);
            }

            text_line.generate(-94, -64, text_cache[0], text_vector[0]);
            text_line.generate(-94, -48, text_cache[1], text_vector[1]);
            text_line.generate(-94, -32, text_cache[2], text_vector[2]);
            text_line.generate(-94, -16, text_cache[3], text_vector[3]);
            text_line.generate(-94, 0, text_cache[4], text_vector[4]);
        }

        if (w_active) {
            w_chat.set_x(lerp(w_chat.x(), -88, 0.2));
        } else {
            w_chat.set_x(lerp(w_chat.x(), -160, 0.2));
        }

        if (e_active) {
            e_chat.set_x(lerp(e_chat.x(), 88, 0.2));
        } else {
            e_chat.set_x(lerp(e_chat.x(), 160, 0.2));
        }

        update();
    }
}

int main() {
    init();
    globals = new global_data();

    int current_world = 0;
    bn::music_items::dixie.play(0.5);

    while (true) {
        dialogue(current_world);

        update();
    }
}