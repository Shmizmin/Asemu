#pragma once

#include <cstdint>
#include "Literals.hpp"

namespace asemu
{
	enum AddressingMode : std::uint8_t
	{
		NULL_ADDRESSING = 0uc,

		REG_ABSOLUTE = 1uc,
		MEM_ABSOLUTE = 2uc,

		REG_DEREFERENCE = 3uc,
		MEM_DEREFERENCE = 4uc,

		REG_RELATIVE = 5uc,
		MEM_RELATIVE = 6uc,

		IMMEDIATE_DATA = 7uc
	};

	enum EncodingScheme : std::uint8_t
	{
		ADDITION       = 0b00010000uc,
		SUBTRACTION    = 0b00100000uc,
		MULTIPLICATION = 0b00110000uc,
		DIVISION       = 0b01000000uc,
		SHIFT_LEFT     = 0b01010000uc,
		SHIFT_RIGHT    = 0b01100000uc,
		MODULUS        = 0b01110000uc
	};

	constexpr auto OPERATOR_MASK = 0b11110000uc;
	constexpr auto DATA_MASK     = 0b00001111uc;
}