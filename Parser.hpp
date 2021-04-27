#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace asemu
{
	class Parser
	{
	public:
		std::vector<std::string>&& split(const std::string& string, char delimiter) noexcept;
		std::vector<std::string>&& parse(const char* filepath) noexcept;
		void replace(std::string& string, const std::string& search, const std::string& replace) noexcept;
	};
}