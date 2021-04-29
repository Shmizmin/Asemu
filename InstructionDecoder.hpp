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
			processedBytes = defuse(rawBytes);
		}

		auto decode(void) noexcept;
		auto fetchInstructions(void) noexcept;

	private:
		std::vector<std::uint8_t> rawBytes;
		std::vector<std::vector<std::uint8_t>> processedBytes;

		std::vector<asemu::Instruction> instructions;

		asemu::Instruction decode(std::vector<std::uint8_t>& bytes) noexcept;
		std::vector<std::vector<std::uint8_t>> defuse(std::vector<std::uint8_t>& bytes) noexcept;
	};
}