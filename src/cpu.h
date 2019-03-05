#ifndef CPU_H
#define CPU_H

#include <memory>
#include <stdint.h>

#include "memory.h"

const int cpu_register_count = 16;
const int cpu_stack_depth = 16;

class Cpu {
	private:
		// V0 to VF Registers:
		uint8_t reg[cpu_register_count]; 	

		// Memory Register:
		uint16_t i_reg;

		// Stack Pointer and Stack itself:
		uint8_t sp;
		uint16_t stack[cpu_stack_depth];

		// Program Counter:
		uint16_t pc;

		// Current opcode:
		uint16_t op;

		// Timers:
		uint8_t delay_timer;
		uint8_t sound_timer;

		// Memory Map:
		std::shared_ptr<Memory> mem;

		// Helper Functions:
		inline void increment_pc(void);
		inline void set_carry(void);
		inline void unset_carry(void);

	public:
		Cpu(std::shared_ptr<Memory> mem);
		void reset_cpu(void);
		void run_cycle(void);
};

#endif
