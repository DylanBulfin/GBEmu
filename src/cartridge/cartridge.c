#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "../cpu/internal.h"
#include "../cpu/disassembler.h"
#include "../settings.h"
#include "cartridge.h"

uint8_t *cartridge = NULL;
uint8_t *cartridge_ram = NULL;

char *save_filename;

mbc_type_t mbc = ROM_ONLY;
uint16_t curr_rom_bank = 0;
uint8_t curr_ram_bank = 0;

uint8_t mbc1_mode = 0;

uint8_t ram_banks = 0;
uint16_t rom_banks = 0;
uint16_t ram_bank_size = 0;

uint16_t max_rom_banks = 0;
uint8_t max_ram_banks = 0;
uint8_t has_ram = 0;
uint8_t has_battery = 0;

uint8_t ram_enabled = 0;

uint8_t ONE = 1;

void print_cart_range(uint32_t start_addr, uint32_t end_addr) {
    printf("         x0 x1 x2 x3 x4 x5 x6 x7 x8 x9 xa xb xc xd xe xf");
    
    int count = 0;

    for(uint32_t addr = start_addr; addr <= end_addr; addr++) {
	if(count % 16 == 0) {
	    printf("\n0x%04xx: ", (addr >> 4));
	}
	printf("%02x ", CART(addr));
	count++;
    }
    printf("\n");
}

void write_ram_to_file() {
    if(!has_battery || !has_ram || ram_banks == 0) {
	return;
    }
    FILE *f = fopen(save_filename, "w");

    fwrite(cartridge_ram, sizeof(uint8_t), ram_banks * ram_bank_size, f);

    fclose(f);

    printf("Wrote cart ram to file %s\n", save_filename);
}

void read_ram_from_file(char *game, register_file_t *state) {
    if(!has_battery || !has_ram || ram_banks == 0) {
	return;
    }

    unsigned int game_length = strlen(game);

    char *suffix = ".sram";

    save_filename = calloc(game_length + strlen(SAVE_DIR) + strlen(suffix) + 1, 1);

    for(int i = 0; i < strlen(SAVE_DIR); i++) {
	save_filename[i] = SAVE_DIR[i];
    }

    for(int i = 0; i < game_length; i++) {
	save_filename[i + strlen(SAVE_DIR)] = game[i];
    }

    for(int i = 0; i < strlen(suffix); i++) {
	save_filename[i + strlen(SAVE_DIR) + game_length] = suffix[i];
    }

    if(!LOAD_SAVE) {
	printf("Did not load save file\n\n");
	return;
    }
    
    FILE *f = fopen(save_filename, "r");

    if(f == NULL) {
	printf("There is no save data yet!\n\n");
	return;
    }

    fread(cartridge_ram, sizeof(uint8_t), ram_banks * ram_bank_size, f);

    fclose(f);

    memcpy(&MEM(0xa000), &CART_RAM(0x0000), ram_bank_size);

    printf("Read save from file!\n\n");
}

