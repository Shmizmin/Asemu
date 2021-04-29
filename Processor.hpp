#pragma once

#include <cstdint>

#include "Instruction.hpp"
#include "InstructionDecoder.hpp"
#include "Literals.hpp"

namespace asemu
{
	class Processor
	{
	private:
		InstructionDecoder decoder;

		std::uint8_t addressBus, dataBus;

		std::vector<Instruction> instructions;

	public:
		explicit Processor(std::vector<std::uint8_t>& inBytes) noexcept
			: decoder(inBytes)
		{
			
			
			//instructions = decoder.fetchInstructions();


		}
	};
}