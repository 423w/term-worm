#include "game.h"

int main() {
    GameState game;
    int ch;
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Initialize game
    init_game(&game);
    
    // Main game loop
    while (!game.game_over) {
        // Handle input
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        }
        handle_input(&game, ch);
        
        // Update game state
        update_game(&game);
        
        // Render game
        clear();
        render_game(&game);
        refresh();
        
        // Control game speed
        usleep(GAME_SPEED);
    }
    
    // Game over screen
    clear();
    mvprintw(SCREEN_HEIGHT/2, SCREEN_WIDTH/2 - 10, "GAME OVER!");
    mvprintw(SCREEN_HEIGHT/2 + 1, SCREEN_WIDTH/2 - 10, "Final Score: %d", game.score);
    mvprintw(SCREEN_HEIGHT/2 + 2, SCREEN_WIDTH/2 - 10, "Press any key to exit");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    
    // Cleanup
    cleanup_game();
    endwin();
    
    return 0;
} 