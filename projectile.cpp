// ===== projectile.cpp =====
#include "projectile.h"
#include <cstring>

Projectile g_projectiles[MAX_PROJECTILES];
int g_projectile_count = 0;

void init_projectiles() {
    g_projectile_count = 0;
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        g_projectiles[i].active = false;
        g_projectiles[i].x = 0;
        g_projectiles[i].y = 0;
        g_projectiles[i].dir = Direction::NONE;
    }
}

bool create_projectile(int x, int y, Direction dir) {
    if (g_projectile_count >= MAX_PROJECTILES) return false;
    
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        if (!g_projectiles[i].active) {
            g_projectiles[i].x = x;
            g_projectiles[i].y = y;
            g_projectiles[i].dir = dir;
            g_projectiles[i].active = true;
            ++g_projectile_count;
            return true;
        }
    }
    return false;
}

void update_projectiles(int field_height, int field_width) {
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        if (g_projectiles[i].active) {
            switch (g_projectiles[i].dir) {
                case Direction::UP: g_projectiles[i].y--; break;
                case Direction::DOWN: g_projectiles[i].y++; break;
                case Direction::LEFT: g_projectiles[i].x--; break;
                case Direction::RIGHT: g_projectiles[i].x++; break;
                default:
                    g_projectiles[i].active = false;
                    --g_projectile_count;
                    continue;
            }
            
            if (g_projectiles[i].x < 0 || g_projectiles[i].x >= field_width ||
                g_projectiles[i].y < 0 || g_projectiles[i].y >= field_height) {
                g_projectiles[i].active = false;
                --g_projectile_count;
            }
        }
    }
}

void render_projectiles_on_field(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                                  int height, int width) {
    (void)height; (void)width;
    
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        if (g_projectiles[i].active) {
            int x = g_projectiles[i].x, y = g_projectiles[i].y;
            if (x >= 0 && x < MAX_FIELD_WIDTH && y >= 0 && y < MAX_FIELD_HEIGHT) {
                field[y][x] = SYMBOL_PROJECTILE;
            }
        }
    }
}

bool projectile_hits(const Projectile& proj, int target_x, int target_y) {
    return proj.active && proj.x == target_x && proj.y == target_y;
}

Projectile* get_active_projectile(int index) {
    int count = 0;
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        if (g_projectiles[i].active) {
            if (count == index) return &g_projectiles[i];
            ++count;
        }
    }
    return nullptr;
}
