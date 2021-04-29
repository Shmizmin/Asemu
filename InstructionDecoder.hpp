#pragma once

#include <cstdint>
#include <vector>

#include "Instruction.hpp"

namespace asemu
{
	class InstructionDecoder
	{
	public:
		explicit InstructionDecoder(std::vector<std::uint8_t>& bytes) noexcept
			: rawBytes(bytes)
		{
			defuse(rawBytes);
			decode();
		}

		void decode(void) noexcept;
		std::vector<Instruction> fetchInstructions(void) noexcept;

		std::vector<std::uint8_t> rawBytes;
		std::vector<std::vector<std::uint8_t>> processedBytes;

		std::vector<asemu::Instruction> instructions;

		asemu::Instruction decode(std::vector<std::uint8_t>& bytes) noexcept;
		void defuse(const std::vector<std::uint8_t>& bytes) noexcept;
	};
}