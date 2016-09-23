#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdint.h>
#include <vector>
#include "helpers.h"

class BaseOperation
{
public:
	virtual bool UpdateIP() = 0;
	virtual void GetString(std::stringstream &s, uint64_t operation) = 0;
	virtual void Execute(uint64_t operation) = 0;
	virtual uint32_t GetSize() = 0;
};

class CDevice
{
public:
	virtual uint8_t ReadRegister(uint32_t reg) = 0;
	virtual void WriteRegister(uint32_t reg, uint8_t val) = 0;
};

class CPU
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

	std::string m_register_names[16] = { "%r0", "%r1", "%r2", "%r3", "%r4", "%r5", "%r6", "%r7", "%r8", "%r9", "%r10", "%r11", "%r12", "%flags", "%fp", "%sp" };

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

	
	
	std::vector<CDevice> m_devices;

	BaseOperation *m_operations[256];

	uint64_t GetOperation();
public:
	cpu_state_t m_state;
	CPU(uint32_t memory_size);
	~CPU();

	uint64_t ReadMemory64(uint32_t offset);
	uint32_t ReadMemory32(uint32_t offset);
	uint16_t ReadMemory16(uint32_t offset);
	uint8_t ReadMemory8(uint32_t offset);

	void WriteMemory64(uint32_t offset, uint64_t value);
	void WriteMemory32(uint32_t offset, uint32_t value);
	void WriteMemory16(uint32_t offset, uint16_t value);
	void WriteMemory8(uint32_t offset, uint8_t value);

	void WriteMemory(uint8_t *buffer, size_t len);

	uint32_t ReadRegister(uint8_t register_num);
	void WriteRegister(uint8_t register_num, uint32_t value);

	const std::string& GetRegisterName(uint32_t register_number);

	void RegisterOp(uint8_t op_code, BaseOperation *op);
	void AddDevice(uint32_t bar, CDevice *device);
	void Cycle();

	void Decompile(std::stringstream &s);

	void PrintState(std::stringstream &s);
};

inline uint32_t GetBitsValue(uint64_t val, uint32_t bits)
{
	if (bits == 0)
		return 0;
	else
		return (val >> (64 - bits)) & ((2ULL << bits) - 1);
}

template <uint32_t bits>
class NullVal
{
public:
	void GetString(std::stringstream &s, CPU *cpu)
	{
		if (bits)
			s << "0";
	}

	uint64_t Parse(uint64_t operation)
	{
		return operation << bits;
	}
	static uint32_t GetSize()
	{
		return bits;
	}
	uint32_t GetValue(CPU *cpu)
	{
		return 0;
	}
	void SetValue(uint32_t val, CPU *cpu)
	{
	}
};

template <uint32_t bits>
class Immediate
{
private:
	uint32_t m_value;
public:
	void GetString(std::stringstream &s, CPU *cpu)
	{
		s << "0x" << m_value;
	}
	uint64_t Parse(uint64_t operation)
	{
		m_value = GetBitsValue(operation, bits);
		return operation << bits;
	}
	static uint32_t GetSize()
	{
		return bits;
	}
	uint32_t GetValue(CPU *cpu)
	{
		return  m_value;
	}
	void SetValue(uint32_t val, CPU *cpu)
	{
		assert(0, "Can not assign value to immediate");
	}
};

