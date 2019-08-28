#include <stdio.h>
#include <stdlib.h>
#include "internal.h"
#include "arrays.h"

char *disassemble(register_file_t *state) {
    uint8_t *code = &MEM(PC);
    char *ret = malloc(sizeof(char) * 100);
    int argnum = num_args[*code];
    if(*code != 0xcb) {
	if(argnum == 2) {
	    sprintf(ret, reg_ops[*code], code[2], code[1]);
	} else if(argnum == 1) {
	    sprintf(ret, reg_ops[*code], code[1]);
	} else if(argnum == 0){
	    sprintf(ret, reg_ops[*code]);
	} else {
	    if(*code < 0x40) {
		sprintf(ret, reg_ops[*code], code[1]);
	    } else if(reg_ops[*code][0] == 'J' || reg_ops[*code][0] == 'C') {
		sprintf(ret, reg_ops[*code], code[2], code[1]);
	    } else {
		sprintf(ret, reg_ops[*code]);
	    }
	}   
    } else {
	sprintf(ret, ext_ops[code[1]]);
    }
    return ret;
}
