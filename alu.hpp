#pragma once

class ALU
{
private:
	Flags flags;
	DATASIZE num1, num2;

public:
	auto poke(Flags f, DATASIZE n1, DATASIZE n2)
	{
		flags = f;
		num1 = n1;
		num2 = n2;
	}

	auto execute(DATASIZE& inFlags)
	{
		auto& ref = registers[num1];
		auto& val = ref.read(0ui16);

		switch (flags)
		{
		case Flags::ALU_DEREF_ADD:
			if ((size_t)memory.read(num1) + (size_t)memory.read(num2) > MAX16)
				inFlags |= Flags::STATUS_Overflow;

			memory.write(num1, memory.read(num1) + memory.read(num2));

			break;

		case Flags::ALU_DEREF_SUB:
			memory.write(num1, memory.read(num1) - memory.read(num2));

			if (memory.read(num1) == memory.read(num2))
				inFlags |= Flags::STATUS_Zero;

			if (memory.read(num1) < memory.read(num2))
				inFlags |= Flags::STATUS_Negative;

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
			if ((val + memory.read(num2) == 0))
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val + (size_t)memory.read(num2) > (size_t)MAX16))
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val + memory.read(num2)));

			break;

		case Flags::ALU_NORM_SUB:
			if (val == memory.read(num2))
				inFlags |= Flags::STATUS_Zero;

			if (val < memory.read(num2))
				inFlags |= Flags::STATUS_Negative;

			ref.write(0ui16, (val - memory.read(num2)));

			break;

		case Flags::ALU_NORM_MUL:
			if (((size_t)val * (size_t)memory.read(num2) > (size_t)MAX16))
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val * memory.read(num2)));
			break;

		case Flags::ALU_NORM_DIV:
			ref.write(0ui16, (val / memory.read(num2)));

			float whole2, fractional2;
			fractional2 = std::modf(val, &whole2);

			if (fractional2 != 0.0f)
				inFlags |= Flags::STATUS_Truncated;

			break;

		case Flags::ALU_NORM_SHL:
			ref.write(0ui16, (val << memory.read(num2)));

			inFlags |= Flags::STATUS_Carry;

			break;

		case Flags::ALU_NORM_SHR:
			ref.write(0ui16, (val >> memory.read(num2)));

			inFlags |= Flags::STATUS_Carry;

			break;
		}
	}

};