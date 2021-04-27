#include "Assembler.hpp"
#include "Instruction.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>

#pragma warning(suppress : 4455)
inline constexpr std::size_t operator"" z(unsigned long long n) noexcept
{
	return n;
}

inline bool isInt(const std::string& s, int base) noexcept
{
	if (s.empty() || std::isspace(s[0])) return false;
	char* p;
	std::strtol(s.c_str(), &p, base);
	return (*p == 0);
}

inline bool isPositiveInt(const std::string& s, int base) noexcept
{
	if (s.empty() || std::isspace(s[0]) || s[0] == '-') return false;
	char* p;
	std::strtol(s.c_str(), &p, base);
	return (*p == 0);
}

inline bool isNegativeInt(const std::string& s, int base) noexcept
{
	if (s.empty() || std::isspace(s[0]) || s[0] != '-') return false;
	char* p;
	std::strtol(s.c_str(), &p, base);
	return (*p == 0);
}

int hexToInt(std::string hex) noexcept
{
	std::stringstream stream;
	stream << std::dec << hex;
	return std::stoi(stream.str());
}

std::string intToHex(int num) noexcept
{
	std::stringstream stream;
	stream << std::hex << num;
	return stream.str();
}

auto asemu::Assembler::assemble(std::vector<std::string>& lines) noexcept
{
	for (auto& line : lines)
	{
		//parser.replace(line, "sax", "0");
		//replace(code, "sbx", "1");
		//replace(code, "scx", "2");
		//replace(code, "sdx", "3");
		//replace(code, "sbp", "4");
		//replace(code, "ssp", "5");
		//replace(code, "sip", "6");

		const auto&& tokens = parser.split(line, ' ');

		auto&& operands = parser.split(tokens[1], ',');
		const auto& instruction = tokens[0];


		auto& decoded = asemu::instructionMap[instruction];

		auto& encoding = std::get<0>(decoded);
		auto& size = std::get<1>(decoded);

		machineCode.emplace_back(std::move(encoding));
	
		if (size == operands.size())
		{
			for (auto s = 0z; s < size; ++s)
			{
				auto percent = operands[s].find('%');
				auto pound = operands[s].find('#');
				auto ampersand = operands[s].find('&');
				auto star = operands[s].find('*');

				auto test = [&](std::size_t num)
				{
					return (num != -1z);
				};

				using m = asemu::AddressingMode;
				m mode;

				auto myAlpha = [&](char ch) -> bool
				{
					return std::isalpha(static_cast<unsigned char>(ch));
				};




				if (test(percent))
				{
					//implement relative addressing here
				}



				else if (test(pound))
				{
					parser.replace(operands[s], "#", "");

					if (test(operands[s].find('$')))
					{
						parser.replace(operands[s], "$", "");

						machineCode.emplace_back(asemu::immediate);
						machineCode.emplace_back(static_cast<std::uint8_t>(hexToInt(operands[s])));
					}

					else if (test(operands[s].find('@')))
					{
						parser.replace(operands[s], "@", "");

						machineCode.emplace_back(asemu::immediate);
						machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(operands[s])));
					}
				}

				else if (test(ampersand))
				{
					if (myAlpha(operands[s][ampersand + 1z]))
					{
						parser.replace(operands[s], "&", "");

						auto index = asemu::registerMap[operands[s]];

						machineCode.emplace_back(asemu::reg_deref);
						machineCode.emplace_back(index);
					}

					else
					{
						parser.replace(operands[s], "&", "");

						machineCode.emplace_back(asemu::mem_deref);

						if (operands[s][ampersand + 2z] == '$')
						{
							machineCode.emplace_back(static_cast<std::uint8_t>(hexToInt(operands[s])));
						}

						if (operands[s][ampersand + 2z] == '@')
						{
							machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(operands[s])));
						}

						else std::exit(3);
					}
				}

				else if (test(star))
				{
					if (myAlpha(operands[s][ampersand + 1z]))
					{
						parser.replace(operands[s], "*", "");

						auto index = asemu::registerMap[operands[s]];

						machineCode.emplace_back(asemu::reg_absolute);
						machineCode.emplace_back(index);
					}

					else
					{
						parser.replace(operands[s], "*", "");

						machineCode.emplace_back(asemu::mem_absolute);

						if (operands[s][ampersand + 2z] == '$')
						{
							machineCode.emplace_back(static_cast<std::uint8_t>(hexToInt(operands[s])));
						}

						if (operands[s][ampersand + 2z] == '@')
						{
							machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(operands[s])));
						}

						else std::exit(3);
					}
				}


				switch (mode)
				{
				case m::ABSOLUTE:


					break;

				case m::RELATIVE:
					parser.replace(operands[s], "%[", "");
					parser.replace(operands[s], "]", "");

					auto& expr = operands[s];

					break;

				case m::IMMEDIATE:
					parser.replace(operands[s], "#", "");

					if (test(operands[s].find('$')))
					{
						parser.replace(operands[s], "$", "");
						
						machineCode.emplace_back(asemu::imm);
						machineCode.emplace_back(static_cast<std::uint8_t>(hexToInt(operands[s])));
					}

					else if (test(operands[s].find('@')))
					{
						parser.replace(operands[s], "@", "");

						machineCode.emplace_back(asemu::imm);
						machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(operands[s])));
					}

					else break;
				}





				
			}
		}

		else
		{
			std::puts("Mismatched operand count for specified instruction");
			std::exit(2);
		}

	}
}