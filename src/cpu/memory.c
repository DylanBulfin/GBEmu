#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "internal.h"
#include "../timing/clock.h"
#include "../input/input.h"
#include "../cpu/disassembler.h"
#include "../cartridge/cartridge.h"
#include "../graphics/graphics.h"

uint8_t hold_val = 0;

void write_memory(uint16_t addr, uint8_t val, register_file_t *state) {
    if(addr == TAC && (((MEM(TAC)>>2)&0x1) == 0) && ((val>>2) & 0x1)) {
	start_timer();
    }

    if(addr >= 0x0000 && addr < 0x8000) {
	handle_cartridge_memory_write(addr, val, state);
	return;
    }

    if(addr >= 0xa000 && addr < 0xc000) {
	//printf("Attempted cartridge ram write at addr 0x%04x, val = 0x%02x\n", addr, val);
	write_to_cartridge_ram(addr, val, state);
	return;
    }

    if(addr == LCDC && !(val & 0x80)) {
	MEM(LY) = 0;
	clear_screen();
    }

    if(addr == P1) {
        MEM(addr) = val;
	handle_input(state);
    } else if(addr == DMA) {
	uint16_t start_addr = ((uint16_t) val) << 8;
	memcpy(&MEM(0xfe00), &MEM(start_addr), 0x100 * sizeof(uint8_t));
	MEM(addr) = val;
    } else if(addr == DIV || addr == VBK) {
	MEM(addr) = 0;
    } else if(addr >= 0xc000 && addr < 0xde00) {
	MEM(addr) = val;
	MEM(addr + 0x2000) = val;
    } else if(addr >= 0xe000 && addr < 0xfe00) {
	MEM(addr) = val;
	MEM(addr - 0x2000) = val;
    } else {
       	MEM(addr) = val;
    }
}

uint8_t *read_memory(uint16_t addr, register_file_t *state) {
    /*
    if(addr >= 0xff00 && addr <= 0xff4b && addr != P1 && addr != LY && addr != SCY) {
	printf("Special register 0x%04x read by instruction %s\n", addr, disassemble(state));
    }*/
    if(addr >= 0xa000 && addr < 0xc000) {
	return read_from_cartridge_ram(addr, state);
    }

    if(addr == P1) {
	handle_input(state);
	hold_val = MEM(P1) & 0x3f;
	return &hold_val;
    }

    return &MEM(addr);
}

    
void print_mem_range(uint16_t start_addr, uint16_t end_addr, register_file_t *state) {
    printf("        x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb xc xd xe xf");
    
    int count = 0;

    for(uint16_t addr = start_addr; addr <= end_addr; addr++) {
	if(count % 16 == 0) {
	    printf("\n0x%03xx: ", (addr >> 4));
	}
	printf("%02x ", MEM(addr));
	count++;
    }
    printf("\n");
}
