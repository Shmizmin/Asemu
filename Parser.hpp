#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace asemu
{
	class Parser
	{
	public:
		explicit Parser(const char* filepath) noexcept
		{
			parsedData = this->parse(filepath);
		}

		~Parser() = default;

		Parser(const Parser&) = delete;
		Parser& operator=(const Parser&) = delete;

		Parser(Parser&&) = default;
		Parser& operator=(Parser&&) = default;

		std::vector<std::string> parsedData{};

		std::vector<std::string> split(const std::string& string, char delimiter) noexcept;
		std::vector<std::string> parse(const char* filepath) noexcept;
		void replace(std::string& string, const std::string& search, const std::string& replace) noexcept;
	};
}