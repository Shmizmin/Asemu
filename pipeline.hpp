#pragma once

class Pipeline
{
private:
	std::deque<Instruction> instructions;

public:
	auto decompose(std::size_t index)
	{
		if (index < instructions.size())
			return instructions[index].ops;
	}

	auto fetch()
	{

	}

	auto predict()
	{

	}


	auto peek()
	{

	}

	auto poke()
	{

	}

};