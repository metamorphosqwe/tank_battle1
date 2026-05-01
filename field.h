// ===== field.h =====
#ifndef FIELD_H
#define FIELD_H

#include "game_constants.h"

struct GameField {
    char data[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH];
    int height;
    int width;
};

void init_field(GameField& field, int height, int width);
void load_level(GameField& field, const LevelConfig& config);
void render_field(const GameField& field);
void clear_screen();
bool is_wall(const GameField& field, int x, int y);
char get_field_symbol(const GameField& field, int x, int y);

#endif
