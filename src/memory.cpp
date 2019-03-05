#include "memory.h"

Memory::Memory(void) {
	this->reset_memory();
}

void Memory::reset_memory(void) {
	for (int i = 0; i < memory_limit; i++) {
		this->ram[i] = 0x00;
	}
}

uint8_t Memory::read_byte(const uint16_t addr) {
	if ( addr >= memory_limit ) {
		return 0x00;
	}
	return this->ram[addr];
}

void Memory::write_byte(const uint16_t addr, const uint8_t value) {
	if ( addr < memory_limit ) {
		this->ram[addr] = value;
	}
}
