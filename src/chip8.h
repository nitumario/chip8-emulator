/**
 * @file chip8.h
 *
 * @author Nitu Mario
 */

#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h> 


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

const unsigned int FONTSET_SIZE = 80;
uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#endif  // CHIP8_H