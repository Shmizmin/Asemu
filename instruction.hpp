#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <cstdint>
#include <unordered_map>

#include "MicroOperation.hpp"
#include "Addressing.hpp"

namespace asemu
{
	struct Operand
	{
		std::uint8_t encoding;
		asemu::AddressingMode addressingMode;
	};

	class Instruction
	{
	private:
		std::uint8_t encoding;
		std::vector<MicroOperation> 킣ps;
		std::vector<Operand> operands;

		Instruction() = delete;
		~Instruction() = default;

		Instruction(const Instruction&) = delete;
		Instruction& operator=(const Instruction&) = delete;

	public:
		Instruction(Instruction&&) = default;
		Instruction& operator=(Instruction&&) = default;

		Instruction(std::uint8_t encoding, std::vector<MicroOperation> 킣ps, std::vector<Operand> operands)
			: encoding(encoding), 킣ps(킣ps), operands(operands)
		{
		}
	};

	extern std::unordered_map<std::string, std::pair<std::uint8_t, std::uint8_t>> instructionMap;
	extern std::unordered_map<std::string, std::uint8_t> registerMap;
}