// ===== io_requests.h =====
#ifndef IO_REQUESTS_H
#define IO_REQUESTS_H

#include "game_constants.h"
#include "field.h"

// Модуль процедур пользовательского ввода-вывода
// Согласно п.2 условий задания - реализация пользовательских запросов

// Вывод приветственного сообщения
void print_welcome_message();

// Вывод сообщения об ошибке
void print_error_message(const char* message);

// Вывод игрового статуса (счет, уровень и т.д.)
void print_game_status(int level, int enemies_remaining, bool player_alive);

// Запрос подтверждения действия
bool request_confirmation(const char* prompt);

// Ввод числа с клавиатуры (для меню)
int read_integer_input(int min_val, int max_val);

// Ожидание нажатия клавиши пользователем
void wait_for_keypress();

// Вывод сообщения о победе
void print_victory_message(int level);

// Вывод сообщения о поражении
void print_defeat_message();

// Вывод инструкции по управлению
void print_controls_help();

#endif // IO_REQUESTS_H