// Indirect. [Val + Offset]
template <uint8_t memory_access_width, class T, uint32_t bits>
class Indirect
{
private:
	T m_val;
	uint32_t m_offset;
public:
	void GetString(std::stringstream &s, CPU *cpu)
	{
		// [val.GetString + m_Offset]
		s << "[";
		m_val.GetString(s, cpu);
		if (m_offset)
			s << " + " << m_offset << "]";
		else
			s << "]";
	}
	uint64_t Parse(uint64_t operation)
	{
		m_val.Parse(operation);
		operation <<= m_val.GetSize();
		m_offset = GetBitsValue(operation, bits);
		return operation << bits;
	}
	static uint32_t GetSize()
	{
		return T::GetSize() + bits;
	}
	uint32_t GetValue(CPU *cpu)
	{
		uint32_t ptr = m_val.GetValue(cpu) + m_offset;
		if (memory_access_width == 8)
		{
			return cpu->ReadMemory8(ptr);
		}
		else if (memory_access_width == 16)
		{
			return cpu->ReadMemory16(ptr);
		}
		else if (memory_access_width == 32)
		{
			return cpu->ReadMemory32(ptr);
		}
		else
		{
			assert(0, "Invalid memory access width for indirect");
			return 0;
		}
	}
	void SetValue(uint32_t val, CPU *cpu)
	{
		uint32_t ptr = m_val.GetValue(cpu) + m_offset;
		if (memory_access_width == 8)
		{
			return cpu->WriteMemory8(ptr, val & 0xff);
		}
		else if (memory_access_width == 16)
		{
			return cpu->WriteMemory16(ptr, val & 0xffff);
		}
		else if (memory_access_width == 32)
		{
			return cpu->WriteMemory32(ptr, val);
		}
		else
		{
			assert(0, "Invalid memory access width for indirect");
		}
	}
};

template <uint32_t bits>
class Register
{
private:
	uint8_t m_register_number;
public:
	void GetString(std::stringstream &s, CPU *cpu)
	{
		s << cpu->GetRegisterName(m_register_number);
	}
	uint64_t Parse(uint64_t operation)
	{
		m_register_number = GetBitsValue(operation, bits);
		return operation << bits;
	}
	static uint32_t GetSize()
	{
		return bits;
	}
	uint32_t GetValue(CPU *cpu)
	{
		return cpu->ReadRegister(m_register_number);
	}
	void SetValue(uint32_t val, CPU *cpu)
	{
		return cpu->WriteRegister(m_register_number, val);
	}
};

typedef uint32_t(*OperationFunction)(CPU *cpu, uint32_t arg1, uint32_t arg2);



template <uint8_t op_code, OperationFunction func, bool update_ip, class lval, class rval1, class rval2, uint8_t padding>
class Operation : public BaseOperation
{
private:
	CPU *m_cpu;
	const char *m_assembler;
public:
	static void Register(CPU *cpu, const char* str)
	{
		BaseOperation *op = new Operation<op_code, func, update_ip, lval, rval1, rval2, padding>(cpu, str);
		cpu->RegisterOp(op_code, op);
	}
	Operation(CPU *cpu, const char *assembler) :
		m_cpu(cpu)
	{
		m_assembler = assembler;
	}
	bool UpdateIP()
	{
		return update_ip;
	}
	void GetString(std::stringstream &s, uint64_t operation)
	{
		lval l;
		rval1 a1;
		rval2 a2;
		// Skip opcode
		operation <<= 8;

		operation = l.Parse(operation);
		operation = a1.Parse(operation);
		operation = a2.Parse(operation);

		s << m_assembler << " ";

		l.GetString(s, m_cpu);

		if (a1.GetSize())
		{
			s << ", ";
			a1.GetString(s, m_cpu);
		}
		if (a2.GetSize())
		{
			s << ", ";
			a2.GetString(s, m_cpu);
		}
	}
	void Execute(uint64_t operation)
	{
		lval l;
		rval1 a1;
		rval2 a2;
		uint32_t result;
		// Skip opcode
		operation <<= 8;

		operation = l.Parse(operation);
		operation = a1.Parse(operation);
		operation = a2.Parse(operation);

		result = func(m_cpu, a1.GetValue(m_cpu), a2.GetValue(m_cpu));

		if (result & 0x80000000)
			m_cpu->m_state.registers[CPU::FLAGS] |= CPU::SIGN;
		else
			m_cpu->m_state.registers[CPU::FLAGS] &= ~CPU::SIGN;

		if (result == 0)
			m_cpu->m_state.registers[CPU::FLAGS] |= CPU::ZERO;
		else
			m_cpu->m_state.registers[CPU::FLAGS] &= ~CPU::ZERO;

		l.SetValue(result, m_cpu);

		if (update_ip || result)
			m_cpu->m_state.ip += GetSize() / 8;
	}
	uint32_t GetSize()
	{
		return 8 + lval::GetSize() + rval1::GetSize() + rval2::GetSize() + padding;
	}
};