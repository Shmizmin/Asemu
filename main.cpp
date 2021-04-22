#include <cstdint>
#include <array>
#include <iostream>
#include <vector>
#include <deque>
#include <functional>
#include <algorithm>

#define args Flags flags, DATASIZE op1, DATASIZE op2

#pragma warning(disable : 26812)

using DATASIZE = std::uint16_t;
constexpr auto MAX16 = std::numeric_limits<DATASIZE>{}.max();

constexpr auto MEMSIZE = MAX16;

#pragma warning(suppress : 4455)
constexpr std::size_t operator "" z(unsigned long long n)
{
	return n;
}


enum Flags : DATASIZE
{
	STATUS_Overflow = 1ui16,
	STATUS_Zero = 2ui16,
	STATUS_Carry = 4ui16,
	STATUS_Truncated = 8ui16,
	
	ALU_DEREF_ADD,
	ALU_DEREF_SUB,
	ALU_DEREF_MUL,
	ALU_DEREF_DIV,
	ALU_DEREF_SHL,
	ALU_DEREF_SHR,

	ALU_NORM_ADD,
	ALU_NORM_SUB,
	ALU_NORM_MUL,
	ALU_NORM_DIV,
	ALU_NORM_SHL,
	ALU_NORM_SHR,

	ALU_POKE,
	ALU_BEGIN,
	ALU_RETURN,

	MEMORY_PEEK,
	MEMORY_POKE
};

struct MicroOp
{
	std::function<DATASIZE(args)> call;

	auto operator()(args) noexcept
	{
		call(flags, op1, op2);
	}
};

struct CallingInformation
{
	MicroOp op;
	Flags flags;
};

struct Instruction
{
	std::vector<CallingInformation> ops;

	auto operator()(const DATASIZE& operand1, const DATASIZE& operand2 = 0ui16) noexcept
	{
		for (auto& m : ops)
		{
			m.op(m.flags, operand1, operand2);
		}
	}
};



class Pipeline
{
private:
	std::deque<Instruction> instructions;

public:
	auto decompose(std::size_t index)
	{
		if (index < instructions.size())
			return instructions[index].ops;
	}

	auto fetch()
	{

	}

	auto predict()
	{

	}


	auto peek()
	{

	}

	auto poke()
	{

	}

};

template<std::size_t S>
class Memory
{
private:
	std::array<DATASIZE, S> data{};

public:
	auto& read(DATASIZE loc) { return data[loc]; }
	auto write(DATASIZE loc, DATASIZE val) { data[loc] = val; }
};


using Cache = Memory<8>;
using Register = Memory<1>;

Memory<MEMSIZE> memory;

class ALU
{
private:
	Flags flags;
	DATASIZE num1, num2;

public:
	auto peek()
	{
		return std::tie(num1, num2);
	}

	auto poke(Flags f, DATASIZE n1, DATASIZE n2)
	{
		flags = f;
		num1 = n1;
		num2 = n2;
	}

