// ===== game_state.h =====
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "game_constants.h"
#include "field.h"

struct GameSession {
    GameState state;
    GameField field;
    int current_level;
    bool game_running;
};

void init_game_session(GameSession& session);
bool start_level(GameSession& session, int level_index);
void run_game_loop(GameSession& session);
GameState check_game_condition(const GameSession& session);
void handle_game_over(GameSession& session, GameState end_state);
void return_to_menu(GameSession& session);

#endif
