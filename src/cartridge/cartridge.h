#pragma once

#include "../cpu/internal.h"

typedef enum mbc_type{ROM_ONLY,MBC1,MBC2,MBC3,MBC5} mbc_type_t;

extern uint8_t *cartridge;
extern uint8_t *cartridge_ram;

void load_file(char*,register_file_t*);
void handle_cartridge_memory_write(uint16_t,uint8_t,register_file_t*);
void write_to_cartridge_ram(uint16_t,uint8_t,register_file_t*);
uint8_t *read_from_cartridge_ram(uint16_t,register_file_t*);
void write_ram_to_file();

#define CART(addr) cartridge[addr]
#define CART_RAM(addr) cartridge_ram[addr]

#define ROM_BANK_START_LOC 0x4000
#define ROM_BANK_ADDR(num) (0x4000 * num)
#define ROM_BANK_SIZE      0x4000

#define RAM_BANK_START_LOC 0xa000
#define RAM_BANK_ADDR(num) (0x2000 * num)
#define MAX_RAM_BANK_SIZE 0x2000

#define MEM_CONTROLLER_TYPE CART(0x147)
#define ROM_SIZE CART(0x148)
#define RAM_SIZE CART(0x149)