	auto execute(DATASIZE& inFlags)
	{
		switch (flags)
		{
		case Flags::ALU_DEREF_ADD:
			if ((size_t)memory.read(num1) + (size_t)memory.read(num2) > MAX16)
				inFlags |= Flags::STATUS_Overflow;

			memory.write(num1, memory.read(num1) + memory.read(num2));

			break;

		case Flags::ALU_DEREF_SUB:
			memory.write(num1, memory.read(num1) - memory.read(num2));
			break;

		case Flags::ALU_DEREF_MUL:
			if ((size_t)memory.read(num1) * (size_t)memory.read(num2) > MAX16)
				inFlags |= Flags::STATUS_Overflow;

			memory.write(num1, memory.read(num1) * memory.read(num2));
			break;

		case Flags::ALU_DEREF_DIV:
			memory.write(num1, memory.read(num1) / memory.read(num2));

			float whole, fractional;
			fractional = std::modf(float(memory.read(num1)), &whole);

			if (fractional != 0.0f)
				inFlags |= Flags::STATUS_Truncated;

			break;

		case Flags::ALU_DEREF_SHL:
			memory.write(num1, memory.read(num1) << memory.read(num2));
			inFlags |= Flags::STATUS_Carry;
			break;

		case Flags::ALU_DEREF_SHR:
			memory.write(num1, memory.read(num1) >> memory.read(num2));
			inFlags |= Flags::STATUS_Carry;
			break;




		case Flags::ALU_NORM_ADD:
			if ((size_t)num1 + (size_t)num2 > MAX16)
				inFlags |= Flags::STATUS_Overflow;

			num1 += num2;
			break;

		case Flags::ALU_NORM_SUB:
			num1 -= num2;
			break;

		case Flags::ALU_NORM_MUL:
			if ((size_t)num1 * (size_t)num2 > MAX16)
				inFlags |= Flags::STATUS_Overflow;

			num1 *= num2;
			break;

		case Flags::ALU_NORM_DIV:
			num1 /= num2;

			float whole2, fractional2;
			fractional2 = std::modf(num1, &whole2);

			if (fractional2 != 0.0f)
				inFlags |= Flags::STATUS_Truncated;

			break;

		case Flags::ALU_NORM_SHL:
			num1 <<= num2;
			inFlags |= Flags::STATUS_Carry;

			break;

		case Flags::ALU_NORM_SHR:
			num1 >>= num2;
			inFlags |= Flags::STATUS_Carry;

			break;
		}
	}

};

struct Core
{
	ALU alu;
	Pipeline pipeline;

	DATASIZE status;

	Cache cache;

	Register r1;
	Register r2;
};

struct CPU
{
	Core core;
} processor;


MicroOp memPeek = { [&](args) -> DATASIZE { return memory.read(op1); } };
MicroOp memPoke = { [&](args) -> DATASIZE { memory.write(op1, op2); return 0ui16; } };

MicroOp aluPoke = { [&](args) -> DATASIZE { processor.core.alu.poke(flags, op1, op2); return 0ui16; } };
MicroOp aluBegin = { [&](args) -> DATASIZE { processor.core.alu.execute(processor.core.status); return 0ui16; } };
MicroOp aluReturn = { [&](args) -> DATASIZE { return std::get<0>(processor.core.alu.peek());  } };

#define INSTRUCTION_ALU(o) Instruction MM##o \
{ { \
	{ aluPoke, Flags::ALU_DEREF_##o }, \
	{ aluBegin, Flags::ALU_BEGIN }, \
	{ aluReturn, Flags::ALU_RETURN } \
} }; \
Instruction RR##o \
{ { \
	{ aluPoke, Flags::ALU_NORM_##o }, \
	{ aluBegin, Flags::ALU_BEGIN }, \
	{ aluReturn, Flags::ALU_RETURN } \
} }; \

INSTRUCTION_ALU(ADD);
INSTRUCTION_ALU(SUB);
INSTRUCTION_ALU(MUL);
INSTRUCTION_ALU(DIV);
INSTRUCTION_ALU(SHL);
INSTRUCTION_ALU(SHR);

Instruction RPMOV =
{ {
	{ memPoke, Flags::MEMORY_POKE },
} };

#define MPMIO(x) memory.read(x)

int main(void)
{
	//memPoke(Flags::MEMORY_POKE, 1ui16, 4ui16);
	//memPoke(Flags::MEMORY_POKE, 3ui16, 9ui16);

	//(void)aluPoke.call(Flags::ALU_DEREF_ADD, 1ui16, 2ui16);
	//(void)aluBegin.call(Flags::ALU_BEGIN, NULL, NULL);

	//addrr(11ui16, 6ui16);
	//auto [x, y] = processor.core.alu.peek();

	//memPoke(Flags::MEMORY_POKE, )

	//std::cout << x << std::endl;

	RPMOV(1ui16, 5ui16);
	RPMOV(2ui16, 10ui16);

	MMADD(1ui16, 2ui16);

	std::cout << MPMIO(1ui16) << std::endl;
}