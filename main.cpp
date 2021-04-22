#include <cstdint>
#include <array>
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

#include "helper.hpp"
#include "flags.hpp"
#include "microop.hpp"
#include "instruction.hpp"
#include "pipeline.hpp"
#include "memory.hpp"


using Cache = Memory<8>;
using Register = Memory<1>;

Memory<MEMSIZE> memory;

std::array registers{ Register(), Register(), Register() };


#include "alu.hpp"
#include "core.hpp"

struct CPU
{
	Core core;
	//Core worker;
} processor;

#include "microop_define.hpp"
#include "instruction_define.hpp"

auto step(const std::string& code) noexcept
{
	auto ops = split(code, ' ');

	auto instruction = ops[0];

	DATASIZE operand1 = static_cast<DATASIZE>(std::stoi(ops[1])), operand2;

	if (ops.size() >= 3) operand2 = static_cast<DATASIZE>(std::stoi(ops[2]));

	if (instruction == "MMCMP")
	{
		MMCPY(operand1, 100ui16);
		MMCPY(operand2, 101ui16);

		MMSUB(100ui16, 101ui16);

		MIMOV(100ui16, 0ui16);
		MIMOV(101ui16, 0ui16);
	}

	if (instruction == "MPMIO")
		return MPMIO(operand1);

	if (instruction == "MRMIO")
		return MRMIO(operand1);

	INSN_CMP(MMCPY)
	INSN_CMP(RMCPY)
	INSN_CMP(RIMOV)
	INSN_CMP(MIMOV)
	INSN_CMP(MMADD)
	INSN_CMP(MMSUB)
	INSN_CMP(MMMUL)
	INSN_CMP(MMDIV)
	INSN_CMP(MMSHL)
	INSN_CMP(MMSHR)

	INSN_CMP(RMADD)
	INSN_CMP(RMSUB)
	INSN_CMP(RMMUL)
	INSN_CMP(RMDIV)
	INSN_CMP(RMSHL)
	INSN_CMP(RMSHR)

	return 0ui16;
}


int main(void)
{
	std::ifstream t("./assembly.txt");
	std::string code;

	t.seekg(0, std::ios::end);
	code.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	code.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	ReplaceStringInPlace(code, "SAX", "0");
	ReplaceStringInPlace(code, "SBX", "1");
	ReplaceStringInPlace(code, "SSP", "2");
	ReplaceStringInPlace(code, "\n", "");
	auto lines = split(code, ';');

	auto curIndex = 0z;

	while (true)
	{
		if (curIndex + 1z <= lines.size())
		{
			std::cout << lines[curIndex] << " : " << step(lines[curIndex]);
			++curIndex;
		}

		else
		{
			std::cout << "Can't step another line!" << std::endl;
		}

		std::cin.get();
	}

	return 0;
}