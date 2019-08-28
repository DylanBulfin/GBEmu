#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "../timing/clock.h"
#include "../cpu/operations.h"

void update_background(register_file_t *state) {
    if(!draw_next_frame) {
	return;
    }
    if(!BG_WINDOW_ENABLE) {
	for(uint8_t pixel_count = 0; pixel_count < SCREEN_WIDTH; pixel_count++) {
	    pixels[(MEM(LY) * SCREEN_WIDTH) + pixel_count] = BG_COLOR_RGB(0);
	}
	return;
    }

    if(BG_ADDRESS_MODE == 1) {
	//treats background as table of 32x32 tiles 
	uint8_t row = ((MEM(SCY) + MEM(LY)) % BACKGROUND_HEIGHT_PIXELS) / TILE_HEIGHT_PIXELS;
	uint8_t column = (MEM(SCX) % BACKGROUND_WIDTH_PIXELS) / TILE_WIDTH_PIXELS;

	uint16_t tile_addr = BG_TILEMAP_ADDR + (row * BACKGROUND_WIDTH_TILES) + column;

	uint8_t tile_num = MEM(tile_addr);

	uint8_t y_line = ((MEM(SCY) + MEM(LY)) % TILE_HEIGHT_PIXELS);

	uint16_t tile_data_addr = TILE_DATA_ADDRESS1 + (tile_num * TILE_SIZE_BYTES) + (y_line * TILE_LINE_SIZE_BYTES);

	uint8_t has_wrapped_around = 0;
	
	for(uint8_t pixel_count = 0; pixel_count < SCREEN_WIDTH; pixel_count++) {
	    uint8_t xpos = ((MEM(SCX) + pixel_count) % BACKGROUND_WIDTH_PIXELS);
	    if(pixel_count != 0 && (xpos % TILE_WIDTH_PIXELS) == 0) {
		if((MEM(SCX) + pixel_count) >= BACKGROUND_WIDTH_PIXELS && !has_wrapped_around) {
		    tile_addr -= BACKGROUND_WIDTH_TILES;
		    has_wrapped_around = 1;
		}
		tile_addr++;
		tile_num = MEM(tile_addr);
		tile_data_addr = TILE_DATA_ADDRESS1 + (tile_num * TILE_SIZE_BYTES) + (y_line * TILE_LINE_SIZE_BYTES);
	    }

	    uint8_t color_index = COLOR_INDEX(tile_data_addr,xpos);
	    
	    pixel_codes[(MEM(LY) * SCREEN_WIDTH) + pixel_count] = color_index;
	    pixels[(MEM(LY) * SCREEN_WIDTH) + pixel_count] = BG_COLOR_RGB(color_index);
	}
    }
    else {
	if(!in_bios) {
	    //   printf("MODE 2\n");
	}
	uint8_t row = ((MEM(SCY) + MEM(LY)) % BACKGROUND_HEIGHT_PIXELS) / TILE_HEIGHT_PIXELS;
	uint8_t column = (MEM(SCX) % BACKGROUND_WIDTH_PIXELS) / TILE_WIDTH_PIXELS;

	uint16_t tile_addr = BG_TILEMAP_ADDR + (row * BACKGROUND_WIDTH_TILES) + column;

	uint8_t tile_num = MEM(tile_addr);

	uint8_t y_line = ((MEM(SCY) + MEM(LY)) % TILE_HEIGHT_PIXELS);

	uint16_t tile_data_addr = 0x0000;

	if(tile_num < 0x80) {
	    tile_data_addr = TILE_DATA_ADDRESS0 + (tile_num * TILE_SIZE_BYTES)
		+ (y_line * TILE_LINE_SIZE_BYTES);
	} else {
	    uint8_t tile_num_tc = TC(tile_num);
	    tile_data_addr = TILE_DATA_ADDRESS0 - (tile_num_tc * TILE_SIZE_BYTES)
		+ (y_line * TILE_LINE_SIZE_BYTES);
	}

	uint8_t has_wrapped_around = 0;

	for(uint8_t pixel_count = 0; pixel_count < SCREEN_WIDTH; pixel_count++) {
	    uint8_t xpos = ((MEM(SCX) + pixel_count) % BACKGROUND_WIDTH_PIXELS) ;
	    if(pixel_count != 0 && (xpos % TILE_WIDTH_PIXELS) == 0) {
		if((MEM(SCX) + pixel_count) >= BACKGROUND_WIDTH_PIXELS && !has_wrapped_around) {
		    tile_addr -= BACKGROUND_WIDTH_TILES;
		    has_wrapped_around = 1;
		}
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

	    uint8_t color_index = COLOR_INDEX(tile_data_addr,xpos);

	    pixel_codes[(MEM(LY) * SCREEN_WIDTH) + pixel_count] = color_index;
	    pixels[(MEM(LY) * SCREEN_WIDTH) + pixel_count] = BG_COLOR_RGB(color_index);
	}
    }
}
