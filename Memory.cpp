#include "Memory.hpp"

void asemu::Memory::read(busArgs) noexcept
{
	dataBus = bytes[addressBus];
}

void asemu::Memory::write(busArgs) noexcept
{
	bytes[addressBus] = dataBus;
}


void asemu::Register::read(busArgs) noexcept
{
	dataBus = bytes[addressBus];
}

void asemu::Register::write(busArgs) noexcept
{
	bytes[addressBus] = dataBus;
}