#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>

#include<ncurses.h>

#define WIDTH   64
#define HEIGHT  32

#define DELAY 2

#define KEY1    '1'
#define KEY2    '2'
#define KEY3    '3'
#define KEYC    '4'
#define KEY4    'q'
#define KEY5    'w'
#define KEY6    'e'
#define KEYD    'r'
#define KEY7    'a'
#define KEY8    's'
#define KEY9    'd'
#define KEYE    'f'
#define KEYA    'z'
#define KEY0    'x'
#define KEYB    'c'
#define KEYF    'v'
#define KEYQUIT 'm'

typedef struct {
    uint16_t I;
    uint16_t pc;

    uint16_t stack[16];
    uint16_t sp;

    uint8_t V[16];
    uint8_t memory[4097];

    uint8_t gfx[WIDTH * HEIGHT];
    uint8_t draw_flag;

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t key[16];
} Chip8;

static const uint8_t chip8_fontset[80] = {
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

void initCurses(void);
Chip8* initEmu(void);
uint16_t getOpcode(Chip8* emu);
void emulateCycle(Chip8* emu);
void getInput(Chip8* emu, char input);
void drawGame(Chip8* emu);
void openRom(Chip8* emu, const char* file);

int main(int argc, char** argv){

    if(argc < 2){
        printf("No game specified\n");
        exit(EXIT_FAILURE);
    }

    Chip8* emu = initEmu();
    openRom(emu, argv[1]);

    initCurses();

    while(1){
        emulateCycle(emu);

        if(emu->draw_flag)
            drawGame(emu);

        usleep(DELAY * 1000);
    }
}

void initCurses(void){
    initscr();
    raw();
    curs_set(0);
    timeout(0);
    clear();
    noecho();
}

Chip8* initEmu(void){
    Chip8* emu = malloc(sizeof(Chip8));
    memset(emu, 0, sizeof(Chip8));

    emu->pc = 0x200;
    for(int i=0; i<80; i++){
        emu->memory[i] = chip8_fontset[i];
    }
    emu->draw_flag = 1;
    return emu;
}

void openRom(Chip8* emu, const char* file){
    FILE* rom;
    rom = fopen(file, "rb");
    if(!rom){
        printf("error opening file: %s\n", file);
        free(emu);
        exit(EXIT_FAILURE);
    }
    fread(&emu->memory[0x200], 0xFFF, 1, rom);
    fclose(rom);
}

void drawGame(Chip8* emu){
    uint16_t i,j;
    for(i=0; i<HEIGHT; i++){
        for(j=0; j<WIDTH; j++){
            if(emu->gfx[j + (i * WIDTH)]){
                mvaddch(i, j, ACS_BLOCK);
            }else{
                mvaddch(i, j, ' ');
            }
        }
    }
    refresh();
    emu->draw_flag = 0;
	memset(emu->key, 0, sizeof(emu->key));
}

void getInput(Chip8* emu, char input){
    while(input != ERR){
		emu->key[0x0] = (input == KEY0);
		emu->key[0x1] = (input == KEY1);
		emu->key[0x2] = (input == KEY2);
		emu->key[0x3] = (input == KEY3);
		emu->key[0x4] = (input == KEY4);
		emu->key[0x5] = (input == KEY5);
		emu->key[0x6] = (input == KEY6);
		emu->key[0x7] = (input == KEY7);
		emu->key[0x8] = (input == KEY8);
		emu->key[0x9] = (input == KEY9);
		emu->key[0xA] = (input == KEYA);
		emu->key[0xB] = (input == KEYB);
		emu->key[0xC] = (input == KEYC);
		emu->key[0xD] = (input == KEYD);
		emu->key[0xE] = (input == KEYE);
		emu->key[0xF] = (input == KEYF);
		
		if(input == KEYQUIT){
			endwin();
            free(emu);
            exit(EXIT_SUCCESS);
		}
		input = getch();
    }
}

void emulateCycle(Chip8* emu)
{
    getInput(emu, getch());
	// Fetch opcode
	uint16_t opcode = emu->memory[emu->pc] << 8 | emu->memory[emu->pc + 1];
	// Process opcode
	//printf("0x%X\n", opcode);
	switch(opcode & 0xF000)
	{
		case 0x0000:
			switch(opcode & 0x000F)
			{
				case 0x0000: // 0x00E0: Clears the screen
					for(int i = 0; i < 2048; ++i)
						emu->gfx[i] = 0x0;
					emu->draw_flag = 1;
					emu->pc += 2;
				break;

				case 0x000E: // 0x00EE: Returns from subroutine
					emu->sp--;			// 16 levels of stack, decrease stack pointer to prevent overwrite
					emu->pc = emu->stack[emu->sp];	// Put the stored return address from the stack back into the program counter
					emu->pc += 2;		// Don't forget to increase the program counter!
				break;

				default:
					printf ("Unknown opcode [0x0000]: 0x%X\n", opcode);
			}
		break;

		case 0x1000: // 0x1NNN: Jumps to address NNN
			emu->pc = opcode & 0x0FFF;
		break;

		case 0x2000: // 0x2NNN: Calls subroutine at NNN.
			emu->stack[emu->sp] = emu->pc;			// Store current address in stack
			emu->sp++;					// Increment stack pointer
			emu->pc = opcode & 0x0FFF;	// Set the program counter to the address at NNN
		break;

		case 0x3000: // 0x3XNN: Skips the next instruction if VX equals NN
			if(emu->V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
				emu->pc += 4;
			else
				emu->pc += 2;
		break;

		case 0x4000: // 0x4XNN: Skips the next instruction if VX doesn't equal NN
			if(emu->V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
				emu->pc += 4;
			else
				emu->pc += 2;
		break;

		case 0x5000: // 0x5XY0: Skips the next instruction if VX equals VY.
			if(emu->V[(opcode & 0x0F00) >> 8] == emu->V[(opcode & 0x00F0) >> 4])
				emu->pc += 4;
			else
				emu->pc += 2;
		break;

		case 0x6000: // 0x6XNN: Sets VX to NN.
			emu->V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
			emu->pc += 2;
		break;

		case 0x7000: // 0x7XNN: Adds NN to VX.
			emu->V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
			emu->pc += 2;
		break;

		case 0x8000:
			switch(opcode & 0x000F)
			{
				case 0x0000: // 0x8XY0: Sets VX to the value of VY
					emu->V[(opcode & 0x0F00) >> 8] = emu->V[(opcode & 0x00F0) >> 4];
					emu->pc += 2;
				break;

				case 0x0001: // 0x8XY1: Sets VX to "VX OR VY"
					emu->V[(opcode & 0x0F00) >> 8] |= emu->V[(opcode & 0x00F0) >> 4];
					emu->pc += 2;
				break;

				case 0x0002: // 0x8XY2: Sets VX to "VX AND VY"
					emu->V[(opcode & 0x0F00) >> 8] &= emu->V[(opcode & 0x00F0) >> 4];
					emu->pc += 2;
				break;

				case 0x0003: // 0x8XY3: Sets VX to "VX XOR VY"
					emu->V[(opcode & 0x0F00) >> 8] ^= emu->V[(opcode & 0x00F0) >> 4];
					emu->pc += 2;
				break;

				case 0x0004: // 0x8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
					if(emu->V[(opcode & 0x00F0) >> 4] > (0xFF - emu->V[(opcode & 0x0F00) >> 8]))
						emu->V[0xF] = 1; //carry
					else
						emu->V[0xF] = 0;
					emu->V[(opcode & 0x0F00) >> 8] += emu->V[(opcode & 0x00F0) >> 4];
					emu->pc += 2;
				break;

				case 0x0005: // 0x8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
					if(emu->V[(opcode & 0x00F0) >> 4] > emu->V[(opcode & 0x0F00) >> 8])
						emu->V[0xF] = 0; // there is a borrow
					else
						emu->V[0xF] = 1;
					emu->V[(opcode & 0x0F00) >> 8] -= emu->V[(opcode & 0x00F0) >> 4];
					emu->pc += 2;
				break;

				case 0x0006: // 0x8XY6: Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift
					emu->V[0xF] = emu->V[(opcode & 0x0F00) >> 8] & 0x1;
					emu->V[(opcode & 0x0F00) >> 8] >>= 1;
					emu->pc += 2;
				break;

				case 0x0007: // 0x8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
					if(emu->V[(opcode & 0x0F00) >> 8] > emu->V[(opcode & 0x00F0) >> 4])	// VY-VX
						emu->V[0xF] = 0; // there is a borrow
					else
						emu->V[0xF] = 1;
					emu->V[(opcode & 0x0F00) >> 8] = emu->V[(opcode & 0x00F0) >> 4] - emu->V[(opcode & 0x0F00) >> 8];
					emu->pc += 2;
				break;

				case 0x000E: // 0x8XYE: Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift
					emu->V[0xF] = emu->V[(opcode & 0x0F00) >> 8] >> 7;
					emu->V[(opcode & 0x0F00) >> 8] <<= 1;
					emu->pc += 2;
				break;

				default:
					printf ("Unknown opcode [0x8000]: 0x%X\n", opcode);
			}
		break;

		case 0x9000: // 0x9XY0: Skips the next instruction if VX doesn't equal VY
			if(emu->V[(opcode & 0x0F00) >> 8] != emu->V[(opcode & 0x00F0) >> 4])
				emu->pc += 4;
			else
				emu->pc += 2;
		break;

		case 0xA000: // ANNN: Sets I to the address NNN
			emu->I = opcode & 0x0FFF;
			emu->pc += 2;
		break;

		case 0xB000: // BNNN: Jumps to the address NNN plus V0
			emu->pc = (opcode & 0x0FFF) + emu->V[0];
		break;

		case 0xC000: // CXNN: Sets VX to a random number and NN
			emu->V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
			emu->pc += 2;
		break;

		case 0xD000: // DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
					 // Each row of 8 pixels is read as bit-coded starting from emu->memory location I;
					 // I value doesn't change after the execution of this instruction.
					 // VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn,
					 // and to 0 if that doesn't happen
		{
			uint16_t x = emu->V[(opcode & 0x0F00) >> 8];
			uint16_t y = emu->V[(opcode & 0x00F0) >> 4];
			uint16_t height = opcode & 0x000F;
			uint16_t pixel;

			emu->V[0xF] = 0;
			for (int yline = 0; yline < height; yline++)
			{
				pixel = emu->memory[emu->I + yline];
				for(int xline = 0; xline < 8; xline++)
				{
					if((pixel & (0x80 >> xline)) != 0)
					{
						if(emu->gfx[(x + xline + ((y + yline) * 64))] == 1)
						{
							emu->V[0xF] = 1;
						}
						emu->gfx[x + xline + ((y + yline) * 64)] ^= 1;
					}
				}
			}

			emu->draw_flag = 1;
			emu->pc += 2;
		}
		break;

		case 0xE000:
			switch(opcode & 0x00FF)
			{
				case 0x009E: // EX9E: Skips the next instruction if the key stored in VX is pressed
					if(emu->key[emu->V[(opcode & 0x0F00) >> 8]] != 0)
						emu->pc += 4;
					else
						emu->pc += 2;
				break;

				case 0x00A1: // EXA1: Skips the next instruction if the key stored in VX isn't pressed
					if(emu->key[emu->V[(opcode & 0x0F00) >> 8]] == 0)
						emu->pc += 4;
					else
						emu->pc += 2;
				break;

				default:
					printf ("Unknown opcode [0xE000]: 0x%X\n", opcode);
			}
		break;

		case 0xF000:
			switch(opcode & 0x00FF)
			{
				case 0x0007: // FX07: Sets VX to the value of the delay timer
					emu->V[(opcode & 0x0F00) >> 8] = emu->delay_timer;
					emu->pc += 2;
				break;

				case 0x000A: // FX0A: A key press is awaited, and then stored in VX
				{
					int keyPress = 0;
					getInput(emu, getch());
					for(int i = 0; i < 16; ++i)
					{
						if(emu->key[i] != 0)
						{
							emu->V[(opcode & 0x0F00) >> 8] = i;
							keyPress = 1;
						}
					}

					// If we didn't received a keypress, skip this cycle and try again.
					if(!keyPress)
						return;

					emu->pc += 2;
				}
				break;

				case 0x0015: // FX15: Sets the delay timer to VX
					emu->delay_timer = emu->V[(opcode & 0x0F00) >> 8];
					emu->pc += 2;
				break;

				case 0x0018: // FX18: Sets the sound timer to VX
					emu->sound_timer = emu->V[(opcode & 0x0F00) >> 8];
					emu->pc += 2;
				break;

				case 0x001E: // FX1E: Adds VX to I
					if(emu->I + emu->V[(opcode & 0x0F00) >> 8] > 0xFFF)	// VF is set to 1 when range overflow (I+VX>0xFFF), and 0 when there isn't.
						emu->V[0xF] = 1;
					else
						emu->V[0xF] = 0;
					emu->I += emu->V[(opcode & 0x0F00) >> 8];
					emu->pc += 2;
				break;

				case 0x0029: // FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font
					emu->I = emu->V[(opcode & 0x0F00) >> 8] * 0x5;
					emu->pc += 2;
				break;

				case 0x0033: // FX33: Stores the Binary-coded decimal representation of VX at the addresses I, I plus 1, and I plus 2
					emu->memory[emu->I]     = emu->V[(opcode & 0x0F00) >> 8] / 100;
					emu->memory[emu->I + 1] = (emu->V[(opcode & 0x0F00) >> 8] / 10) % 10;
					emu->memory[emu->I + 2] = (emu->V[(opcode & 0x0F00) >> 8] % 100) % 10;
					emu->pc += 2;
				break;

				case 0x0055: // FX55: Stores V0 to VX in emu->memory starting at address I
					for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
						emu->memory[emu->I + i] = emu->V[i];

					// On the original interpreter, when the operation is done, I = I + X + 1.
					emu->I += ((opcode & 0x0F00) >> 8) + 1;
					emu->pc += 2;
				break;

				case 0x0065: // FX65: Fills V0 to VX with values from emu->memory starting at address I
					for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
						emu->V[i] = emu->memory[emu->I + i];

					// On the original interpreter, when the operation is done, I = I + X + 1.
					emu->I += ((opcode & 0x0F00) >> 8) + 1;
					emu->pc += 2;
				break;

				default:
					printf ("Unknown opcode [0xF000]: 0x%X\n", opcode);
			}
		break;

		default:
			printf ("Unknown opcode: 0x%X\n", opcode);
	}

	// Update timers
	if(emu->delay_timer > 0)
		emu->delay_timer--;
}
