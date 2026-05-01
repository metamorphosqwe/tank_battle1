// ===== game_constants.h =====
#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <cstdint>

// Константы размеров поля (максимальные)
constexpr int MAX_FIELD_HEIGHT = 25;
constexpr int MAX_FIELD_WIDTH = 80;
constexpr int MAX_PROJECTILES = 50;
constexpr int MAX_ENEMIES = 10;
constexpr int MAX_LEVELS = 3;

// Символы игрового поля
constexpr char SYMBOL_PLAYER = 'T';
constexpr char SYMBOL_ENEMY = 'W';
constexpr char SYMBOL_WALL = '#';
constexpr char SYMBOL_PROJECTILE = '*';
constexpr char SYMBOL_EMPTY = ' ';

// Направления движения
enum class Direction : int8_t {
    NONE = 0,
    UP = -1,
    DOWN = 1,
    LEFT = -2,
    RIGHT = 2
};

// Состояния игры
enum class GameState {
    MENU,
    PLAYING,
    WIN,
    LOSE
};

// Конфигурация уровня
struct LevelConfig {
    int height;
    int width;
    int enemy_count;
    int player_start_x;
    int player_start_y;
    // Массивы позиций врагов и стен для уровня
    int enemy_start_x[MAX_ENEMIES];
    int enemy_start_y[MAX_ENEMIES];
    // Карта стен (упрощенно - строки с позициями стен)
    char map_data[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH];
};

#endif // GAME_CONSTANTS_H
