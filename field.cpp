// ===== field.cpp =====
#include "field.h"
#include <iostream>
#include <cstring>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void init_field(GameField& field, int height, int width) {
    field.height = height;
    field.width = width;
    
    for (int y = 0; y < MAX_FIELD_HEIGHT; ++y) {
        for (int x = 0; x < MAX_FIELD_WIDTH; ++x) {
            field.data[y][x] = SYMBOL_EMPTY;
        }
    }
}

void load_level(GameField& field, const LevelConfig& config) {
    init_field(field, config.height, config.width);
    
    for (int y = 0; y < config.height && y < MAX_FIELD_HEIGHT; ++y) {
        for (int x = 0; x < config.width && x < MAX_FIELD_WIDTH; ++x) {
            if (config.map_data[y][x] == SYMBOL_WALL) {
                field.data[y][x] = SYMBOL_WALL;
            } else {
                field.data[y][x] = SYMBOL_EMPTY;
            }
        }
    }
}

void render_field(const GameField& field) {
    std::ostringstream buffer;
    buffer << "\033[H";
    buffer << "+";
    for (int x = 0; x < field.width; ++x) buffer << "-";
    buffer << "+\n";
    
    for (int y = 0; y < field.height; ++y) {
        buffer << "|";
        for (int x = 0; x < field.width; ++x) buffer << field.data[y][x];
        buffer << "|\n";
    }
    
    buffer << "+";
    for (int x = 0; x < field.width; ++x) buffer << "-";
    buffer << "+\n";
    
    std::cout << buffer.str() << std::flush;
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H" << std::flush;
#endif
}

bool is_wall(const GameField& field, int x, int y) {
    if (x < 0 || x >= field.width || y < 0 || y >= field.height) return true;
    return field.data[y][x] == SYMBOL_WALL;
}

char get_field_symbol(const GameField& field, int x, int y) {
    if (x < 0 || x >= field.width || y < 0 || y >= field.height) return SYMBOL_WALL;
    return field.data[y][x];
}
