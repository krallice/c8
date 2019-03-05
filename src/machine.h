#ifndef MACHINE_H
#define MACHINE_H

#include <memory>
#include <string>

#include "cpu.h"
#include "memory.h"

class Machine {
	private:
		std::shared_ptr<Memory> memory;
		std::unique_ptr<Cpu> cpu;
	public:
		Machine(void);
		void reset_machine(void);
		int load_rom(std::string rom);
};
#endif
