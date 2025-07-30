#include "game.h"

void init_platforms(Platform platforms[]) {
    // Initialize all platforms as inactive
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        platforms[i].active = 0;
    }
    
    // Create starting solid platform
    platforms[0].active = 1;
    platforms[0].x = 0;
    platforms[0].y = GROUND_LEVEL;
    platforms[0].width = STARTING_PLATFORM_LENGTH;
    
    // Create subsequent platforms with gaps
    int current_x = STARTING_PLATFORM_LENGTH + GAP_MIN_WIDTH;
    for (int i = 1; i < 10 && i < MAX_PLATFORMS; i++) {
        platforms[i].active = 1;
        platforms[i].x = current_x;
        platforms[i].y = GROUND_LEVEL;
        
        // Random platform width
        platforms[i].width = PLATFORM_MIN_WIDTH + 
                            (rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH + 1));
        
        // Move to next platform position with a gap
        current_x += platforms[i].width;
        int gap_width = GAP_MIN_WIDTH + 
                       (rand() % (GAP_MAX_WIDTH - GAP_MIN_WIDTH + 1));
        current_x += gap_width;
    }
}

void update_platforms(Platform platforms[], int camera_x) {
    // Deactivate platforms that are too far behind
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        if (platforms[i].active && platforms[i].x + platforms[i].width < camera_x - 20) {
            platforms[i].active = 0;
        }
    }
    
    // Find the rightmost platform position
    int rightmost_x = camera_x + SCREEN_WIDTH;  // Start at visible edge
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        if (platforms[i].active) {
            int platform_right = platforms[i].x + platforms[i].width;
            if (platform_right > rightmost_x) {
                rightmost_x = platform_right;
            }
        }
    }
    
    // Generate new platforms one at a time
    if (rightmost_x < camera_x + SCREEN_WIDTH + 50) {
        // Find an inactive platform to reuse
        for (int i = 0; i < MAX_PLATFORMS; i++) {
            if (!platforms[i].active) {
                // Create new platform with proper gap
                platforms[i].active = 1;
                platforms[i].x = rightmost_x + GAP_MIN_WIDTH + (rand() % (GAP_MAX_WIDTH - GAP_MIN_WIDTH + 1));
                platforms[i].y = GROUND_LEVEL;
                platforms[i].width = PLATFORM_MIN_WIDTH + (rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH + 1));
                break;
            }
        }
    }
}

void render_platforms(Platform platforms[], int camera_x) {
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        if (!platforms[i].active) continue;
        
        // Calculate screen position
        int screen_start = platforms[i].x - camera_x;
        int screen_end = screen_start + platforms[i].width;
        
        // Only render if platform is visible on screen
        if (screen_end >= 0 && screen_start < SCREEN_WIDTH) {
            // Clamp to screen bounds
            int render_start = screen_start < 0 ? 0 : screen_start;
            int render_end = screen_end >= SCREEN_WIDTH ? SCREEN_WIDTH - 1 : screen_end;
            
            // Render platform
            for (int x = render_start; x < render_end; x++) {
                mvaddch(platforms[i].y, x, PLATFORM_CHAR);
            }
        }
    }
} 