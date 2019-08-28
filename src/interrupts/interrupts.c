#include <stdio.h>
#include "interrupts.h"
#include "../cpu/internal.h"
#include "../cpu/operations.h"
#include "../timing/clock.h"

void perform_interrupt(uint8_t bit_num, register_file_t *state) {
    if((1 << bit_num) & LCDC_STATUS) {
	//	printf("STAT interrupt occurred at LY = 0x%02x\n", MEM(LY));
    }
    
    UNHALT;
    IME = 0;
    INC_CLOCK(20,state);

    uint16_t addr = 0x40 + (bit_num << 3);

    MEM(SP-1) = HI_BYTE(PC);
    MEM(SP-2) = LO_BYTE(PC);

    SP -= 2;

    PC = addr;
}

int check_interrupts(register_file_t *state) {
    if((IME == 0) || (MEM(IE) == 0)) {
	if(MEM(IE) & MEM(IF) & 0x1f) {
	    UNHALT;
	}
 	return 0;
    }
    
    for(int bit = 0; bit < 5; bit++) {
	uint8_t mask = 0x1 << bit;
	if((MEM(IF) & mask) && (MEM(IE) & mask)) {
	    perform_interrupt(bit, state);
	    MEM(IF) &= (~mask);
	    return 1;
	}
    }
    return 0;
}

void request_interrupt(uint8_t mask, register_file_t *state) {
    if(mask == LCDC_STATUS) {
	//	printf("STAT interrupt requested at LY = 0x%02x\n", MEM(LY));
    }
    
    UNHALT;
    MEM(IF) |= mask;
}
