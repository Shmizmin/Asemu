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
Instruction RR##o \
{ { \
	{ aluPoke, Flags::ALU_REGISTER_##o }, \
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

Instruction RIMOV =
{ {
	{ regPokeI, Flags::REGISTER_POKE }
} };


Instruction MMCPY =
{ {
	{ memCopy, Flags::MEMORY_COPY }
} };



Instruction MRMOV
{ {
	{ regSaveM, Flags::REGISTER_SAVE }
} };

Instruction RMMOV
{ {
	{ regLoadM, Flags::REGISTER_LOAD }
} };

Instruction RRMOV
{ {
	{ regLoadR, Flags::REGISTER_COPY }
} };



Instruction UNJMP
{ {
	{ jmpUncon, Flags::JUMP_UNCONDITIONAL }
} };


Instruction ERJMP
{ {
	{ jmpEqZeR, Flags::JUMP_EQUAL_ZERO }
} };

Instruction NRJMP
{ {
	{ jmpNoEqR, Flags::JUMP_NOT_EQUAL_ZERO }
} };


Instruction EMJMP
{ {
	{ jmpEqZeM, Flags::JUMP_EQUAL_ZERO }
} };

Instruction NMJMP
{ {
	{ jmpNoEqM, Flags::JUMP_NOT_EQUAL_ZERO }
} };