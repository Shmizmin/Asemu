#pragma once

MicroOp memPoke = { [&](args) { memory.write(op1, op2); } };
MicroOp memCopy = { [&](args) { memory.write(op2, memory.read(op1)); } };

MicroOp aluPoke = { [&](args) { processor.core.alu.poke(flags, op1, op2); } };
MicroOp aluBegin = { [&](args) { processor.core.alu.execute(processor.core.status); } };
MicroOp aluBind = { [&](args) {} };

MicroOp regPoke = { [&](args) { registers[op1].write(0ui16, op2); } };
MicroOp regCopy = { [&](args) { memory.write(op2, registers[op1].read(0ui16)); } };