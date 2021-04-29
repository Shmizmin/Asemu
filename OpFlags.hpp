#pragma once

#include <cstdint>

enum class OpFlags : std::uint8_t
{
	MEMORY_IN,
	MEMORY_OUT,

	ALU_IN,
	ALU_OUT,

	REGISTER_IN,
	REGISTER_OUT,

	ADDRESS_BUS_ENABLE,
	ADDRESS_BUS_DISABLE,

	DATA_BUS_ENABLE,
	DATA_BUS_DISABLE
};