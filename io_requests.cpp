// ===== io_requests.cpp =====
#include "io_requests.h"
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

void print_welcome_message() {
    std::cout << "============================================" << std::endl;
    std::cout << "       ДОБРО ПОЖАЛОВАТЬ В TANK BATTLE!      " << std::endl;
    std::cout << "============================================" << std::endl;
}

void print_error_message(const char* message) {
    std::cout << "[ОШИБКА] " << message << std::endl;
}

void print_game_status(int level, int enemies_remaining, bool player_alive) {
    std::cout << "Уровень: " << level 
              << " | Врагов: " << enemies_remaining
              << " | Статус: " << (player_alive ? "В ИГРЕ" : "УНИЧТОЖЕН")
              << std::endl;
}

bool request_confirmation(const char* prompt) {
    std::cout << prompt << " (y/n): ";
    
    char ch;
#ifdef _WIN32
    ch = _getch();
    std::cout << ch << std::endl;
#else
    std::cin >> ch;
#endif
    
    return (ch == 'y' || ch == 'Y');
}

int read_integer_input(int min_val, int max_val) {
    int value = 0;
    bool valid = false;
    
    while (!valid) {
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод! Введите число: ";
        } else if (value < min_val || value > max_val) {
            std::cout << "Число должно быть от " << min_val 
                      << " до " << max_val << ": ";
        } else {
            valid = true;
            std::cin.ignore(10000, '\n');
        }
    }
    
    return value;
}

void wait_for_keypress() {
    std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
    
#ifdef _WIN32
    _getch();
#else

#endif
}

void print_victory_message(int level) {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "           ПОБЕДА!                      " << std::endl;
    std::cout << "   Уровень " << level << " пройден успешно!          " << std::endl;
    std::cout << "   Все враги уничтожены!              " << std::endl;
    std::cout << "========================================" << std::endl;
}

void print_defeat_message() {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "           ПОРАЖЕНИЕ!                   " << std::endl;
    std::cout << "   Ваш танк был уничтожен!            " << std::endl;
    std::cout << "   Попробуйте еще раз!                " << std::endl;
    std::cout << "========================================" << std::endl;
}

void print_controls_help() {
    std::cout << std::endl;
    std::cout << "=== УПРАВЛЕНИЕ ===" << std::endl;
    std::cout << "  W / Стрелка вверх    - Движение вверх" << std::endl;
    std::cout << "  S / Стрелка вниз     - Движение вниз" << std::endl;
    std::cout << "  A / Стрелка влево    - Движение влево" << std::endl;
    std::cout << "  D / Стрелка вправо   - Движение вправо" << std::endl;
    std::cout << "  Пробел               - Выстрел" << std::endl;
    std::cout << "  ESC / 0 в меню       - Выход" << std::endl;
    std::cout << std::endl;
}
