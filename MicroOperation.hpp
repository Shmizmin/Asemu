#pragma once

#include "OpFlags.hpp"
#include "Addressing.hpp"
#include "Literals.hpp"
#include "Memory.hpp"
#include <functional>

namespace asemu
{
	class MicroOperation
	{
	public:
		AddressingMode addressingMode;

		std::function<void(µOpArgs)> functor;
	};
}