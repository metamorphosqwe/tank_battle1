// ===== player.cpp =====
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include <cstdio>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

static Player g_player;

#ifndef _WIN32
static int kbhit_impl() {
    struct termios oldt, newt;
    int ch, oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

static int getch_impl() {
    struct termios oldt, newt;
    int ch;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}
#endif

void init_player(int start_x, int start_y) {
    g_player.x = start_x;
    g_player.y = start_y;
    g_player.last_dir = Direction::RIGHT;
    g_player.alive = true;
}

const Player& get_player() { return g_player; }

bool handle_player_input(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                         int field_height, int field_width) {
#ifdef _WIN32
    if (!_kbhit()) return false;
    int key = _getch();
    if (key == 224 || key == 0) key = _getch();
#else
    if (!kbhit_impl()) return false;
    int key = getch_impl();
#endif
    
    int new_x = g_player.x, new_y = g_player.y;
    Direction move_dir = Direction::NONE;
    
    switch (key) {
        case 'w': case 'W': case 'k': case 72:
            new_y--; move_dir = Direction::UP; break;
        case 's': case 'S': case 'j': case 80:
            new_y++; move_dir = Direction::DOWN; break;
        case 'a': case 'A': case 'h': case 75:
            new_x--; move_dir = Direction::LEFT; break;
        case 'd': case 'D': case 'l': case 77:
            new_x++; move_dir = Direction::RIGHT; break;
        case ' ':
            create_projectile(g_player.x, g_player.y, g_player.last_dir);
            return true;
        default:
            return false;
    }
    
    if (new_x < 0 || new_x >= field_width || new_y < 0 || new_y >= field_height)
        return false;
    if (field[new_y][new_x] == SYMBOL_WALL)
        return false;
    
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (g_enemies[i].active && g_enemies[i].x == new_x && g_enemies[i].y == new_y)
            return false;
    }
    
    g_player.x = new_x;
    g_player.y = new_y;
    if (move_dir != Direction::NONE)
        g_player.last_dir = move_dir;
    
    return false;
}

void render_player_on_field(char field[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH], 
                            int height, int width) {
    (void)height; (void)width;
    if (g_player.alive && g_player.x >= 0 && g_player.x < MAX_FIELD_WIDTH &&
        g_player.y >= 0 && g_player.y < MAX_FIELD_HEIGHT) {
        field[g_player.y][g_player.x] = SYMBOL_PLAYER;
    }
}

bool player_hit(int x, int y) {
    if (g_player.alive && g_player.x == x && g_player.y == y) {
        g_player.alive = false;
        return true;
    }
    return false;
}

void reset_player() {
    g_player.x = 0; g_player.y = 0;
    g_player.last_dir = Direction::NONE;
    g_player.alive = false;
}
