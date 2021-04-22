#pragma once

#define INSTRUCTION_ALU(o) Instruction MM##o \
{ { \
	{ aluPoke, Flags::ALU_DEREF_##o }, \
	{ aluBegin, Flags::ALU_BEGIN }, \
	{ aluBind, Flags::ALU_BIND } \
} }; \
Instruction RM##o \
{ { \
	{ aluPoke, Flags::ALU_NORM_##o }, \
	{ aluBegin, Flags::ALU_BEGIN }, \
	{ aluBind, Flags::ALU_BIND } \
} }; \

INSTRUCTION_ALU(ADD);
INSTRUCTION_ALU(SUB);
INSTRUCTION_ALU(MUL);
INSTRUCTION_ALU(DIV);
INSTRUCTION_ALU(SHL);
INSTRUCTION_ALU(SHR);

Instruction MIMOV =
{ {
	{ memPoke, Flags::MEMORY_POKE }
} };

Instruction MMCPY =
{ {
	{ memCopy, Flags::MEMORY_COPY }
} };

Instruction RIMOV =
{ {
	{ regPoke, Flags::REGISTER_POKE }
} };

Instruction RMCPY
{ {
	{ regCopy, Flags::REGISTER_COPY }
} };