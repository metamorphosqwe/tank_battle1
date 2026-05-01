// ===== player.h =====
#ifndef PLAYER_H
#define PLAYER_H

#include "game_constants.h"

struct Player {
    int x, y;
    Direction last_dir;
    bool alive;
};

void init_player(int start_x, int start_y);
const Player& get_player();
bool handle_player_input(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                         int field_height, int field_width);
void render_player_on_field(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                            int height, int width);
bool player_hit(int x, int y);
void reset_player();

#endif