void set_mbc_values() {
    printf("MBC: 0x%02x\n", MEM_CONTROLLER_TYPE);
    //Set ram support 
    switch(MEM_CONTROLLER_TYPE) {
	case 0x00: case 0x01: case 0x0f: case 0x11:
	case 0x19: case 0x1c:
	    has_ram = 0;
	    break;
	case 0x02: case 0x03: case 0x05: case 0x06:
	case 0x10: case 0x12: case 0x13: case 0x1a:
	case 0x1b: case 0x1d: case 0x1e:
	    has_ram = 1;
	    break;
	default:
	    printf("This MBC type: 0x%02x, is not supported!\n", MEM_CONTROLLER_TYPE);
	    exit(1);
    }

    //Set battery support
    switch(MEM_CONTROLLER_TYPE) {
	case 0x00: case 0x01: case 0x02: case 0x05:
	case 0x11: case 0x12: case 0x19: case 0x1a:
	case 0x1c: case 0x1d:
	    has_battery = 0;
	    break;
	case 0x03: case 0x06: case 0x0f: case 0x10:
	case 0x13: case 0x1b: case 0x1e:
	    has_battery = 1;
	    break;
	default:
	    printf("This MBC type: 0x%02x, is not supported!\n", MEM_CONTROLLER_TYPE);
	    exit(1);
    }

    printf("%s\n", (has_battery ? "Can save" : "Cannot save"));

    //Set mbc type
    switch(MEM_CONTROLLER_TYPE) {
	case 0x00:
	    mbc = ROM_ONLY;
	    break;
	case 0x01: case 0x02: case 0x03:
	    mbc = MBC1;
	    break;
	case 0x05: case 0x06:
	    mbc = MBC2;
	    break;
	case 0x0f: case 0x10: case 0x11: case 0x12:
	case 0x13:
	    mbc = MBC3;
	    break;
	case 0x19: case 0x1a: case 0x1b: case 0x1c:
	case 0x1d: case 0x1e:
	    mbc = MBC5;
	    break;
	default:
	    printf("This MBC type: 0x%02x, is not supported!\n", MEM_CONTROLLER_TYPE);
	    exit(1);
    }
    
    //Set max ram/rom sizes
    switch(mbc) {
	case ROM_ONLY:
	    max_rom_banks = 2;
	    max_ram_banks = 0;
	    break;
	case MBC1:
	    max_rom_banks = 128;
	    max_ram_banks = 1;
	    break;
	case MBC2:
	    max_rom_banks = 16;
	    max_ram_banks = 1;
	    break;
	case MBC3:
	    max_rom_banks = 128;
	    max_ram_banks = 4;
	    break;
	case MBC5:
	    max_rom_banks = 512;
	    max_ram_banks = 16;
	    break;
	default:
	    printf("This MBC type: 0x%02x, is not supported!\n", MEM_CONTROLLER_TYPE);
	    exit(1);

    }

    //Set ROM size
    switch(ROM_SIZE) {
	case 0x00:
	    rom_banks = 2;
	    break;
	case 0x01:
	    rom_banks = 4;
	    break;
	case 0x02:
	    rom_banks = 8;
	    break;
	case 0x03:
	    rom_banks = 16;
	    break;
	case 0x04:
	    rom_banks = 32;
	    break;
	case 0x05:
	    rom_banks = 64;
	    break;
	case 0x06:
	    rom_banks = 128;
	    break;
	case 0x07:
	    rom_banks = 256;
	    break;
	case 0x52:
	    rom_banks = 72;
	    break;
	case 0x53:
	    rom_banks = 80;
	    break;
	case 0x54:
	    rom_banks = 96;
	    break;
	default:
	    printf("This MBC type: 0x%02x, is not supported!\n", MEM_CONTROLLER_TYPE);
	    exit(1);
    }

    //Set RAM size
    switch(RAM_SIZE) {
	case 0x00:
	    if(mbc == MBC2) {
		ram_banks = 1;
		ram_bank_size = 0x200;
	    } else {
		ram_banks = 0;
		ram_bank_size = 0;
	    }
	    break;
	case 0x01:
	    ram_banks = 1;
	    ram_bank_size = 0x800;
	    break;
	case 0x02:
	    ram_banks = 1;
	    ram_bank_size = 0x2000;
	    break;
	case 0x03:
	    ram_banks = 4;
	    ram_bank_size = 0x2000;
	    break;
    }

    if(has_ram && ram_banks != 0) {
	cartridge_ram = malloc(ram_banks * ram_bank_size * sizeof(uint8_t));
	printf("Allocating %d bytes for cartridge memory\n\n", ram_banks * ram_bank_size);
    }

}    

