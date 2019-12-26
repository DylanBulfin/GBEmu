#pragma once

#include <SDL2/SDL.h>

typedef struct button_file{
  uint8_t a:1;
  uint8_t b:1;
  uint8_t start:1;
  uint8_t select:1;
  uint8_t up:1;
  uint8_t down:1;
  uint8_t left:1;
  uint8_t right:1;
} buttons_t;

extern SDL_Event event;
extern buttons_t buttons;
extern uint8_t joypad_signal;

void print_buttons();
void handle_input(register_file_t*);
void wait_for_valid_button_press(register_file_t*);

#define DIR_SELECTED (!((MEM(P1)>>4)&0x1))
#define BUT_SELECTED (!((MEM(P1)>>5)&0x1))

#define DOWN_MASK   (~(0x08))
#define UP_MASK     (~(0x04))
#define LEFT_MASK   (~(0x02))
#define RIGHT_MASK  (~(0x01))
#define START_MASK  (~(0x08))
#define SELECT_MASK (~(0x04))
#define B_MASK      (~(0x02))
#define A_MASK      (~(0x01))
