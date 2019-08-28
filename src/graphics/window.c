#include <stdio.h>
#include <SDL2/SDL.h>
#include "../cpu/internal.h"
#include "../cpu/operations.h"
#include "graphics.h"

void update_window(register_file_t *state) {
    if(!draw_next_frame || !BG_WINDOW_ENABLE || !WINDOW_ENABLE) {
	return;
    }

    if(MEM(LY) < WINDOW_Y) {
	return;
    }

    if(MEM(WX) < 0 || MEM(WX) > 166 || MEM(WY) < 0 || MEM(WY) > 143) {
	return;
    }

    if(BG_ADDRESS_MODE == 1) {
	//treats background as table of 32x32 tiles 
	uint8_t row = (MEM(LY) - WINDOW_Y) / TILE_HEIGHT_PIXELS;
	
	uint16_t tile_addr = WINDOW_TILEMAP_ADDR + (row * BACKGROUND_WIDTH_TILES);

	uint8_t tile_num = MEM(tile_addr);

	uint8_t y_line = (MEM(LY) - WINDOW_Y) % TILE_HEIGHT_PIXELS;

	uint16_t tile_data_addr = TILE_DATA_ADDRESS1 + (tile_num * TILE_SIZE_BYTES) + (y_line * TILE_LINE_SIZE_BYTES);

	for(uint8_t x_pos = WINDOW_X; x_pos < SCREEN_WIDTH; x_pos++) {
	    if(x_pos != WINDOW_X && (x_pos % TILE_WIDTH_PIXELS) == 0) {
		tile_addr++;
		tile_num = MEM(tile_addr);
		tile_data_addr = TILE_DATA_ADDRESS1 + (tile_num * TILE_SIZE_BYTES) + (y_line * TILE_LINE_SIZE_BYTES);
	    }

	    uint8_t color_index = COLOR_INDEX(tile_data_addr,x_pos);

	    pixel_codes[(MEM(LY) * SCREEN_WIDTH) + x_pos] = color_index;
	    pixels[(MEM(LY) * SCREEN_WIDTH) + x_pos] = BG_COLOR_RGB(color_index);
	}
    }
    else {
	uint8_t row = (MEM(LY) - WINDOW_Y) / TILE_HEIGHT_PIXELS;
	
	uint16_t tile_addr = WINDOW_TILEMAP_ADDR + (row * BACKGROUND_WIDTH_TILES);

	uint8_t tile_num = MEM(tile_addr);

	uint8_t y_line = (MEM(LY) - WINDOW_Y) % TILE_HEIGHT_PIXELS;

	uint16_t tile_data_addr = 0x0000;

	if(tile_num < 0x80) {
	    tile_data_addr = TILE_DATA_ADDRESS0 + (tile_num * TILE_SIZE_BYTES)
		+ (y_line * TILE_LINE_SIZE_BYTES);
	} else {
	    uint8_t tile_num_tc = TC(tile_num);
	    tile_data_addr = TILE_DATA_ADDRESS0 - (tile_num_tc * TILE_SIZE_BYTES)
		+ (y_line * TILE_LINE_SIZE_BYTES);
	}

	for(uint8_t x_pos = WINDOW_X; x_pos < SCREEN_WIDTH; x_pos++) {
	    if(x_pos != WINDOW_X && (x_pos % TILE_WIDTH_PIXELS) == 0) {
		tile_addr++;
		tile_num = MEM(tile_addr);
		if(tile_num < 0x80) {
		    tile_data_addr = TILE_DATA_ADDRESS0 + (tile_num * TILE_SIZE_BYTES)
			+ (y_line * TILE_LINE_SIZE_BYTES);
		} else {
		    uint8_t tile_num_tc = TC(tile_num);
		    tile_data_addr = TILE_DATA_ADDRESS0 - (tile_num_tc * TILE_SIZE_BYTES)
			+ (y_line * TILE_LINE_SIZE_BYTES);
		}
	    }

	    uint8_t color_index = COLOR_INDEX(tile_data_addr,x_pos);

	    pixel_codes[(MEM(LY) * SCREEN_WIDTH) + x_pos] = color_index;
	    pixels[(MEM(LY) * SCREEN_WIDTH) + x_pos] = BG_COLOR_RGB(color_index);
	}
    }
}
