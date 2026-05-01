// ===== projectile.h =====
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_constants.h"

struct Projectile {
    int x, y;
    Direction dir;
    bool active;
};

extern Projectile g_projectiles[MAX_PROJECTILES];
extern int g_projectile_count;

void init_projectiles();
bool create_projectile(int x, int y, Direction dir);
void update_projectiles(int field_height, int field_width);
void render_projectiles_on_field(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                                  int height, int width);
bool projectile_hits(const Projectile& proj, int target_x, int target_y);
Projectile* get_active_projectile(int index);

#endif
