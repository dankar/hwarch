#pragma once

#include <stdint.h>
#include <vector>

class CDevice
{
public:
	virtual uint8_t ReadRegister(uint32_t reg) = 0;
	virtual void WriteRegister(uint32_t reg, uint8_t val) = 0;
};

class CCPU
{
public:
	enum registers_e
	{
		R0 = 0,
		R1 = 1,
		R2 = 2,
		R3 = 3,
		R4 = 4,
		R5 = 5,
		R6 = 6,
		R7 = 7,
		R8 = 8,
		R9 = 9,
		R10 = 10,
		R11 = 11,
		R12 = 12,

		R13 = 13,
		FLAGS = 13,

		R14 = 14,
		FP = 14,

		R15 = 15,
		SP = 15
	};

	enum flags_e
	{
		SIGN = 0x1,
		ZERO = 0x2,
		CARRY = 0x4,
		INTERRUPT_ENABLE = 0x80
	};
private:
	struct cpu_state_t
	{
		uint32_t registers[16];
		uint32_t ip;
		uint8_t *memory;
	};

	cpu_state_t m_state;
	
	std::vector<CDevice> m_devices;
public:
	CCPU(uint32_t memory_size);
	~CCPU();
	void AddDevice(uint32_t bar, CDevice *device);
	void Cycle();
};
