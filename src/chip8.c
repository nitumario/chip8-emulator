#include <stdio.h>
#include "chip8.h"

const unsigned int ROM_START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

void loadROM(char const* filename) {
    // open the file in binary format
    FILE* rom = fopen(filename, "rb");
    if (rom == NULL) {
        printf("Failed to open ROM file");
        return;
    }

    // fetch the file size to make sure it fits
    fseek(rom, 0, SEEK_END);
    long romSize = ftell(rom);
    rewind(rom);

    if (romSize > (sizeof(memory) - ROM_START_ADDRESS)) {
        printf("program too large to fit in ROm.\n");
        fclose(rom);
        return;
    }

    //copy the program into the ROM memory starting at 0x200
    size_t bytesRead = fread(&memory[ROM_START_ADDRESS], sizeof(uint8_t), romSize, rom);
    if (bytesRead != romSize) {
        printf("error reading ROM file.\n");
    }

    fclose(rom);

    printf("%ld bytes read.\n", bytesRead);
}

void init(){
    sp = 0;
    pc = ROM_START_ADDRESS;
    for (unsigned int i = 0; i < FONTSET_SIZE; i++){
		memory[FONTSET_START_ADDRESS + i] = fontset[i];
	}

}

// clear the display
void op_00E0(){
    for(int i=0; i<=64*32; i++)
        video[i] == 0;
}

// return from a subroutine
void op_00EE(){
    sp--; // seting the stack pointer one value up
    pc = stack[sp]; // setting the next instruction to the last one held in the stack
}

// jump to adress nnn
void op_1nnn(){
    pc = opcode & 0x0FFFu; // this AND operation deletes the first 4-bits keeping only the last 12(the nnn value)
}
// call subroutine at nn
void op_2nnn(){
    stack[sp] = pc; // puts current command on top of the stack
    sp++;
    pc = opcode & 0x0FFFu;
}
