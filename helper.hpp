#pragma once

#define MPMIO(x, y) memory.read(x)
#define MRMIO(x, y) registers[x].read(0ui16)

#define INSN_CMP(s) else if (instruction == #s) { \
		##s(operand1, operand2); } \

#define INSN(s) s(operand1, operand2)

#define args Flags flags, DATASIZE op1, DATASIZE op2

#pragma warning(disable : 26812)


using DATASIZE = std::uint16_t;
constexpr auto MAX16 = std::numeric_limits<DATASIZE>{}.max();

constexpr auto MEMSIZE = MAX16;

#pragma warning(suppress : 4455)
constexpr std::size_t operator "" z(unsigned long long n)
{
	return n;
}

std::vector<std::string> split(const std::string & str, char delim)
{
	std::vector<std::string> strings;
	std::size_t start;
	std::size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		strings.push_back(str.substr(start, end - start));
	}

	return strings;
}


void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace)
{
	std::size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}