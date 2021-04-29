#include "Parser.hpp"
#include "Instruction.hpp"

std::vector<std::string> asemu::Parser::split(const std::string& string, char delimiter) noexcept
{
	std::vector<std::string> strings;
	std::size_t start;
	std::size_t end = 0;

	while ((start = string.find_first_not_of(delimiter, end)) != std::string::npos)
	{
		end = string.find(delimiter, start);
		strings.push_back(string.substr(start, end - start));
	}

	return strings;
}

void asemu::Parser::replace(std::string& string, const std::string& search, const std::string& replace) noexcept
{
	std::size_t pos = 0;
	while ((pos = string.find(search, pos)) != std::string::npos)
	{
		string.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

std::vector<std::string> asemu::Parser::parse(const char* filepath) noexcept
{
	std::ifstream t(filepath);
	std::string code;

	t.seekg(0, std::ios::end);
	code.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	code.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return this->split(code, '\n');
}