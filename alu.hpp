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
		auto& ref2 = registers[num2];

		auto& val = ref.read(0ui16);
		auto& val2 = ref2.read(0ui16);

		switch (flags)
		{
		case Flags::ALU_DEREF_ADD:
			if ((size_t)memory.read(num1) + (size_t)memory.read(num2) >= MAX16)
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
			if ((size_t)memory.read(num1) * (size_t)memory.read(num2) >= MAX16)
				inFlags |= Flags::STATUS_Overflow;

			if (memory.read(num1) == 0ui16 or memory.read(num2) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			memory.write(num1, memory.read(num1) * memory.read(num2));
			break;

		case Flags::ALU_DEREF_DIV:
			if ((memory.read(num1) / memory.read(num2)) == 0ui16)
				inFlags |= Flags::STATUS_Zero;
			
			memory.write(num1, memory.read(num1) / memory.read(num2));

			float whole, fractional;
			fractional = std::modf(float(memory.read(num1)), &whole);

			if (fractional != 0.0f)
				inFlags |= Flags::STATUS_Truncated;

			break;

		case Flags::ALU_DEREF_SHL:
			if ((memory.read(num1) << memory.read(num2)) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)memory.read(num1) << (size_t)memory.read(num2)) >= (size_t)MAX16)
				inFlags |= Flags::STATUS_Overflow;

			memory.write(num1, memory.read(num1) << memory.read(num2));
			
			inFlags |= Flags::STATUS_Carry;
			
			break;

		case Flags::ALU_DEREF_SHR:
			if ((memory.read(num1) >> memory.read(num2)) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)memory.read(num1) >> (size_t)memory.read(num2)) >= (size_t)MAX16)
				inFlags |= Flags::STATUS_Overflow;

			memory.write(num1, memory.read(num1) >> memory.read(num2));
			
			inFlags |= Flags::STATUS_Carry;
			
			break;




		case Flags::ALU_NORM_ADD:
			if ((val + memory.read(num2) == 0))
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val + (size_t)memory.read(num2) >= (size_t)MAX16))
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
			if (((size_t)val * (size_t)memory.read(num2) >= (size_t)MAX16))
				inFlags |= Flags::STATUS_Overflow;

			if (val == 0ui16 or memory.read(num2) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			ref.write(0ui16, (val * memory.read(num2)));
			break;

		case Flags::ALU_NORM_DIV:
			if ((val / memory.read(num2)) == 0ui16)
				inFlags |= Flags::STATUS_Zero;
			
			ref.write(0ui16, (val / memory.read(num2)));

			float whole2, fractional2;
			fractional2 = std::modf(val, &whole2);

			if (fractional2 != 0.0f)
				inFlags |= Flags::STATUS_Truncated;

			break;

		case Flags::ALU_NORM_SHL:
			if ((val << memory.read(num2)) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val << (size_t)memory.read(num2)) >= (size_t)MAX16)
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val << memory.read(num2)));

			inFlags |= Flags::STATUS_Carry;

			break;

		case Flags::ALU_NORM_SHR:
			if ((val >> memory.read(num2)) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val >> (size_t)memory.read(num2)) >= (size_t)MAX16)
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val >> memory.read(num2)));

			inFlags |= Flags::STATUS_Carry;

			break;




		case Flags::ALU_REGISTER_ADD:
			if ((val + val2 == 0))
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val + (size_t)val2 >= (size_t)MAX16))
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val + val2));

			break;

		case Flags::ALU_REGISTER_SUB:
			if (val == val2)
				inFlags |= Flags::STATUS_Zero;

			if (val < val2)
				inFlags |= Flags::STATUS_Negative;

			ref.write(0ui16, (val - val2));

			break;

		case Flags::ALU_REGISTER_MUL:
			if (((size_t)val * (size_t)val2 >= (size_t)MAX16))
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val * val2));

			break;

		case Flags::ALU_REGISTER_DIV:
			if ((val / val2) == 0ui16)
				inFlags |= Flags::STATUS_Zero;
			
			ref.write(0ui16, (val / val2));

			float whole3, fractional3;
			fractional3 = std::modf(val, &whole3);

			if (fractional3 != 0.0f)
				inFlags |= Flags::STATUS_Truncated;

			break;

		case Flags::ALU_REGISTER_SHL:
			if ((val << val2) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val << (size_t)val2) >= (size_t)MAX16)
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val << val2));

			inFlags |= Flags::STATUS_Carry;

			break;

		case Flags::ALU_REGISTER_SHR:
			if ((val >> val2) == 0ui16)
				inFlags |= Flags::STATUS_Zero;

			if (((size_t)val >> (size_t)val2) >= (size_t)MAX16)
				inFlags |= Flags::STATUS_Overflow;

			ref.write(0ui16, (val >> val2));

			inFlags |= Flags::STATUS_Carry;


			break;

		}
	}

};