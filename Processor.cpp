#include "Processor.hpp"

void asemu::Processor::execute(std::vector<std::vector<std::uint8_t>> bytes) noexcept
{
	auto lineCount = 0z;
	for (auto i = 0z; i <= bytes.size(); )
	{
		std::cin.get();

		for (auto j = 0z; j < bytes[lineCount].size(); ++j)
		{
			addressBus = i + j;
			memory.read(buses);

			



			
			dataBus = i;
			addressBus = asemu::registerMap["sip"];

			registers[addressBus].write(buses);
		}
	}
}