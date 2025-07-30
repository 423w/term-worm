#include "game.h"

void init_player(Player *player) {
    player->x = 10.0f;
    player->y = GROUND_LEVEL;
    player->vel_y = 0.0f;
    player->on_ground = 1;
    player->width = 1;
    player->height = 1;
}

void update_player(Player *player, Platform platforms[], int camera_x) {
    // Keep player moving forward with the camera to maintain screen position
    player->x = camera_x + 10.0f;
    
    // Always apply gravity - player must be supported by a platform to stay up
    player->vel_y += GRAVITY;
    
    // Update vertical position
    player->y += player->vel_y;
    
    // Check collision with platforms
    player->on_ground = check_collision(player, platforms, camera_x);
    
    // REMOVED: No automatic ground landing - let player fall through gaps
    
    // Limit jump velocity
    if (player->vel_y < -3.0f) {
        player->vel_y = -3.0f;
    }
    if (player->vel_y > 5.0f) {
        player->vel_y = 5.0f;
    }
}

void render_player(Player *player, int camera_x) {
    int screen_x = (int)(player->x - camera_x);
    int screen_y = (int)(player->y);
    
    // Only render if player is on screen
    if (screen_x >= 0 && screen_x < SCREEN_WIDTH && 
        screen_y >= 0 && screen_y < SCREEN_HEIGHT) {
        mvaddch(screen_y, screen_x, PLAYER_CHAR);
    }
}

int check_collision(Player *player, Platform platforms[], int camera_x) {
    (void)camera_x; // Suppress unused parameter warning
    int player_bottom = (int)(player->y + player->height);
    
    // Check collision with each platform
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        if (!platforms[i].active) continue;
        
        int platform_left = platforms[i].x;
        int platform_right = platforms[i].x + platforms[i].width;
        int platform_top = platforms[i].y;
        
        // Only allow landing if player is falling down onto the platform
        // AND the player's center is actually over the platform
        int player_center_x = (int)(player->x + player->width / 2);
        
        if (player->vel_y >= 0 && 
            player_bottom >= platform_top && 
            player_bottom <= platform_top + 2 &&
            player_center_x >= platform_left && 
            player_center_x < platform_right) {
            
            player->y = platform_top - player->height;
            player->vel_y = 0.0f;
            return 1;  // On ground
        }
    }
    
    return 0;  // Not on ground
}

int check_platform_landing(Player *player, Platform platforms[], int camera_x) {
    static int last_platform_x = -1;
    (void)camera_x; // Suppress unused parameter warning
    
    if (!player->on_ground) {
        last_platform_x = -1;  // Reset when airborne
        return 0;
    }
    
    // Check which platform the player is on
    int player_bottom = (int)(player->y + player->height);
    int player_left = (int)(player->x);
    int player_right = (int)(player->x + player->width);
    
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        if (!platforms[i].active) continue;
        
        int platform_left = platforms[i].x;
        int platform_right = platforms[i].x + platforms[i].width;
        int platform_top = platforms[i].y;
        
        // Check if player is on this platform
        if (player_bottom >= platform_top && 
            player_bottom <= platform_top + 2 &&
            player_right > platform_left && 
            player_left < platform_right) {
            
            // Count as a successful jump if this is a new platform (different x position)
            if (last_platform_x != -1 && platform_left > last_platform_x + 5) {
                last_platform_x = platform_left;
                return 1;
            }
            
            // Update last platform position
            if (last_platform_x == -1) {
                last_platform_x = platform_left;
            }
            return 0;
        }
    }
    
    return 0;
} 