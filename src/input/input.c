#include <stdio.h>
#include <SDL2/SDL.h>
#include "../cpu/internal.h"
#include "../interrupts/interrupts.h"
#include "../settings.h"
#include "input.h"

SDL_Event event;
buttons_t buttons = {0,0,0,0,0,0,0,0};
uint8_t joypad_signal = 1;

uint8_t evaluate_joypad_signal(register_file_t *state) {
    uint8_t res = 1;
    for(uint8_t i = 0; i < 4; i++) {
	res &= ((MEM(P1) >> i) & 0x1);
    }
    return res;
}

void print_buttons() {
    printf("A: %d, B: %d, Start: %d, Select: %d\nUp: %d, Down: %d, Left: %d, Right: %d\n", buttons.a, buttons.b, buttons.start, buttons.select, buttons.up, buttons.down, buttons.left, buttons.right);
}
    
void set_key_reg(register_file_t *state) {
    MEM(P1) |= 0x0f;
    if(DIR_SELECTED && !BUT_SELECTED) {
	if(buttons.down) {
	    MEM(P1) &= DOWN_MASK;
	}
	if(buttons.up) {
	    MEM(P1) &= UP_MASK;
	}
	if(buttons.left) {
	    MEM(P1) &= LEFT_MASK;
	}
	if(buttons.right) {
	    MEM(P1) &= RIGHT_MASK;
	}
	return;
    }

    if(BUT_SELECTED && !DIR_SELECTED) {
	if(buttons.start) {
	    MEM(P1) &= START_MASK;
	}
	if(buttons.select) {
	    MEM(P1) &= SELECT_MASK;
	}
	if(buttons.b) {
	    MEM(P1) &= B_MASK;
	}
	if(buttons.a) {
	    MEM(P1) &= A_MASK;
	}
    }

    if(BUT_SELECTED && DIR_SELECTED) {
	if(buttons.down || buttons.start) {
	    MEM(P1) &= DOWN_MASK;
	}
	if(buttons.up || buttons.select) {
	    MEM(P1) &= UP_MASK;
	}
	if(buttons.left || buttons.b) {
	    MEM(P1) &= LEFT_MASK;
	}
	if(buttons.right || buttons.a) {
	    MEM(P1) &= RIGHT_MASK;
	}
    }

    if((BUT_SELECTED || DIR_SELECTED) && !(MEM(P1) | 0xf)) {
	printf("UH OH THIS IS NO GOOD PLZ FIX\n");
	printf("P1: 0x%02x\n", MEM(P1));
    }
}

void handle_input(register_file_t *state) {
    while(SDL_PollEvent(&event)) {
	if(event.type == SDL_QUIT) {
	    quit = 1;
	    return;
	}

	SDL_Keycode k = event.key.keysym.sym;

	if(event.type == SDL_KEYDOWN) {
	    if(k == A_KEY) {
		buttons.a = 1;
	    }
	    if(k == B_KEY) {
		buttons.b = 1;
	    }
	    if(k == START_KEY) {
		buttons.start = 1;
	    }
	    if(k == SELECT_KEY) {
		buttons.select = 1;
	    }
	    if(k == UP_KEY) {
		buttons.up = 1;
	    }
	    if(k == DOWN_KEY) {
		buttons.down = 1;
	    }
	    if(k == LEFT_KEY) {
		buttons.left = 1;
	    }
	    if(k == RIGHT_KEY) {
		buttons.right = 1;
	    }
	}
	if(event.type == SDL_KEYUP) {
	    if(k == A_KEY) {
		buttons.a = 0;
	    }
	    if(k == B_KEY) {
		buttons.b = 0;
	    }
	    if(k == START_KEY) {
		buttons.start = 0;
	    }
	    if(k == SELECT_KEY) {
		buttons.select = 0;
	    }
	    if(k == UP_KEY) {
		buttons.up = 0;
	    }
	    if(k == DOWN_KEY) {
		buttons.down = 0;
	    }
	    if(k == LEFT_KEY) {
		buttons.left = 0;
	    }
	    if(k == RIGHT_KEY) {
		buttons.right = 0;
	    }
	}
	return;
    }
    set_key_reg(state);

    uint8_t new_joypad_signal = evaluate_joypad_signal(state);
    if(joypad_signal && !new_joypad_signal) {
	request_interrupt(JOYPAD, state);
    }
    joypad_signal = new_joypad_signal;
}

int8_t is_valid_button_press(SDL_Keycode sym, register_file_t *state) {
    return (sym == DOWN_KEY || sym == UP_KEY || sym == LEFT_KEY || sym == RIGHT_KEY || sym == A_KEY || sym == B_KEY || sym == START_KEY || sym == SELECT_KEY);
}

void wait_for_valid_button_press(register_file_t *state) {
    while(1) {
	SDL_WaitEvent(&event);
	while(event.type != SDL_KEYDOWN) {
	    SDL_WaitEvent(&event);
	}
	if(is_valid_button_press(event.key.keysym.sym, state)) {
	    return;
	}
    }
}
