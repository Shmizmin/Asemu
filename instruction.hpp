#pragma once

struct CallingInformation
{
	MicroOp op;
	Flags flags;
};

struct Instruction
{
	std::vector<CallingInformation> ops;

	auto operator()(const DATASIZE& operand1, const DATASIZE& operand2 = 0ui16) noexcept
	{
		for (auto& m : ops)
		{
			m.op(m.flags, operand1, operand2);
		}
	}
};