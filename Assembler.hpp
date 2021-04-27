#pragma once

#include <cstddef>
#include <vector>
#include <string>

#include "Parser.hpp"

namespace asemu
{
	class Assembler
	{
	private:
		Parser parser;

		std::vector<std::uint8_t> machineCode;

	public:
		auto assemble(std::vector<std::string>& lines) noexcept;
	};
}