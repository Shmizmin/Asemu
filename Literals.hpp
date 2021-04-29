#pragma once

#include <cstdint>
#include <cstdlib>

#pragma warning(push)
#pragma warning(disable: 4455)
inline constexpr std::size_t operator"" z(unsigned long long n) noexcept
{
	return static_cast<std::size_t>(n);
}

inline constexpr std::uint8_t operator"" uc(unsigned long long n) noexcept
{
	return static_cast<std::uint8_t>(n);
}

inline constexpr std::uint16_t operator"" us(unsigned long long n) noexcept
{
	return static_cast<std::uint16_t>(n);
}

inline constexpr std::uint32_t operator"" ui(unsigned long long n) noexcept
{
	return static_cast<std::uint32_t>(n);
}

inline constexpr std::uint64_t operator"" ul(unsigned long long n) noexcept
{
	return static_cast<std::uint64_t>(n);
}
#pragma warning(pop)

#define busArgs std::uint8_t& addressBus, std::uint8_t& dataBus
#define buses addressBus, dataBus

#define µOpArgs std::uint8_t& addressBus, std::uint8_t& dataBus, Memory& memory, std::array<Register, 7>& registers