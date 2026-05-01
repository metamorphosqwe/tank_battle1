// ===== enemy.cpp =====
#include "enemy.h"
#include "projectile.h"
#include <cstdlib>
#include <ctime>

Enemy g_enemies[MAX_ENEMIES];
int g_enemy_count = 0;
static bool g_random_initialized = false;

void init_enemies() {
    g_enemy_count = 0;
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        g_enemies[i].active = false;
        g_enemies[i].x = 0;
        g_enemies[i].y = 0;
        g_enemies[i].dir = Direction::NONE;
        g_enemies[i].move_timer = 0;
        g_enemies[i].shoot_timer = 0;
    }
    g_random_initialized = false;
}

bool add_enemy(int x, int y) {
    if (g_enemy_count >= MAX_ENEMIES) return false;
    
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (!g_enemies[i].active) {
            g_enemies[i].x = x;
            g_enemies[i].y = y;
            g_enemies[i].dir = Direction::NONE;
            g_enemies[i].active = true;
            g_enemies[i].move_timer = 0;
            g_enemies[i].shoot_timer = 0;
            ++g_enemy_count;
            return true;
        }
    }
    return false;
}

Direction generate_random_direction() {
    if (!g_random_initialized) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        g_random_initialized = true;
    }
    
    switch (std::rand() % 4) {
        case 0: return Direction::UP;
        case 1: return Direction::DOWN;
        case 2: return Direction::LEFT;
        case 3: return Direction::RIGHT;
        default: return Direction::NONE;
    }
}

void update_enemies(int field_height, int field_width,
                    char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH]) {
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active) {
            Enemy& enemy = g_enemies[i];
            enemy.move_timer++;
            enemy.shoot_timer++;
            
            if (enemy.move_timer >= 5) {
                enemy.move_timer = 0;
                
                if (std::rand() % 100 < 30 || enemy.dir == Direction::NONE) {
                    enemy.dir = generate_random_direction();
                }
                
                int new_x = enemy.x, new_y = enemy.y;
                
                switch (enemy.dir) {
                    case Direction::UP: new_y--; break;
                    case Direction::DOWN: new_y++; break;
                    case Direction::LEFT: new_x--; break;
                    case Direction::RIGHT: new_x++; break;
                    default: break;
                }
                
                if (new_x >= 0 && new_x < field_width &&
                    new_y >= 0 && new_y < field_height &&
                    field[new_y][new_x] != SYMBOL_WALL) {
                    enemy.x = new_x;
                    enemy.y = new_y;
                } else {
                    enemy.dir = generate_random_direction();
                }
            }
            
            if (enemy.shoot_timer >= 10 + (std::rand() % 10)) {
                enemy.shoot_timer = 0;
                Direction shoot_dir = enemy.dir;
                if (shoot_dir == Direction::NONE) {
                    shoot_dir = generate_random_direction();
                }
                create_projectile(enemy.x, enemy.y, shoot_dir);
            }
        }
    }
}

void render_enemies_on_field(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                              int height, int width) {
    (void)height; (void)width;
    
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active) {
            int x = g_enemies[i].x, y = g_enemies[i].y;
            if (x >= 0 && x < MAX_FIELD_WIDTH && y >= 0 && y < MAX_FIELD_HEIGHT) {
                field[y][x] = SYMBOL_ENEMY;
            }
        }
    }
}

bool enemy_hit(int x, int y) {
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active && g_enemies[i].x == x && g_enemies[i].y == y) {
            g_enemies[i].active = false;
            --g_enemy_count;
            return true;
        }
    }
    return false;
}

Enemy* get_active_enemy(int index) {
    int count = 0;
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active) {
            if (count == index) return &g_enemies[i];
            ++count;
        }
    }
    return nullptr;
}

int count_active_enemies() {
    int count = 0;
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active) ++count;
    }
    return count;
}
