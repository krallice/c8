#include "machine.h"

// Constructor:
Machine::Machine(void) {
	memory = std::make_shared<Memory>();
	cpu = std::make_unique<Cpu>(memory);
}

void Machine::reset_machine(void) {
	this->cpu->reset_cpu();
	this->memory->reset_memory();
}

