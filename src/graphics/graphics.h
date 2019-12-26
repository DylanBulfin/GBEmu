#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include "../cpu/internal.h"


//Constants
#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 144
#define SCREEN_PIXELS 23040
#define BACKGROUND_WIDTH_PIXELS 256
#define BACKGROUND_HEIGHT_PIXELS 256
#define BACKGROUND_WIDTH_TILES 32
#define TILE_SIZE_BYTES 16
#define TILE_LINE_SIZE_BYTES 2
#define TILE_WIDTH_PIXELS 8
#define TILE_HEIGHT_PIXELS 8
#define TILE_DATA_ADDRESS1 0x8000
#define TILE_DATA_ADDRESS0 0x9000
#define TILE_DATA_ADDRESS0_TC 0x8800

//LCDC bits
#define BG_WINDOW_ENABLE (MEM(LCDC)&0x1)
#define SPRITE_ENABLE ((MEM(LCDC)>>1)&0x1)
#define SPRITE_SIZE_CODE ((MEM(LCDC)>>2)&0x1)
#define BG_TILEMAP ((MEM(LCDC)>>3)&0x1)
#define BG_ADDRESS_MODE ((MEM(LCDC)>>4)&0x1)
#define WINDOW_ENABLE ((MEM(LCDC)>>5)&0x1)
#define WINDOW_TILEMAP ((MEM(LCDC)>>6)&0x1)
#define LCD_ENABLE ((MEM(LCDC)>>7)&0x1)

//Sprite control bits
#define SPRITE_PRIORITY    ((control>>7)&0x1)
#define SPRITE_Y_FLIP      ((control>>6)&0x1)
#define SPRITE_X_FLIP      ((control>>5)&0x1)
#define SPRITE_PALETTE_NUM ((control>>4)&0x1)

//Helper Macros
#define BG_TILEMAP_ADDR ((BG_TILEMAP) ? (0x9c00) : (0x9800))
#define COLOR_INDEX(lineaddr,xpixel) ((((MEM(lineaddr + 1) >> (7 - (xpixel % 8))) & 0x1) << 1) + ((MEM(lineaddr) >> (7 - (xpixel % 8))) & 0x1))
#define BG_COLOR_RGB(index) COLORS[(MEM(BGP) >> (2 * index)) & 0x3]

#define SPRITE_SIZE (SPRITE_SIZE_CODE ? 16 : 8)
#define SPRITE(num) &MEM(0xfe00+(4*num))
#define SPRITE_Y    (sprite[0] - 16)
#define SPRITE_X    (sprite[1] - 8)

#define SPRITE_PALETTE_ADDR ((SPRITE_PALETTE_NUM)?OBP1:OBP0)
#define SPRITE_COLOR_CODE(index,palette_addr) ((MEM(palette_addr) >> (2 * index)) & 0x3)

#define WINDOW_TILEMAP_ADDR ((WINDOW_TILEMAP) ? (0x9c00) : (0x9800))
#define WINDOW_X (MEM(WX) > 7 ? (MEM(WX)-7) : 0)
#define WINDOW_Y (MEM(WY))

void setup_display();
void update_background(register_file_t*);
void update_window(register_file_t *state);
void update_sprites(register_file_t*);
void draw_pixels_to_screen();
void clear_screen();

extern uint32_t COLORS[];
extern uint32_t *pixels;
extern uint8_t *pixel_codes;
extern uint32_t *background;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;


//Control variables
extern int draw_next_frame;
