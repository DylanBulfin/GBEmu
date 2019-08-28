#pragma once

#include "internal.h"
#include "operations.h"

extern const void (*func_array[])(register_file_t*);
extern const void (*cb_array[])(register_file_t*);
extern const int num_args[];

//Disassembler string arrays
extern const char* reg_ops[];
extern const char* ext_ops[];

//Internal BIOS
extern const uint8_t bios[];
extern const uint8_t val_after_bios[];

//Clock cycle count
extern const uint8_t cycles[];
