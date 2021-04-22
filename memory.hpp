#pragma once

template<std::size_t S>
class Memory
{
private:
	std::array<DATASIZE, S> data{};

public:
	auto& read(DATASIZE loc) { return data[loc]; }
	auto write(DATASIZE loc, DATASIZE val) { data[loc] = val; }
};
