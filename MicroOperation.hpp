#pragma once

#include "OpFlags.hpp"
#include <functional>

namespace asemu
{
	class MicroOperation
	{
	private:
		OpFlags opFlag;

	public:
		std::function<void(void)> functor;
	};
}