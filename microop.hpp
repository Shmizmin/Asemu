#pragma once

#include "helper.hpp"
#include <functional>

struct MicroOp
{
	std::function<void(args)> call;

	auto operator()(args) noexcept
	{
		call(flags, op1, op2);
	}
};