// ===== collision.cpp =====
#include "collision.h"
#include "projectile.h"
#include "enemy.h"
#include "player.h"

bool check_projectile_wall_collision(int proj_x, int proj_y, const GameField& field) {
    if (proj_x < 0 || proj_x >= field.width || proj_y < 0 || proj_y >= field.height)
        return true;
    return field.data[proj_y][proj_x] == SYMBOL_WALL;
}

int check_projectile_enemy_collision(int proj_x, int proj_y) {
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active && g_enemies[i].x == proj_x && g_enemies[i].y == proj_y)
            return i;
    }
    return -1;
}

bool check_projectile_player_collision(int proj_x, int proj_y) {
    const Player& player = get_player();
    return player.alive && player.x == proj_x && player.y == proj_y;
}

void process_all_collisions(GameField& field) {
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        if (!g_projectiles[i].active) continue;
        
        int proj_x = g_projectiles[i].x;
        int proj_y = g_projectiles[i].y;
        
        if (check_projectile_wall_collision(proj_x, proj_y, field)) {
            g_projectiles[i].active = false;
            --g_projectile_count;
            continue;
        }
        
        int enemy_index = check_projectile_enemy_collision(proj_x, proj_y);
        if (enemy_index != -1) {
            g_enemies[enemy_index].active = false;
            --g_enemy_count;
            g_projectiles[i].active = false;
            --g_projectile_count;
            continue;
        }
        
        if (check_projectile_player_collision(proj_x, proj_y)) {
            player_hit(proj_x, proj_y);
            g_projectiles[i].active = false;
            --g_projectile_count;
            continue;
        }
    }
}
