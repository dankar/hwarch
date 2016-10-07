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

// Indirect. [Val + Offset]
template <uint8_t memory_access_width, class T, class O>
class Indirect
{
private:
	T m_val;
	O m_offset;
public:
	void GetString(std::stringstream &s, CPU *cpu)
	{
		// [val.GetString + m_Offset]
		if (memory_access_width == 32)
			s << "d ";
		if (memory_access_width == 16)
			s << "w ";
		if (memory_access_width == 8)
			s << "b ";
		s << "[";
		m_val.GetString(s, cpu);
		if (m_offset.GetSize())
		{
			s << " + ";
			m_offset.GetString(s, cpu);
			s << "]";
		}
		else
			s << "]";
	}
	uint64_t Parse(uint64_t operation)
	{
		m_val.Parse(operation);
		operation <<= m_val.GetSize();
		m_offset.Parse(operation);
		operation <<= m_offset.GetSize();
		return operation;
	}
	static uint32_t GetSize()
	{
		return T::GetSize() + O::GetSize();
	}
	uint32_t GetValue(CPU *cpu)
	{
		uint32_t ptr = m_val.GetValue(cpu) + m_offset.GetValue(cpu);
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
		uint32_t ptr = m_val.GetValue(cpu) + m_offset.GetValue(cpu);
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

typedef uint32_t(*OperationFunction)(CPU *cpu, uint32_t arg1, uint32_t arg2);



template <uint8_t op_code, OperationFunction func, bool update_ip, class result_val, class operand1, class operand2, uint8_t padding_bits>
class Operation : public BaseOperation
{
private:
	CPU *m_cpu;
	const char *m_assembler;
public:
	static void Register(CPU *cpu, const char* str)
	{
		BaseOperation *op = new Operation<op_code, func, update_ip, result_val, operand1, operand2, padding_bits>(cpu, str);
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
		result_val result;
		operand1 op1;
		operand2 op2;
		bool anything_printed = false;
		// Skip opcode
		operation <<= 8;

		operation = result.Parse(operation);
		operation = op1.Parse(operation);
		operation = op2.Parse(operation);

		s << m_assembler << " ";

		if (result.GetSize())
		{
			anything_printed = true;
			result.GetString(s, m_cpu);
		}

		if (op1.GetSize())
		{
			if(anything_printed)
				s << ", ";
			op1.GetString(s, m_cpu);
			anything_printed = true;
		}
		if (op2.GetSize())
		{
			if (anything_printed)
				s << ", ";
			op2.GetString(s, m_cpu);
			anything_printed = true;
		}
	}
	void Execute(uint64_t operation)
	{
		result_val result;
		operand1 op1;
		operand2 op2;
		uint32_t res;
		// Skip opcode
		operation <<= 8;

		operation = result.Parse(operation);
		operation = op1.Parse(operation);
		operation = op2.Parse(operation);

		res = func(m_cpu, op1.GetValue(m_cpu), op2.GetValue(m_cpu));

		if (res & 0x80000000)
			m_cpu->m_state.registers[CPU::FLAGS] |= CPU::SIGN;
		else
			m_cpu->m_state.registers[CPU::FLAGS] &= ~CPU::SIGN;

		if (res == 0)
			m_cpu->m_state.registers[CPU::FLAGS] |= CPU::ZERO;
		else
			m_cpu->m_state.registers[CPU::FLAGS] &= ~CPU::ZERO;

		result.SetValue(res, m_cpu);

		if (update_ip || res)
			m_cpu->m_state.ip += GetSize() / 8;
	}
	uint32_t GetSize()
	{
		return 8 + result_val::GetSize() + operand1::GetSize() + operand2::GetSize() + padding_bits;
	}
};