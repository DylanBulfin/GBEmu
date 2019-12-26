#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

uint8_t *sprite_list = NULL;

register_file_t *state;

int compare_sprites(const void * a, const void * b) {    
  uint8_t *sprite_a = SPRITE(*((uint8_t*)a));
  uint8_t *sprite_b = SPRITE(*((uint8_t*)b));
  if(sprite_a[1] < sprite_b[1]) {
    return -1;
  } else if(sprite_b[1] < sprite_a[1]) {
    return 1;
  } else if(*((uint8_t*)a) < *((uint8_t*)b)) {
    return -1;
  } else {
    return 1;
  }
}

void draw_sprite(uint8_t sprite_num) {
  uint8_t *sprite = SPRITE(sprite_num);
  uint8_t control = sprite[3];

  uint8_t y_line = 0;
  if(SPRITE_Y_FLIP) {
    y_line = (SPRITE_SIZE - 1) - (MEM(LY) - SPRITE_Y);
  } else {
    y_line = MEM(LY) - SPRITE_Y;
  }

  uint16_t line_address = TILE_DATA_ADDRESS1 + (sprite[2] * TILE_SIZE_BYTES) + (TILE_LINE_SIZE_BYTES * y_line);

  if(SPRITE_X_FLIP) {
    uint8_t screen_x_loc = SPRITE_X;
    for(int8_t x_pixel = 7; x_pixel >= 0; x_pixel--) {
      if(screen_x_loc >= 0 && screen_x_loc < 160) {
	uint8_t color_code = SPRITE_COLOR_CODE(COLOR_INDEX(line_address,x_pixel),SPRITE_PALETTE_ADDR);
	if(!(COLOR_INDEX(line_address, x_pixel) == 0)) {
	  uint32_t *dest = &pixels[(MEM(LY) * SCREEN_WIDTH) + screen_x_loc];
	  uint8_t *dest_codes = &pixel_codes[(MEM(LY) * SCREEN_WIDTH) + screen_x_loc];
	  if(SPRITE_PRIORITY) {
	    if(*dest_codes == 0) {
	      *dest = COLORS[color_code];
	    }
	  } else {
	    *dest = COLORS[color_code];
	  }
	}
      }
      screen_x_loc++;
    }
  } else {
    uint8_t screen_x_loc = SPRITE_X;
    for(uint8_t x_pixel = 0; x_pixel < 8; x_pixel++) {
      if(screen_x_loc >= 0 && screen_x_loc < 160) {
	uint8_t color_code = SPRITE_COLOR_CODE(COLOR_INDEX(line_address,x_pixel),SPRITE_PALETTE_ADDR);
	if(!(COLOR_INDEX(line_address, x_pixel) == 0)) {
	  uint32_t *dest = &pixels[(MEM(LY) * SCREEN_WIDTH) + screen_x_loc];
	  uint8_t *dest_codes = &pixel_codes[(MEM(LY) * SCREEN_WIDTH) + screen_x_loc];
	  if(SPRITE_PRIORITY) {
	    if(*dest_codes == 0) {
	      *dest = COLORS[color_code];
	    }
	  } else {
	    *dest = COLORS[color_code];
	  }
	}
      }
      screen_x_loc++;
    }
  }
}

void update_sprites(register_file_t *rf) {
  state = rf;
  if(!draw_next_frame || !SPRITE_ENABLE) {
    return;
  }
  sprite_list = malloc(40 * sizeof(uint8_t));

  uint8_t sprite_count = 0;
    
  for(uint8_t sprite_num = 0; sprite_num < 40; sprite_num++) {
    uint8_t *sprite = SPRITE(sprite_num);
    if(SPRITE_Y <= MEM(LY) && (SPRITE_Y + SPRITE_SIZE) > MEM(LY)) {
      sprite_list[sprite_count] = sprite_num;
      sprite_count++;
    }
  }

  sprite_list = realloc(sprite_list, sprite_count * sizeof(uint8_t));
		
  if(sprite_count > 10) {
    qsort(sprite_list, sprite_count, sizeof(uint8_t), compare_sprites);
    for(int8_t i = 9; i >= 0; i--) {
      draw_sprite(sprite_list[i]);
    }
  } else {
    for(int8_t i = sprite_count - 1; i >= 0; i--) {
      draw_sprite(sprite_list[i]);
    }
  }

  free(sprite_list);
}
