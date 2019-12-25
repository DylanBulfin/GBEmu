#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "clock.h"
#include "waiting.h"
#include "../interrupts/interrupts.h"
#include "../graphics/graphics.h"
#include "../input/input.h"
#include "../settings.h"

#define SCANLINE_LENGTH 456

#define STAT_HBLANK         0
#define STAT_VBLANK         1
#define STAT_SPRITE_SEARCH  2
#define STAT_SPRITE_DRAW    3

#define STAT_LYC_INTERRUPT    ((MEM(STAT)>>6)&0x1)
#define STAT_OAM_INTERRUPT    ((MEM(STAT)>>5)&0x1)
#define STAT_VBLANK_INTERRUPT ((MEM(STAT)>>4)&0x1)
#define STAT_HBLANK_INTERRUPT ((MEM(STAT)>>3)&0x1)

uint32_t last_scanline = 0;
uint32_t frames = 0;

uint8_t curr_status = STAT_SPRITE_SEARCH;
uint32_t last_status_change;

const uint16_t STAT_LENGTH[4] = {204, 4560, 80, 172};

void move_scanline(register_file_t *state) {
    handle_input(state);
    if(!LCD_ENABLE) {
	return;
    }

    if(MEM(LY) == 153) {
	draw_next_frame = LCD_ENABLE;
	MEM(LY) = 0;
    } else {
	if(MEM(LY) < 144) {
	    update_background(state);
	    update_window(state);
	    update_sprites(state);
	}
	if(MEM(LY) == MEM(LYC)) {
	MEM(STAT) |= 0x04;
	    if(STAT_LYC_INTERRUPT) {
		request_interrupt(LCDC_STATUS, state);
	    }
	} else {
	    MEM(STAT) &= 0xfb;
	}
	MEM(LY)++;
	
	if(MEM(LY) == 144) {
	    if(REAL_TIME) {
		pause_execution();
	    }
	    frames++;

	    draw_pixels_to_screen();
	    
	    request_interrupt(V_BLANK, state);
	    //	    memset(pixels, 0, SCREEN_PIXELS * sizeof(uint32_t));
	    handle_input(state);
	}
    }


}

void check_status(uint32_t new_clock, register_file_t *state) {
    if(new_clock >= ((last_status_change + STAT_LENGTH[curr_status]) % CLOCK_MAX_VALUE) && ((new_clock < STAT_LENGTH[curr_status]) || (new_clock - STAT_LENGTH[curr_status] < ((last_status_change + STAT_LENGTH[curr_status]) % CLOCK_MAX_VALUE)))) {
	uint8_t new_status = 0;
	switch(curr_status) {
	    case STAT_SPRITE_SEARCH:
		new_status = STAT_SPRITE_DRAW;
		break;
	    case STAT_SPRITE_DRAW:
		new_status = STAT_HBLANK;
		if(STAT_HBLANK_INTERRUPT) {
		    request_interrupt(LCDC_STATUS, state);
		}
		break;
	    case STAT_HBLANK:
		if(MEM(LY) == 143) {
		    new_status = STAT_VBLANK;
		    if(STAT_VBLANK_INTERRUPT) {
			request_interrupt(LCDC_STATUS, state);
		    }
		} else {
		    new_status = STAT_SPRITE_SEARCH;
		    if(STAT_OAM_INTERRUPT) {
			request_interrupt(LCDC_STATUS, state);
		    }
		}
		break;
	    case STAT_VBLANK:
		new_status = STAT_SPRITE_SEARCH;
		if(STAT_OAM_INTERRUPT) {
		    request_interrupt(LCDC_STATUS, state);
		}
		break;
	}
	last_status_change += STAT_LENGTH[curr_status];
	curr_status = new_status;
	MEM(STAT) &= 0xf8;
	MEM(STAT) |= curr_status;
    }
}

void check_scanline(uint32_t new_clock, register_file_t *state) {
    check_status(new_clock, state);
    if(new_clock >= ((last_scanline + SCANLINE_LENGTH) % CLOCK_MAX_VALUE) && ((new_clock < SCANLINE_LENGTH) || (new_clock - SCANLINE_LENGTH < ((last_scanline + SCANLINE_LENGTH) % CLOCK_MAX_VALUE)))) {
	move_scanline(state);
	last_scanline += SCANLINE_LENGTH;
    }
}
