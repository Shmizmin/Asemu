#pragma once

#include "Assembler.hpp"
#include "InstructionDecoder.hpp"
#include "Processor.hpp"

namespace asemu
{
	class Executor
	{
	public:
		Assembler assembler;
		Processor processor;

		Executor() = delete;
		~Executor() = default;

		Executor(const Executor&) = delete;
		Executor& operator=(const Executor&) = delete;

		Executor(Executor&&) = default;
		Executor& operator=(Executor&&) = default;

		explicit Executor(const char* filepath) noexcept
			: assembler(filepath), processor(assembler.machineCode)
		{
	
		}
	};
}