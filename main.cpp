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

std::array registers{ Register(), Register(), Register(), Register() };

DATASIZE& programCounter = regval(3);

constexpr auto basePointer = 128ui16;

#include "alu.hpp"
#include "core.hpp"

struct CPU
{
	Core core;
	//Core worker;
} processor;

#include "microop_define.hpp"
#include "instruction_define.hpp"


auto step(DATASIZE instruction, DATASIZE operand1, DATASIZE operand2) noexcept
{
	switch (instruction)
	{
	case 0: break;
	case 1: return MPMIO(operand1, operand2); break;
	case 2: return MRMIO(operand1, operand2); break;

	case 3:
	{
		MMCPY(operand1, 126ui16);
		MMCPY(operand2, 127ui16);

		MMSUB(126ui16, 127ui16);

		//MIMOV(126ui16, 0ui16);
		//MIMOV(127ui16, 0ui16);
	}

	case 4: INSN(MMCPY); break;
	case 5: INSN(MRMOV); break;
	case 6: INSN(RMMOV); break;
	case 7: INSN(RRMOV); break;
	case 8: INSN(MIMOV); break;
	case 9: INSN(RIMOV); break;

	case 10: INSN(MMADD); break;
	case 11: INSN(MMSUB); break;
	case 12: INSN(MMMUL); break;
	case 13: INSN(MMDIV); break;
	case 14: INSN(MMSHL); break;
	case 15: INSN(MMSHR); break;

	case 16: INSN(RMADD); break;
	case 17: INSN(RMSUB); break;
	case 18: INSN(RMMUL); break;
	case 19: INSN(RMDIV); break;
	case 20: INSN(RMSHL); break;
	case 21: INSN(RMSHR); break;

	case 22: INSN(RRADD); break;
	case 23: INSN(RRSUB); break;
	case 24: INSN(RRMUL); break;
	case 25: INSN(RRDIV); break;
	case 26: INSN(RRSHL); break;
	case 27: INSN(RRSHR); break;

	case 28: INSN(UNJMP); break;
	case 29: INSN(ERJMP); break;
	case 30: INSN(NRJMP); break;
	case 31: INSN(EMJMP); break;
	case 32: INSN(NMJMP); break;

	default:
		std::cout << "Instruction not supported : ";
		return DATASIZE(-1);
	}

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
	ReplaceStringInPlace(code, "SBP", "128");
	ReplaceStringInPlace(code, "SIP", std::to_string(programCounter));
	ReplaceStringInPlace(code, "\n", "");
	auto lines = split(code, ';');

	for (auto& line : lines)
	{
		ReplaceStringInPlace(line, "MPMIO", "1");
		ReplaceStringInPlace(line, "MRMIO", "2");

		ReplaceStringInPlace(line, "MMCMP", "3");
		ReplaceStringInPlace(line, "MMCPY", "4");

		ReplaceStringInPlace(line, "MRMOV", "5");
		ReplaceStringInPlace(line, "RMMOV", "6");
		ReplaceStringInPlace(line, "RRMOV", "7");

		ReplaceStringInPlace(line, "MIMOV", "8");
		ReplaceStringInPlace(line, "RIMOV", "9");

		ReplaceStringInPlace(line, "MMADD", "10");
		ReplaceStringInPlace(line, "MMSUB", "11");
		ReplaceStringInPlace(line, "MMMUL", "12");
		ReplaceStringInPlace(line, "MMDIV", "13");
		ReplaceStringInPlace(line, "MMSHL", "14");
		ReplaceStringInPlace(line, "MMSHR", "15");

		ReplaceStringInPlace(line, "RMADD", "16");
		ReplaceStringInPlace(line, "RMSUB", "17");
		ReplaceStringInPlace(line, "RMMUL", "18");
		ReplaceStringInPlace(line, "RMDIV", "19");
		ReplaceStringInPlace(line, "RMSHL", "20");
		ReplaceStringInPlace(line, "RMSHR", "21");

		ReplaceStringInPlace(line, "RRADD", "22");
		ReplaceStringInPlace(line, "RRSUB", "23");
		ReplaceStringInPlace(line, "RRMUL", "24");
		ReplaceStringInPlace(line, "RRDIV", "25");
		ReplaceStringInPlace(line, "RRSHL", "26");
		ReplaceStringInPlace(line, "RRSHR", "27");

		ReplaceStringInPlace(line, "UOJMP", "28");

		ReplaceStringInPlace(line, "ERJMP", "29");
		ReplaceStringInPlace(line, "NRJMP", "30");

		ReplaceStringInPlace(line, "EMJMP", "31");
		ReplaceStringInPlace(line, "NMJMP", "32");
	}

	auto i = 128ui16;
	for (auto& line : lines)
	{
		auto ops = split(line, ' ');

		memory.write(i + 0ui16, DATASIZE(std::stoi(ops[0])));
		memory.write(i + 1ui16, DATASIZE(std::stoi(ops[1])));
		memory.write(i + 2ui16, DATASIZE(std::stoi(ops[2])));

		i += 3ui16;
	}

	while (true)
	{
		auto instruction = memory.read(programCounter + 0ui16);
		auto operand1    = memory.read(programCounter + 1ui16);
		auto operand2    = memory.read(programCounter + 2ui16);

		std::cout << instruction << ' ' << operand1 << ' ' << operand2 << " : " << step(instruction, operand1, operand2);

		programCounter += 3ui16;
		
		std::cin.ignore();
	}

	return EXIT_SUCCESS;
}