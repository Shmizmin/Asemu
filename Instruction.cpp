#include "Instruction.hpp"
#include "Literals.hpp"

std::unordered_map<std::string, std::tuple<std::uint8_t, std::uint8_t>> asemu::instructionMap =
{
	{ "nop", {  0uc, 0uc } },
	{ "mov", {  1uc, 2uc } },
	{ "add", {  2uc, 2uc } },
	{ "sub", {  3uc, 2uc } },
	{ "mul", {  4uc, 2uc } },
	{ "div", {  5uc, 2uc } },
	{ "asl", {  6uc, 2uc } },
	{ "asr", {  7uc, 2uc } },
	{ "jmp", {  8uc, 1uc } },
	{ "jez", {  9uc, 2uc } },
	{ "jnz", { 10uc, 2uc } },
	{ "jgz", { 11uc, 2uc } },
	{ "jlz", { 12uc, 2uc } },
	{ "cal", { 13uc, 1uc } },
	{ "ret", { 14uc, 0uc } },
	{ "psh", { 15uc, 1uc } },
	{ "pop", { 16uc, 1uc } }
};

std::unordered_map<std::string, std::uint8_t> asemu::registerMap =
{
	{ "sax", 1uc },
	{ "sbx", 2uc },
	{ "scx", 3uc },
	{ "sdx", 4uc },
	{ "sbp", 5uc },
	{ "ssp", 6uc },
	{ "sip", 7uc }
};

using Mode = asemu::AddressingMode;

std::unordered_map<std::uint8_t, std::vector<asemu::MicroOperation>> asemu::µOpMap =
{

};
//{
//	{  0uc, { Mode::NULL_ADDRESSING, [&](µOpArgs) {  } } },
//	{  1uc, {  } },
//	{  2uc, {  } },
//	{  3uc, {  } },
//	{  4uc, {  } },
//	{  5uc, {  } },
//	{  6uc, {  } },
//	{  7uc, {  } },
//	{  8uc, {  } },
//	{  9uc, {  } },
//	{ 10uc, {  } },
//	{ 11uc, {  } },
//	{ 12uc, {  } },
//	{ 13uc, {  } },
//	{ 14uc, {  } },
//	{ 15uc, {  } },
//	{ 16uc, {  } }
//};