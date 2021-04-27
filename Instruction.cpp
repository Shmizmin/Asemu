#include "Instruction.hpp"

using mode = asemu::AddressingMode;

std::unordered_map<std::string, std::pair<std::uint8_t, std::uint8_t>> asemu::instructionMap =
{
	{ "nop", {  0ui8, 0ui8 } },
	{ "mov", {  1ui8, 2ui8 } },
	{ "add", {  2ui8, 2ui8 } },
	{ "sub", {  3ui8, 2ui8 } },
	{ "mul", {  4ui8, 2ui8 } },
	{ "div", {  5ui8, 2ui8 } },
	{ "asl", {  6ui8, 2ui8 } },
	{ "asr", {  7ui8, 2ui8 } },
	{ "jmp", {  8ui8, 1ui8 } },
	{ "jez", {  9ui8, 2ui8 } },
	{ "jnz", { 10ui8, 2ui8 } },
	{ "jgz", { 11ui8, 2ui8 } },
	{ "jlz", { 12ui8, 2ui8 } },
	{ "cal", { 13ui8, 1ui8 } },
	{ "ret", { 14ui8, 0ui8 } }
};

std::unordered_map<std::string, std::uint8_t> asemu::registerMap =
{
	{ "sax", 0ui8 },
	{ "sbx", 1ui8 },
	{ "scx", 2ui8 },
	{ "sdx", 3ui8 },
	{ "sbp", 4ui8 },
	{ "ssp", 5ui8 },
	{ "sip", 6ui8 }
};