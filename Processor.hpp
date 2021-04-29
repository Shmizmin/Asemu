#pragma once

#include <cstdint>
#include <iostream>

#include "Instruction.hpp"
#include "InstructionDecoder.hpp"
#include "Literals.hpp"
#include "Memory.hpp"

namespace asemu
{
	class Processor
	{
	public:
		InstructionDecoder decoder;

		std::uint8_t addressBus, dataBus;

		Memory memory;
		std::array<Register, 7z> registers;

		std::vector<Instruction> instructions;

		struct ALU
		{
			std::uint8_t num1, num2;
		} alu;

		explicit Processor(std::vector<std::uint8_t>& inBytes) noexcept
			: decoder(inBytes)
		{
			for (auto a = 0z; a < inBytes.size(); ++a)
			{
				addressBus = (uint8_t)a;
				dataBus = inBytes[a];

				memory.write(buses);
			}
			
			instructions = decoder.fetchInstructions();

			execute(decoder.processedBytes);
		}

		void execute(std::vector<std::vector<std::uint8_t>> bytes) noexcept;
	};
}