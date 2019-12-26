#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "graphics.h"
#include "../settings.h"

uint32_t COLORS[4];// = COLOR_MODE ? {0x777777, 0x6c6c6c, 0x404040, 0x1c1c1c} : {0x9bbc0f, 0x8bac0f, 0x306230, 0x0f380f};
SDL_Window *window = NULL;
uint8_t *pixel_codes = NULL;
uint32_t *pixels = NULL;
uint32_t *background = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

int draw_next_frame = -1;

void setup_display() {
  pixels = malloc(SCREEN_PIXELS * sizeof(uint32_t));
  pixel_codes = malloc(SCREEN_PIXELS * sizeof(uint8_t));
  background = malloc(256 * 256 * sizeof(uint32_t));
  //    COLORS = {0x9bbc0f, 0x8bac0f, 0x306230, 0x0f380f};
  //COLORS = malloc(4 * sizeof(uint32_t));
  if(COLOR_MODE == 1) {
    COLORS[0] = 0xffffff;
    COLORS[1] = 0xa9a9a9;
    COLORS[2] = 0x545454;
    COLORS[3] = 0x000000;
  } else if(COLOR_MODE == 0){
    COLORS[0] = 0x9bbc0f;
    COLORS[1] = 0x8bac0f;
    COLORS[2] = 0x306230;
    COLORS[3] = 0x0f380f;
  }
  SDL_Init(SDL_INIT_VIDEO);
    
  window = SDL_CreateWindow("Gameboy Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

  draw_next_frame = 0;
}

void draw_pixels_to_screen() {
  SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void clear_screen() {
  for(int i = 0; i < SCREEN_PIXELS; i++) {
    pixels[i] = COLORS[0];
  }
  draw_pixels_to_screen();
}
