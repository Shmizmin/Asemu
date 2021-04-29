#pragma once

#include <cstddef>
#include <vector>
#include <string>

#include "Parser.hpp"

namespace asemu
{
	class Assembler
	{
	public:
		Parser parser;
		std::vector<std::uint8_t> machineCode;

		Assembler(const char* filepath) noexcept
			: parser(filepath)
		{
			this->assemble(parser.parsedData);
		}

		void assemble(std::vector<std::string>& lines) noexcept;
	};
}