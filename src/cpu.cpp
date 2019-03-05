#include "cpu.h"

// Reset upon init:
Cpu::Cpu(std::shared_ptr<Memory> mem) {
	this->mem = mem;
	reset_cpu();
}

// Reset sequence:
void Cpu::reset_cpu(void) {

	// Initialise all of our values to 0, and then set our PC
	// to our entry point:

	for (int i = 0; i < cpu_register_count; i++) {
		reg[i] = 0x00;
	}

	i_reg = 0x0000;

	sp = 0x00;
	for (int i = 0; i < cpu_stack_depth; i++) {
		stack[i] = 0x0000;
	}

	sound_timer = 0x00;
	delay_timer = 0x00;

	pc = 0x0200;

	return;
}

void Cpu::run_cycle(void) {

	// Helper variables for verbosity, can be replaced with
	// inline bitwise operations, but this is a little clearer
	static uint8_t reg_x;
	static uint8_t reg_y;

	// Fetch our opcode here:

	// Switch on it
	switch (this->op & 0xF000) {

		// 1xxx JMP to addr xxx
		case 1000:
			pc = op & 0x0FFF;
			break;

		// CALL sub at 2xxx
		// Increment SP, put PC ontop of SP, set PC to xxx
		case 2000:
			stack[sp] = pc;
			++sp;
			pc = op & 0x0FFF;
			break;

		// SE 3xkk
		// Skip next instruction if Vx == kk:
		case 3000:
			reg_x = ((op & 0x0F00) >> 8);
			if (reg[reg_x] == (op & 0x00FF)) {
				increment_pc();
				increment_pc();
			} else {
				increment_pc();
			}
			break;

		// SNE 4xkk
		// Skip next instruction if Vx != kk:
		case 4000:
			reg_x = ((op & 0x0F00) >> 8);
			if (reg[reg_x] != (op & 0x00FF)) {
				increment_pc();
				increment_pc();
			} else {
				increment_pc();
			}
			break;

		// SE 5xy0 Vx Vy
		// Skip next instruction if Vx == Vy:
		case 5000:
			if (reg[(op & 0x0F00) >> 8] == reg[(op & 0x00F0) >> 4]) {
				increment_pc();
				increment_pc();
			} else {
				increment_pc();
			}
			break;

		// LD 6xkk
		case 6000:
			reg[(op & 0x0F00) >> 8] = (op & 0x00FF);
			increment_pc();
			break;

		// ADD Vx, kk
		// Set Vx = Vx + kk.
		case 7000:
			reg[(op & 0x0F00) >> 8] += (op & 0x00FF);
			increment_pc();
			break;

		case 8000:

			// Extract our X & Y values:
			reg_x = ((op & 0x0F00) >> 8);
			reg_y = ((op & 0x00F0) >> 4);

			switch (op & 0x000F) {

				// 8xy0 - LD Vx, Vy
				// Set Vx = Vy.
				case 0:
					reg[reg_x] = reg[reg_y];
					increment_pc();
					break;

				// 8xy1 - OR Vx, Vy
				// Set Vx = Vx OR Vy.
				case 1:
					reg[reg_x] |= reg[reg_y];
					increment_pc();
					break;
				
				// 8xy2 - AND Vx, Vy
				// Set Vx = Vx AND Vy.
				case 2:
					reg[reg_x] &= reg[reg_y];
					increment_pc();
					break;

				// 8xy3 - XOR Vx, Vy
				// Set Vx = Vx XOR Vy.
				case 3:
					reg[reg_x] ^= reg[reg_y];
					increment_pc();
					break;

				// 8xy4 - ADD Vx, Vy
				// Set Vx = Vx + Vy, set VF = carry.
				case 4:
					reg[reg_x] += reg[reg_x];
					if ( reg[reg_y] > (0xFF - reg[reg_x])) {
						set_carry();
					} else {
						unset_carry();
					}
					increment_pc();
					break;
			}
			break;
	}
}

// Helper function:
inline void Cpu::increment_pc(void) {
	pc += 2;
}

inline void Cpu::set_carry(void) {
	reg[0xF] = 0x01;
}

inline void Cpu::unset_carry(void) {
	reg[0xF] = 0x01;
}
