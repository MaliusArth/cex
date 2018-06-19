#pragma once

#include "malius/templates/require.h"

#include <cstdlib>
#include <type_traits>

namespace ma
{
	//inline bool isPowerOfTwo(size_t x)
	//{
	//	return ((x != 0) && ((x & (~x + 1)) == x));
	//}

	//template<typename T, MA_REQUIRES(std::is_integral<T>::value)>
	//template<typename T, MA_REQUIRES_NAMED(std::is_integral<T>::value, INTEGRAL_REQUIREMENT)>
	template<typename T, MA_REQUIRES(std::is_integral<T>::value)>
	//template<typename T, typename = std::enable_if_t<std::is_integral<T>::value, bool>>
	constexpr bool isPowerOfTwo(T x)
	{
		return ((x != 0) && ((x & (~x + 1)) == x));
	}

	// not continuously evaluated (resharper/intellisense)
	template<typename T>
	constexpr bool isPowerOfTwo_asserted(T x)
	{
		static_assert(std::is_integral<T>::value, "Template type is not integral!");
		return ((x != 0) && ((x & (~x + 1)) == x));
	}

	inline void MathTest(void)
	{
		const ::size_t size = 0;
		const int integer = 0;
		const float floating_point = 0;

		// should compile
		bool test1 = ma::isPowerOfTwo(size);
		bool test2 = ma::isPowerOfTwo(integer);
		// should not compile:
		//bool test3 = ma::isPowerOfTwo(floating_point);
		//bool test4 = ma::isPowerOfTwo_asserted(floating_point);
	}
}
