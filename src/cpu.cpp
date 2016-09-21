#include "cpu.h"

CCPU::CCPU(uint32_t memory_size) :
	m_state({ 0 })
{
	m_state.memory = new uint8_t[memory_size];

}

CCPU::~CCPU()
{
	delete[] m_state.memory;
}

void CCPU::AddDevice(uint32_t bar, CDevice *device)
{

}

void CCPU::Cycle()
{

}
