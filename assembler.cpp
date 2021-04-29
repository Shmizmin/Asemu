#include "Assembler.hpp"
#include "Instruction.hpp"
#include "Literals.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
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

void asemu::Assembler::assemble(std::vector<std::string>& lines) noexcept
{
	for (auto& line : lines)
	{
		if (line[0z] == '/')
			continue;
		
		//auto tokens = parser.split(line, ' ');
		//auto operands = parser.split(tokens[1], ',');
		//auto operands
		std::vector<std::string> tokens;
		std::vector<std::string> operands;

		tokens = parser.split(line, ':');

		if (tokens.size() != 0z)
		{
			operands = parser.split(tokens[1], ',');
		}
		auto& instruction = tokens[0];



		auto& decoded = asemu::instructionMap[instruction];
		auto& encoding = std::get<0>(decoded);
		auto& size = std::get<1>(decoded);

		machineCode.emplace_back(encoding);
	
		auto&& sizeT = static_cast<std::size_t>(size);

		if (sizeT == operands.size())
		{
			for (auto s = 0z; s < sizeT; ++s)
			{
				auto percent = operands[s].find('%');
				auto pound = operands[s].find('#');
				auto ampersand = operands[s].find('&');
				auto star = operands[s].find('*');

				auto test = [&](std::size_t num) -> bool
				{
					return (num != std::string::npos);
				};

				auto myAlpha = [&](char ch) -> bool
				{
					return std::isalpha(static_cast<std::uint8_t>(ch));
				};

				if (test(percent))
				{
					std::puts("Found an relative data token!");
					
					parser.replace(operands[s], "%", "");
					parser.replace(operands[s], "[", "");
					parser.replace(operands[s], "]", "");
				
					auto parts = split(operands[s], " ");

					auto encoded = 0uc;
					switch (parts[1z][0z])
					{
						case '+': encoded |= asemu::EncodingScheme::ADDITION;       break;
						case '-': encoded |= asemu::EncodingScheme::SUBTRACTION;    break;
						case '*': encoded |= asemu::EncodingScheme::MULTIPLICATION; break;
						case '/': encoded |= asemu::EncodingScheme::DIVISION;       break;
						case '<': encoded |= asemu::EncodingScheme::SHIFT_LEFT;     break;
						case '>': encoded |= asemu::EncodingScheme::SHIFT_RIGHT;    break;
						case '~': encoded |= asemu::EncodingScheme::MODULUS;        break;
					}
					encoded |= static_cast<std::uint8_t>(std::stoi(parts[2z]));
				
				
					if (myAlpha(operands[s][0z]))
					{
						machineCode.emplace_back(asemu::AddressingMode::REG_RELATIVE);
						machineCode.emplace_back(asemu::registerMap[parts[0z]]);
						machineCode.emplace_back(encoded);
					}
					
					else
					{
						machineCode.emplace_back(asemu::AddressingMode::MEM_RELATIVE);
						machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(parts[0z])));
						machineCode.emplace_back(encoded);
					}
				}
				
				else if (test(pound))
				{
					std::puts("Found an immediate data token!");
					
					parser.replace(operands[s], "#", "");
				
					if (test(operands[s].find('$')))
					{
						parser.replace(operands[s], "$", "");
				
						machineCode.emplace_back(asemu::AddressingMode::IMMEDIATE_DATA);
						machineCode.emplace_back(static_cast<std::uint8_t>(hexToInt(operands[s])));
					}
				
					else if (test(operands[s].find('@')))
					{
						parser.replace(operands[s], "@", "");
				
						machineCode.emplace_back(asemu::AddressingMode::IMMEDIATE_DATA);
						machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(operands[s])));
					}
				}
				
				else if (test(ampersand))
				{
					std::puts("Found an dereference data token!");

					if (myAlpha(operands[s][ampersand + 1z]))
					{
						parser.replace(operands[s], "&", "");
				
						auto index = asemu::registerMap[operands[s]];
				
						machineCode.emplace_back(asemu::AddressingMode::REG_DEREFERENCE);
						machineCode.emplace_back(index);
					}
				
					else
					{
						parser.replace(operands[s], "&", "");
				
						machineCode.emplace_back(asemu::AddressingMode::MEM_DEREFERENCE);
				
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
					std::puts("Found an absolute data token!");
					
					if (myAlpha(operands[s][star + 1z]))
					{
						parser.replace(operands[s], "*", "");
				
						machineCode.emplace_back(asemu::AddressingMode::REG_ABSOLUTE);
						machineCode.emplace_back(asemu::registerMap[operands[s]]);
					}
				
					else
					{
						parser.replace(operands[s], "*", "");
				
						machineCode.emplace_back(asemu::AddressingMode::MEM_ABSOLUTE);
				
						if (operands[s][star + 2z] == '$')
						{
							machineCode.emplace_back(static_cast<std::uint8_t>(hexToInt(operands[s])));
						}
				
						if (operands[s][star + 2z] == '@')
						{
							machineCode.emplace_back(static_cast<std::uint8_t>(std::stoi(operands[s])));
						}
				
						else
						{
							std::puts("Could not find immediate data literal");
							std::exit(3);
						}
					}
				}
			}
		}

		else
		{
			std::puts("Mismatched operand count for specified instruction : ");
			std::exit(2);
		}

	}
}