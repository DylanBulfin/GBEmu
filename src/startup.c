#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "cpu/internal.h"
#include "cpu/arrays.h"
#include "cpu/run.h"
#include "graphics/graphics.h"
#include "cartridge/cartridge.h"
#include "settings.h"

#define TOTAL_RAM_SIZE 0x10000

int8_t in_bios = -1;

void set_startup_values(register_file_t *state) {
    A = 0x01;
    SET_FLAGS(0xb0);
    B = 0x00;
    C = 0x13;
    D = 0x00;
    E = 0xd8;
    H = 0x01;
    L = 0x4d;
    SP = 0xfffe;
    PC = 0x100;

    MEM(TIMA) = 0x00;
    MEM(TMA) = 0x00;
    MEM(TAC) = 0x00;
    
    MEM(NR10) = 0x80;
    MEM(NR11) = 0xbf;
    MEM(NR12) = 0xf3;
    MEM(NR14) = 0xbf;
    MEM(NR21) = 0x3f;
    MEM(NR22) = 0x00;
    MEM(NR24) = 0xbf;
    MEM(NR30) = 0x7f;
    MEM(NR31) = 0xff;
    MEM(NR32) = 0x9f;
    MEM(NR33) = 0xbf;
    MEM(NR41) = 0xff;
    MEM(NR42) = 0x00;
    MEM(NR43) = 0x00;
    MEM(NR44) = 0xbf;
    MEM(NR50) = 0x77;
    MEM(NR51) = 0xf3;
    MEM(NR52) = 0xf1;

    MEM(LCDC) = 0x91;
    MEM(SCY) = 0x00;
    MEM(SCX) = 0x00;
    MEM(LYC) = 0x00;
    MEM(BGP) = 0xfc;
    MEM(OBP0) = 0xff;
    MEM(OBP1) = 0xff;
    MEM(WY) = 0x00;
    MEM(WX) = 0x00;
    MEM(IE) = 0x00;
}
void run_bios(register_file_t *state) {
    in_bios = 1;
    uint8_t *temp = malloc(256 * sizeof(uint8_t));
    
    memcpy(temp, state->memory, 0x100);
    memcpy(state->memory, bios, 0x100);
    
    while(PC < 0x100) {
	run_instruction(state);
    }
    
    memcpy(state->memory, temp, 0x100);
    
    free(temp);

    in_bios = 0;
}

void run_startup(char *filename,register_file_t *state) {
    load_settings();
    
    uint8_t *memory = malloc(TOTAL_RAM_SIZE);

    state->memory = memory;

    load_file(filename, state);

    setup_display();	

    run_bios(state);

    set_startup_values(state);
}
