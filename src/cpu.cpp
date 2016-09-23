#include <sstream>
#include <iostream>
#include <iomanip>
#include "cpu.h"
#include "helpers.h"


CPU::CPU(uint32_t memory_size) :
	m_state({ 0 })
{
	m_state.memory = new uint8_t[memory_size];
	memset(m_operations, 0, sizeof(BaseOperation*) * 256);
}

CPU::~CPU()
{
	delete[] m_state.memory;
}

uint32_t CPU::ReadMemory32(uint32_t offset)
{
	return *(uint32_t*)&m_state.memory[offset];
}
uint16_t CPU::ReadMemory16(uint32_t offset)
{
	return *(uint16_t*)&m_state.memory[offset];
}
uint8_t CPU::ReadMemory8(uint32_t offset)
{
	return *(uint8_t*)&m_state.memory[offset];
}
uint64_t CPU::ReadMemory64(uint32_t offset)
{
	return *(uint64_t*)&m_state.memory[offset];
}
void CPU::WriteMemory64(uint32_t offset, uint64_t value)
{
	*(uint64_t*)&m_state.memory[offset] = value;
}

void CPU::WriteMemory32(uint32_t offset, uint32_t value)
{
	*(uint32_t*)&m_state.memory[offset] = value;
}
void CPU::WriteMemory16(uint32_t offset, uint16_t value)
{
	*(uint16_t*)&m_state.memory[offset] = value;
}
void CPU::WriteMemory8(uint32_t offset, uint8_t value)
{
	*(uint8_t*)&m_state.memory[offset] = value;
}

void CPU::WriteMemory(uint8_t *buffer, size_t len)
{
	memcpy(m_state.memory, buffer, len);
}

uint32_t CPU::ReadRegister(uint8_t register_num)
{
	return m_state.registers[register_num];
}

void CPU::WriteRegister(uint8_t register_num, uint32_t value)
{
	m_state.registers[register_num] = value;
}

const std::string& CPU::GetRegisterName(uint32_t register_number)
{
	return m_register_names[register_number];
}

void CPU::RegisterOp(uint8_t op_code, BaseOperation * op)
{
	m_operations[op_code] = op;
}

void CPU::AddDevice(uint32_t bar, CDevice *device)
{

}

uint64_t be(uint64_t val)
{
	uint64_t result = 0;
	uint8_t *b = (uint8_t*)&result;

	b[7] = val & 0xff;
	val >>= 8;
	b[6] = val & 0xff;
	val >>= 8;
	b[5] = val & 0xff;
	val >>= 8;
	b[4] = val & 0xff;
	val >>= 8;
	b[3] = val & 0xff;
	val >>= 8;
	b[2] = val & 0xff;
	val >>= 8;
	b[1] = val & 0xff;
	val >>= 8;
	b[0] = val & 0xff;
	val >>= 8;
	
	return result;
}

uint64_t CPU::GetOperation()
{
	uint64_t operation = ReadMemory64(m_state.ip);
	operation = be(operation);
	return operation;
}

void CPU::Cycle()
{
	uint64_t operation = GetOperation();
	uint8_t op_code = operation >> 56;

	assert(m_operations[op_code] != NULL, "invalid opcode");

	m_operations[op_code]->Execute(operation);
}

void CPU::Decompile(std::stringstream &s)
{
	uint64_t operation = GetOperation();
	uint8_t op_code = operation >> 56;
	uint32_t num_bytes = 0;

	assert(m_operations[op_code] != NULL, "invalid opcode");

	num_bytes = m_operations[op_code]->GetSize() / 8;

	s << std::setbase(16);
	s << std::setfill('0') << std::setw(8) << m_state.ip << ": ";

	for (uint32_t i = 0; i < num_bytes; i++)
	{
		s << std::setw(2) << (uint32_t)ReadMemory8(m_state.ip + i) << " ";
	}

	uint8_t padding = 40 - (8 + 1 + 3 * num_bytes);

	for (int i = 0; i < padding; i++)
	{
		s << " ";
	}

	m_operations[op_code]->GetString(s, operation);
}

void CPU::PrintState(std::stringstream &s)
{
	s << std::setbase(16);
	for (int i = 0; i < 16; i++)
	{
		s << GetRegisterName(i);
		s << " = " << m_state.registers[i] << std::endl;
	}
	s << "%ip = " << m_state.ip << std::endl;
}