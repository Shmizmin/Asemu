#pragma once

MicroOp memPoke = { [&](args) { memory.write(op1, op2); } };
MicroOp memCopy = { [&](args) { memory.write(op2, memory.read(op1)); } };

MicroOp aluPoke = { [&](args) { processor.core.alu.poke(flags, op1, op2); } };
MicroOp aluBegin = { [&](args) { processor.core.alu.execute(processor.core.status); } };
MicroOp aluBind = { [&](args) {} };

MicroOp regPokeI = { [&](args) { registers[op1].write(0ui16, op2); } };
MicroOp regLoadM = { [&](args) { registers[op1].write(0ui16, memory.read(op2)); } };
MicroOp regSaveM = { [&](args) { memory.write(op2, registers[op1].read(0ui16)); } };
MicroOp regLoadR = { [&](args) { registers[op1].write(0ui16, registers[op2].read(0ui16)); } };

MicroOp jmpUncon = { [&](args) { programCounter = op1; } };

MicroOp jmpEqZeR = { [&](args) { if (registers[op2].read(0ui16) == 0ui16) programCounter = op1; } };
MicroOp jmpNoEqR = { [&](args) { if (registers[op2].read(0ui16) != 0ui16) programCounter = op1; } };

MicroOp jmpEqZeM = { [&](args) { if (memory.read(op2) == 0ui16) programCounter = op1; } };
MicroOp jmpNoEqM = { [&](args) { if (memory.read(op2) != 0ui16) programCounter = op1; } };