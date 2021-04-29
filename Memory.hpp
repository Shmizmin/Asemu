#pragma once

#include <array>

#include "Literals.hpp"

namespace asemu
{
	class Memory
	{
	public:
		static constexpr auto N = 255z;

		std::array<std::uint8_t, N> bytes;

		void read(busArgs) noexcept;
		void write(busArgs) noexcept;
	};

	class Register
	{
	public:
		static constexpr auto N = 1z;

		std::array<std::uint8_t, N> bytes;

		void read(busArgs) noexcept;
		void write(busArgs) noexcept;
	};
}