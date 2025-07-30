#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define GROUND_LEVEL (SCREEN_HEIGHT - 3)
#define MAX_PLATFORMS 20
#define PLATFORM_MIN_WIDTH 3
#define PLATFORM_MAX_WIDTH 8
#define GAP_MIN_WIDTH 4
#define GAP_MAX_WIDTH 8
#define PLAYER_CHAR '#'
#define PLATFORM_CHAR '='
#define GAME_SPEED 80000   // microseconds delay (faster game)
#define STARTING_PLATFORM_LENGTH 30  // Length of solid starting ground
#define JUMP_STRENGTH -1.2f
#define GRAVITY 0.15f

typedef struct {
    int x, y;
    int width;
    int active;
} Platform;

typedef struct {
    float x, y;
    float vel_y;
    int on_ground;
    int width, height;
} Player;

typedef struct {
    Player player;
    Platform platforms[MAX_PLATFORMS];
    int score;
    int game_over;
    int camera_x;
    int platforms_jumped;
} GameState;

// Function declarations
void init_game(GameState *game);
void update_game(GameState *game);
void render_game(GameState *game);
void handle_input(GameState *game, int ch);
void cleanup_game(void);

// Platform functions
void init_platforms(Platform platforms[]);
void update_platforms(Platform platforms[], int camera_x);
void render_platforms(Platform platforms[], int camera_x);

// Player functions
void init_player(Player *player);
void update_player(Player *player, Platform platforms[], int camera_x);
void render_player(Player *player, int camera_x);
int check_collision(Player *player, Platform platforms[], int camera_x);
int check_platform_landing(Player *player, Platform platforms[], int camera_x);

#endif 