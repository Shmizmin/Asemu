#pragma once

struct Core
{
	ALU alu;
	Pipeline pipeline;

	DATASIZE status;

	Cache cache;

	Register r1;
	Register r2;
};