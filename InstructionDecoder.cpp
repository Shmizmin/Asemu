#include "InstructionDecoder.hpp"
#include "Literals.hpp"
#include "Addressing.hpp"

#include <algorithm>

asemu::Instruction asemu::InstructionDecoder::decode(std::vector<std::uint8_t>& bytes) noexcept
{
	bool hasOffset = (bytes[1z] == asemu::AddressingMode::MEM_RELATIVE or bytes[1z] == asemu::AddressingMode::REG_RELATIVE);
	
	Instruction insn;

	insn.encoding = bytes[0z];

	const auto& amode1 = bytes[1z];
	const auto& opval1 = (hasOffset) ? bytes[2z] : 0uc;
	const auto& relof1 = (hasOffset) ? bytes[3z] : bytes[2z];

	const auto& amode2 = (hasOffset) ? bytes[4z] : bytes[3z];
	const auto& opval2 = (hasOffset) ? bytes[5z] : bytes[4z];
	const auto& relof2 = (hasOffset) ? bytes[6z] : bytes[5z];

	insn.operands.emplace_back(asemu::Operand{ amode1, opval1, relof1 });
	insn.operands.emplace_back(asemu::Operand{ amode2, opval2, relof2 });

	insn.µOps = µOpMap[bytes[0z]];

	return insn;
}

void asemu::InstructionDecoder::defuse(const std::vector<std::uint8_t>& bytes) noexcept
{
	auto find = [&](std::uint8_t val)
	{
		std::uint8_t out;

		std::for_each
		(
			asemu::instructionMap.begin(), asemu::instructionMap.end(),
			[&](const std::pair<std::string, std::tuple<std::uint8_t, std::uint8_t>>& p)
			{
				if (std::get<0>(p.second) == val)
				{
					out = std::get<1>(p.second);
				}
			}
		);

		return out;
	};

	auto step = [&](std::uint8_t val)
	{
		auto returnVal = 0uc;
		
		switch (val)
		{
		case asemu::AddressingMode::NULL_ADDRESSING:
			break;

		case asemu::AddressingMode::MEM_RELATIVE:
			[[fallthrough]];
		case asemu::AddressingMode::REG_RELATIVE:
			returnVal = 3uc;
			break;
		default:
			returnVal = 2uc;

		}
		
		return returnVal;
	};

	auto s = 0z;
	auto i = 0z;
	for (; i < bytes.size() ;)
	{
		s = i;
		
		auto operandCount = find(bytes[i]);

		for (auto j = 0z; j < operandCount; ++j)
		{
			i += step(bytes[i]);
		}

		std::vector<std::uint8_t> data;
		std::copy(bytes.begin() + s, bytes.end() + i, data.begin());

		processedBytes.emplace_back(std::move(data));
	}
}

void asemu::InstructionDecoder::decode(void) noexcept
{
	for (auto& s : processedBytes)
	{
		instructions.emplace_back(this->decode(s));
	}
}

std::vector<asemu::Instruction> asemu::InstructionDecoder::fetchInstructions(void) noexcept
{
	return this->instructions;
}