void load_file(char *game, register_file_t *state) {
    unsigned int game_length = strlen(game);
    
    char *suffix = ".gb";

    char *filename = calloc(game_length + strlen(GAME_DIR) + strlen(suffix) + 1, 1);

    for(int i = 0; i < strlen(GAME_DIR); i++) {
	filename[i] = GAME_DIR[i];
    }

    for(int i = 0; i < game_length; i++) {
	filename[i + strlen(GAME_DIR)] = game[i];
    }

    for(int i = 0; i < strlen(suffix); i++) {
	filename[i + strlen(GAME_DIR) + game_length] = suffix[i];
    }

    FILE *fp;
    fp = fopen(filename, "rb");

    if(!fp) {
	printf("\n\nThis game: %s does not exist, please choose a valid game!\n\n\n", filename);
	exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    printf("\n\nSIZE = %ld\n\n", size);
    fseek(fp, 0L, SEEK_SET);

    cartridge = malloc(size * sizeof(uint8_t));

    fread(cartridge, 1, size * sizeof(uint8_t), fp);

    fclose(fp);

    uint64_t total = 0x0;

    for(long byte_num = 0; byte_num < size; byte_num++) {
	if(byte_num != 0x14e && byte_num != 0x14f) {
	    total += CART(byte_num);
	}
    }

    set_mbc_values();

    read_ram_from_file(game, state);

    memcpy(state->memory, cartridge, ROM_BANK_SIZE * 2);
    curr_rom_bank = 1;
}

void switch_ram_bank(uint16_t new_bank, register_file_t *state) {
    if(new_bank == curr_ram_bank) {
	return;
    }
    curr_ram_bank = new_bank;
    memcpy(&MEM(RAM_BANK_START_LOC), &CART_RAM(RAM_BANK_ADDR(new_bank)), MAX_RAM_BANK_SIZE);
}

void switch_rom_bank(uint16_t new_bank, register_file_t *state) {
    if(mbc != MBC5 && new_bank == 0) {
	curr_rom_bank = 1;
	memcpy(&MEM(ROM_BANK_START_LOC), &CART(ROM_BANK_ADDR(1)), ROM_BANK_SIZE);
	return;
    }
    if(mbc == MBC1) {
	if(new_bank == 0x20 || new_bank == 0x40 || new_bank == 0x60) {
	    curr_rom_bank = new_bank + 1;
	    memcpy(&MEM(ROM_BANK_START_LOC), &CART(ROM_BANK_ADDR(new_bank+1)), ROM_BANK_SIZE);
	    return;
	}
    }

    curr_rom_bank = new_bank;

    memcpy(&MEM(ROM_BANK_START_LOC), &CART(ROM_BANK_ADDR(new_bank)), ROM_BANK_SIZE);
    
}

uint8_t *read_from_cartridge_ram(uint16_t addr, register_file_t *state) {
    if(!has_ram || ram_banks == 0) {
	printf("RAM DOESN'T EXIST\n");
	return &ONE;
    }

    if((addr - 0xa000) >= ram_bank_size) {
	printf("RAM ADDRESS 0x%04x IS OUT OF BOUNDS\n", addr);
	return &ONE;
    }

    if(!ram_enabled) {
	printf("RAM IS DISABLED\n");
	return &ONE;
    }

    return &MEM(addr);
}

void write_to_cartridge_ram(uint16_t addr, uint8_t val, register_file_t *state) {
    if(!has_ram || ram_banks == 0) {
	//printf("RAM DOESN'T EXIST\n");
	return;
    }

    if(!ram_enabled) {
	printf("RAM IS DISABLED\n");
	return;
    }
    
    if(ram_banks == 1) {
	uint16_t ram_addr = addr - 0xa000;
	if(ram_addr > ram_bank_size) {
	    printf("RAM ADDRESS 0x%04x IS OUT OF BOUNDS\n", addr);
	    return;
	}
	
	if(mbc == MBC2) {
	    CART_RAM(ram_addr) = val & 0xf;
	    MEM(addr) = val & 0xf;
	    return;
	} else {
	    CART_RAM(ram_addr) = val;
	}
    } else {
	uint16_t ram_addr = (addr - 0xa000) + (curr_ram_bank * MAX_RAM_BANK_SIZE);
	CART_RAM(ram_addr) = val;
    }
    
    MEM(addr) = val;
}

void handle_cartridge_memory_write(uint16_t addr, uint8_t val, register_file_t *state) {
    switch(mbc) {
	case ROM_ONLY:
	    return;
	    break;
	case MBC1:
	    if(addr >= 0x0000 && addr < 0x2000) {
		if((val & 0xf) == 0x0a) {
		    ram_enabled = 1;
		    //printf("RAM ENABLED\n");
		} else {
		    ram_enabled = 0;
		    //printf("RAM DISABLED\n");
		    write_ram_to_file();
		}
	    } else if(addr >= 0x2000 && addr < 0x4000) {
		if(!mbc1_mode) {
		    uint16_t new_rom_bank = curr_rom_bank & 0xe0;
		    new_rom_bank |= (val & 0x1f);
		    if(new_rom_bank < rom_banks && new_rom_bank < max_rom_banks) {
			switch_rom_bank(new_rom_bank, state);
		    } else {
			printf("DID NOT SWITCH\n");
		    }
		} else {
		    uint16_t new_rom_bank = (val & 0x1f);
		    if(new_rom_bank < rom_banks && new_rom_bank < max_rom_banks) {
			switch_rom_bank(new_rom_bank, state);
		    } else {
			printf("DID NOT SWITCH\n");
		    }
		}
	    } else if(addr >= 0x4000 && addr < 0x6000) {
		if(!mbc1_mode) {
		    uint16_t new_rom_bank = curr_rom_bank & 0x1f;
		    new_rom_bank |= (val << 5);
		    if(new_rom_bank < rom_banks && new_rom_bank < max_rom_banks) {
			switch_rom_bank(new_rom_bank, state);
		    } else {
			printf("DID NOT SWITCH\n");
		    }
		} else {
		    if(ram_banks > 0) {
			if((val & 0x3) < ram_banks && (val & 0x3) < max_ram_banks) {
			    switch_ram_bank(val & 0x3, state);
			} else {
			    printf("DID NOT SWITCH\n");
			}
		    }
		}
	    } else if(addr >= 0x6000 && addr < 0x8000) {
		if(val & 0x1) {
		    mbc1_mode = 1;
		    //		    printf("Switched to MBC mode 1\n");
		    switch_rom_bank(curr_rom_bank & 0x1f, state);
		    max_ram_banks = 4;
		} else {
		    mbc1_mode = 0;
		    //		    printf("Switched to MBC mode 0\n");
		    switch_ram_bank(1, state);
		    max_ram_banks = 1;
		}
	    }
	    break;
	case MBC3:
	    if(addr >= 0x0000 && addr < 0x2000) {
		if((val & 0xf) == 0x0a) {
		    ram_enabled = 1;
		} else {
		    ram_enabled = 0;
		    write_ram_to_file();
		}
	    } else if(addr >= 0x2000 && addr < 0x4000) {
		if((val & 0x7f) < rom_banks && (val & 0x7f) < max_rom_banks) {
		    switch_rom_bank(val & 0x7f, state);
		} else {
		    printf("DID NOT SWITCH\n");
		}
	    } if(addr >= 0x4000 && addr < 0x6000) {
		if(val < 0x4) {
		    if(val < ram_banks && val < max_ram_banks) {
			switch_ram_bank(val, state);
		    } else {
			printf("DID NOT SWITCH\n");
		    }
		}
	    }
	    break;
	default:
	    printf("OTHER MBCs not implemented yet, controller type = 0x%02x\n", MEM_CONTROLLER_TYPE);
	    break;
    }
}
