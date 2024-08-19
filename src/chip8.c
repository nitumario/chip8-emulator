#include <stdio.h>
#include "chip8.h"

const unsigned int ROM_START_ADDRESS = 0x200;

void loadROM(char const* filename) {
    // open the file in binary format
    FILE* rom = fopen(filename, "rb");
    if (rom == NULL) {
        perror("Failed to open ROM file");
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
        printf("Error reading ROM file.\n");
    }

    fclose(rom);

    printf("%ld bytes read.\n", bytesRead);
}

void op_00E0(){
    for(int i=0; i<=64*32, i++;)
        i == 0;
}