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
#pragma warning(pop)