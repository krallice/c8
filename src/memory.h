#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

const uint16_t memory_limit = 0x1000;

class Memory {
	private:
		uint8_t ram[memory_limit];

	public:
		Memory(void);
		void reset_memory(void);
		uint8_t read_byte(const uint16_t addr);
		void write_byte(const uint16_t addr, const uint8_t value);
};

#endif
