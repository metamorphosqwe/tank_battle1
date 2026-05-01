// ===== enemy.h =====
#ifndef ENEMY_H
#define ENEMY_H

#include "game_constants.h"

struct Enemy {
    int x, y;
    Direction dir;
    bool active;
    int move_timer, shoot_timer;
};

extern Enemy g_enemies[MAX_ENEMIES];
extern int g_enemy_count;

void init_enemies();
bool add_enemy(int x, int y);
void update_enemies(int field_height, int field_width, 
                    char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH]);
void render_enemies_on_field(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                              int height, int width);
bool enemy_hit(int x, int y);
Enemy* get_active_enemy(int index);
int count_active_enemies();
Direction generate_random_direction();

#endif
