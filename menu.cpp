// ===== menu.cpp =====
#include "menu.h"
#include "game_state.h"
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

void display_menu() {
    std::cout << "\n============================================\n";
    std::cout << "              TANK BATTLE GAME              \n";
    std::cout << "============================================\n\n";
    std::cout << "  1. Уровень 1 - Легкий (2 врага)\n";
    std::cout << "  2. Уровень 2 - Средний (4 врага)\n";
    std::cout << "  3. Уровень 3 - Сложный (6 врагов)\n";
    std::cout << "  0. Выход из игры\n\n";
    std::cout << "  Управление: WASD/стрелки - движение, Пробел - выстрел\n\n";
    std::cout << "  Символы: T - игрок, W - враг, # - стена, * - снаряд\n\n";
    std::cout << "============================================\n";
    std::cout << "  Выберите уровень (0-3): ";
}

int get_menu_choice() {
    int choice = 0;
    
#ifdef _WIN32
    char ch;
    do {
        ch = _getch();
        if (ch >= '0' && ch <= '3') {
            choice = ch - '0';
            std::cout << ch << '\n';
            break;
        }
    } while (ch != 27);
#else
    std::cin >> choice;
    std::cin.ignore(10000, '\n');
#endif
    
    return choice;
}

void run_main_menu(GameSession& session) {
    bool exit_requested = false;
    
    while (!exit_requested) {
        clear_screen();
        display_menu();
        
        int choice = get_menu_choice();
        
        switch (choice) {
            case 1:
            case 2:
            case 3:
                if (start_level(session, choice - 1)) {
                    run_game_loop(session);
                }
                return_to_menu(session);
                break;
                
            case 0:
                exit_requested = true;
                std::cout << "\nСпасибо за игру!\n";
                break;
                
            default:
                std::cout << "\nНеверный выбор! Нажмите Enter...";
#ifdef _WIN32
                _getch();
#else
                std::cin.ignore(10000, '\n');
                getchar();
#endif
                break;
        }
    }
}
