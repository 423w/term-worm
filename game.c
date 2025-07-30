#include "game.h"

void init_game(GameState *game) {
    srand(time(NULL));
    
    // Initialize player
    init_player(&game->player);
    
    // Initialize platforms
    init_platforms(game->platforms);
    
    // Initialize game state
    game->score = 0;
    game->game_over = 0;
    game->camera_x = 0;
    game->platforms_jumped = 0;
}

void update_game(GameState *game) {
    // Move camera forward (auto-scrolling) - faster now
    game->camera_x += 2;
    
    // Update player
    update_player(&game->player, game->platforms, game->camera_x);
    
    // Check for platform landing
    if (check_platform_landing(&game->player, game->platforms, game->camera_x)) {
        game->platforms_jumped++;
    }
    
    // Update platforms
    update_platforms(game->platforms, game->camera_x);
    
    // Check if player fell off screen
    if (game->player.y > SCREEN_HEIGHT) {
        game->game_over = 1;
    }
    
    // Check if player fell into a gap
    if (game->player.y > GROUND_LEVEL + 1) {
        game->game_over = 1;
    }
    
    // Update score based on distance traveled and platforms jumped
    game->score = (game->camera_x / 10) + (game->platforms_jumped * 10);
}

void render_game(GameState *game) {
    // Render platforms
    render_platforms(game->platforms, game->camera_x);
    
    // Render player
    render_player(&game->player, game->camera_x);
    
    // Render UI
    mvprintw(0, 0, "Score: %d", game->score);
    mvprintw(0, 20, "Platforms: %d", game->platforms_jumped);
    mvprintw(1, 0, "Press SPACE to jump, Q to quit");
    
    // Render ground line
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        mvaddch(GROUND_LEVEL + 1, x, '-');
    }
}

void handle_input(GameState *game, int ch) {
    if (ch == ' ' || ch == KEY_UP) {
        // Jump if on ground
        if (game->player.on_ground) {
            game->player.vel_y = JUMP_STRENGTH;
            game->player.on_ground = 0;
        }
    }
}

void cleanup_game(void) {
    // Any cleanup needed
} 