/**
 * @file chip8.h
 *
 * @author Nitu Mario
 */

#define CHIP8_H

#include <cstdint>

uint8_t registers[16]; // 16 8-bit registers V0 - VF values from 0x00 to 0xFF
uint8_t memory[4096]; // 0x000 to 0xFFF
uint16_t index; // register to store adresses for use in operations
uint16_t pc; // program counter register that holds the adress of the next instruction to exectute
uint16_t stack[16]; // 16 level stack memory
uint8_t sp; // stack pointer to hold where in the stack the most recent value was placed    
uint8_t delayTimer;
uint8_t soundTimer;
uint8_t keypad[16]; 
uint32_t video[64 * 32]; // memory buffer for storing the graphics to display
uint16_t opcode;


