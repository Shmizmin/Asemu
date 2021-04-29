#include "InstructionDecoder.hpp"
#include "Literals.hpp"

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

std::vector<std::vector<std::uint8_t>> asemu::InstructionDecoder::defuse(std::vector<std::uint8_t>& bytes) noexcept
{
	return std::vector<std::vector<std::uint8_t>>{ { bytes } };
}

auto asemu::InstructionDecoder::decode(void) noexcept
{
	for (auto& s : processedBytes)
	{
		instructions.emplace_back(this->decode(s));
	}
}

auto asemu::InstructionDecoder::fetchInstructions(void) noexcept
{
	return this->instructions;
}