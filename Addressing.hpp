#pragma once

#include <cstdint>

namespace asemu
{
	enum class AddressingMode : std::uint8_t
	{
		ABSOLUTE_REG,
		ABSOLUTE_MEM,

		DEREFERENCE_REG,
		DEREFERENCE_MEM,

		RELATIVE,
		IMMEDIATE
	};

	constexpr auto reg_absolute = 0b00000001ui8;
	constexpr auto mem_absolute = 0b00000010ui8;
	constexpr auto reg_deref    = 0b00000011ui8;
	constexpr auto mem_deref    = 0b00000100ui8;
	constexpr auto reg_relative = 0b00000101ui8;
	constexpr auto mem_relative = 0b00000110ui8;
	constexpr auto immediate    = 0b00000111ui8;

	constexpr auto relative_sign_bit = 0b10000000ui8;
	constexpr auto relative_data_bit = 0b01111000ui8;
}