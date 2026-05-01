// ===== main.cpp =====
#include "menu.h"
#include "game_state.h"

int main() {
    GameSession session;
    init_game_session(session);
    run_main_menu(session);
    return 0;
}
