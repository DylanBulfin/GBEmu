#pragma once

#include <SDL2/SDL.h>

void load_settings();

extern uint8_t real_time;

extern uint16_t window_width;
extern uint16_t window_height;

extern char *game_directory;
extern char *save_directory;
extern int8_t load_save_file;

extern SDL_Keycode a_key;
extern SDL_Keycode b_key;
extern SDL_Keycode start_key;
extern SDL_Keycode select_key;
extern SDL_Keycode up_key;
extern SDL_Keycode down_key;
extern SDL_Keycode left_key;
extern SDL_Keycode right_key;

extern SDL_GameControllerButton jp_a;
extern SDL_GameControllerButton jp_b;
extern SDL_GameControllerButton jp_start;
extern SDL_GameControllerButton jp_select;
extern SDL_GameControllerButton jp_up;
extern SDL_GameControllerButton jp_down;
extern SDL_GameControllerButton jp_left;
extern SDL_GameControllerButton jp_right;

extern int8_t color_mode;

#define REAL_TIME            real_time

#define WINDOW_WIDTH         window_width
#define WINDOW_HEIGHT        window_height

#define GAME_DIR             game_directory
#define SAVE_DIR             save_directory
#define LOAD_SAVE            load_save_file

#define A_KEY                a_key
#define B_KEY                b_key
#define START_KEY            start_key
#define SELECT_KEY           select_key 
#define UP_KEY               up_key
#define DOWN_KEY             down_key
#define LEFT_KEY             left_key
#define RIGHT_KEY            right_key

#define JOYPAD_A_BUTTON      jp_a
#define JOYPAD_B_BUTTON      jp_b
#define JOYPAD_START_BUTTON  jp_start
#define JOYPAD_SELECT_BUTTON jp_select
#define JOYPAD_UP_BUTTON     jp_up
#define JOYPAD_DOWN_BUTTON   jp_down
#define JOYPAD_LEFT_BUTTON   jp_left
#define JOYPAD_RIGHT_BUTTON  jp_right

#define COLOR_MODE           color_mode
