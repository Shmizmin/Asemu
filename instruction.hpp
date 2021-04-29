#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <cstdint>
#include <unordered_map>

#include "Addressing.hpp"
#include "MicroOperation.hpp"

namespace asemu
{
	struct Operand
	{
		std::uint8_t addressingMode;
		std::uint8_t encoding;
		std::uint8_t offset;
	};

	class Instruction
	{
	public:
		std::uint8_t encoding;
		std::vector<MicroOperation> �Ops;
		std::vector<Operand> operands;

		Instruction() = default;
		~Instruction() = default;

		Instruction(const Instruction&) = default;
		Instruction& operator=(const Instruction&) = default;

		Instruction(Instruction&&) = default;
		Instruction& operator=(Instruction&&) = default;

		Instruction(std::uint8_t encoding, std::vector<Operand> operands, std::vector<MicroOperation> �Ops)
			: encoding(encoding), operands(operands), �Ops(�Ops)
		{
		}
	};

	extern std::unordered_map<std::string, std::tuple<std::uint8_t, std::uint8_t>> instructionMap;
	extern std::unordered_map<std::string, std::uint8_t> registerMap;
	extern std::unordered_map<std::uint8_t, std::vector<MicroOperation>> �OpMap;
}