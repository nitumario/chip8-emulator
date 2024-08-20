#include <stdio.h>
#include <stdint.h> 

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
        printf("program too large to fit in ROM.\n");
        fclose(rom);
        return;
    }

    // copy the program into the ROM memory starting at 0x200
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
    for(int i = 0; i < 64 * 32; i++)
        video[i] = 0;
}

// return from a subroutine
void op_00EE(){
    sp--; // setting the stack pointer one value up
    pc = stack[sp]; // setting the next instruction to the last one held in the stack
}

// jump to address nnn
void op_1nnn(){
    pc = opcode & 0x0FFFu; // this AND operation deletes the first 4-bits keeping only the last 12 (the nnn value)
}

// call subroutine at nnn
void op_2nnn(){
    stack[sp] = pc; // puts current command on top of the stack
    sp++;
    pc = opcode & 0x0FFFu;
}

void op_3xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get the x value and shift it to the right
    uint8_t kk = opcode & 0x00FFu; // get the kk value

    if (registers[x] == kk) {
        pc += 2; // skipping the next instruction if the register is equal to kk
    }
}

void op_4xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u; // get the x value and shift it to the right
    uint8_t kk = opcode & 0x00FFu; // get the kk value

    if (registers[x] != kk) {
        pc += 2; // skipping the next instruction if the register is not equal to kk
    }
}

// skip next instruction if Vx == Vy
void op_5xy0(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    if (registers[x] == registers[y])
        pc += 2;
}

// set Vx = kk
void op_6xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;
    registers[x] = kk;
}

// set Vx = Vx + kk
void op_7xkk(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;
    registers[x] += kk;  
}

// set Vx = Vy
void op_8xy0(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    registers[x] = registers[y];
}

// set Vx = Vx OR Vy
void op_8xy1(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    registers[x] |= registers[y];
}

// set Vx = Vx AND Vy
void op_8xy2(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    registers[x] &= registers[y];
}

// set Vx = Vx XOR Vy
void op_8xy3(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    registers[x] ^= registers[y];
}

// set Vx = Vx + Vy, set VF = carry 
void op_8xy4(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    uint16_t sum = registers[x] + registers[y];
    if (sum > 255)
        registers[0xF] = 1;
    else
        registers[0xF] = 0;
    registers[x] = sum & 0xFFu;
}           

// set Vx = Vx - Vy, set VF = NOT borrow            
void op_8xy5(){
    uint8_t x = (opcode & 0x0F00u) >> 8u;
    uint8_t y = (opcode & 0x00F0u) >> 4u;
    if (registers[x] > registers[y])
        registers[0xF] = 1;
    else
        registers[0xF] = 0;
    registers[x] -= registers[y];
}