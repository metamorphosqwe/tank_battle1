// ===== game_state.cpp =====
#include "game_state.h"
#include "field.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "collision.h"
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

static const LevelConfig g_level_configs[MAX_LEVELS] = {

    // Уровень 1: Маленькое поле, 2 врага, простые стены
    {
        10, 20, 2,  // height, width, enemy_count
        2, 7,       // player_start_x, player_start_y
        {5, 15},    // enemy_start_x
        {3, 3},     // enemy_start_y
        {
            "####################",
            "#                  #",
            "#  W               #",
            "#         ##       #",
            "#T               W #",
            "#         ##       #",
            "#                  #",
            "#                  #",
            "#                  #",
            "####################"
        }
    },
    // Уровень 2: Среднее поле, 4 врага, больше стен
    {
        15, 30, 4,
        2, 7,
        {5, 25, 15, 25},
        {3, 3, 10, 12},
        {
            "##############################",
            "#                            #",
            "#  W      ####       W       #",
            "#         #  #               #",
            "#  ####   #  #   ####        #",
            "#T #  #       #   #  #   W   #",
            "#  #  #       #   #  #       #",
            "#  ####   ####    ####       #",
            "#                   #        #",
            "#  W     ####      ###   W   #",
            "#         #  #      #        #",
            "#  ########  ########        #",
            "#                            #",
            "#                            #",
            "##############################"
        }
    },
    // Уровень 3: Большое поле, 6 врагов, сложный лабиринт
    {
        20, 40, 6,
        2, 10,
        {5, 35, 20, 35, 10, 30},
        {3, 3, 5, 15, 17, 17},
        {
            "########################################",
            "#                                      #",
            "#  W   ####      ####      ####   W    #",
            "#      #  #      #  #      #  #        #",
            "#  #####  #      #  ########  #####    #",
            "#                                   W  #",
            "#     ####  ######  ##        #######  #",
            "#     #  #       #  ##     #  #     #  #",
            "#  ####  #       #  ##  ####  #  #  #  #",
            "#T #     #       #         #     #  #  #",
            "#  #     #       #####     #######  #  #",
            "#  #                       #           #",
            "#  ####  ##########  ####  #     ##### #",
            "#        #              #  #        #  #",
            "#  #######  #  #  #######  #######  #  #",
            "#  #        #  #                    #  #",
            "#W #  #######  ###############      #  #",
            "#                                 W    #",
            "#  ##########               ########   #",
            "########################################"
        }
    }
};

void init_game_session(GameSession& session) {
    session.state = GameState::MENU;
    session.current_level = 0;
    session.game_running = false;
    init_field(session.field, MAX_FIELD_HEIGHT, MAX_FIELD_WIDTH);
}

bool start_level(GameSession& session, int level_index) {
    if (level_index < 0 || level_index >= MAX_LEVELS) return false;
    
    init_projectiles();
    init_enemies();
    load_level(session.field, g_level_configs[level_index]);
    session.current_level = level_index;
    
    init_player(g_level_configs[level_index].player_start_x,
                g_level_configs[level_index].player_start_y);
    
    for (int i = 0; i < g_level_configs[level_index].enemy_count; ++i) {
        add_enemy(g_level_configs[level_index].enemy_start_x[i],
                  g_level_configs[level_index].enemy_start_y[i]);
    }
    
    session.state = GameState::PLAYING;
    session.game_running = true;
    return true;
}

GameState check_game_condition(const GameSession& session) {
    (void)session;
    const Player& player = get_player();
    
    if (!player.alive) return GameState::LOSE;
    if (count_active_enemies() == 0) return GameState::WIN;
    return GameState::PLAYING;
}

void handle_game_over(GameSession& session, GameState end_state) {
    clear_screen();
    std::cout << "\n========================================\n";
    
    if (end_state == GameState::WIN)
        std::cout << "           ПОБЕДА! ВРАГИ УНИЧТОЖЕНЫ!\n";
    else if (end_state == GameState::LOSE)
        std::cout << "           ПОРАЖЕНИЕ! ТАНК УНИЧТОЖЕН!\n";
    
    std::cout << "========================================\n\n";
    std::cout << "Нажмите любую клавишу для возврата в меню...\n";
    
#ifdef _WIN32
    _getch();
#else
    getchar();
#endif
    
    session.state = GameState::MENU;
    session.game_running = false;
}

void return_to_menu(GameSession& session) {
    session.state = GameState::MENU;
    session.game_running = false;
    reset_player();
    init_projectiles();
    init_enemies();
}

void run_game_loop(GameSession& session) {
    clear_screen();
    
    while (session.game_running && session.state == GameState::PLAYING) {
        std::cout << "\033[H" << std::flush;
        
        GameField render_field_data = session.field;
        render_projectiles_on_field(render_field_data.data, 
                                    render_field_data.height, 
                                    render_field_data.width);
        render_enemies_on_field(render_field_data.data,
                                render_field_data.height,
                                render_field_data.width);
        render_player_on_field(render_field_data.data,
                               render_field_data.height,
                               render_field_data.width);
        render_field(render_field_data);
        
        std::cout << "Уровень: " << (session.current_level + 1) 
                  << " | Врагов: " << count_active_enemies()
                  << " | WASD/стрелки - движение, Пробел - выстрел\n";
        
        handle_player_input(session.field.data, 
                           session.field.height, 
                           session.field.width);
        update_enemies(session.field.height, session.field.width, session.field.data);
        update_projectiles(session.field.height, session.field.width);
        process_all_collisions(session.field);
        
        GameState new_state = check_game_condition(session);
        if (new_state != GameState::PLAYING) {
            handle_game_over(session, new_state);
            break;
        }
        
#ifdef _WIN32
        Sleep(50);
#else
        usleep(50000);
#endif
    }
}
