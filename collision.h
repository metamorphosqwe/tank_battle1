// ===== collision.h =====
#ifndef COLLISION_H
#define COLLISION_H

#include "game_constants.h"
#include "field.h"

bool check_projectile_wall_collision(int proj_x, int proj_y, const GameField& field);
int check_projectile_enemy_collision(int proj_x, int proj_y);
bool check_projectile_player_collision(int proj_x, int proj_y);
void process_all_collisions(GameField& field);

#endif
