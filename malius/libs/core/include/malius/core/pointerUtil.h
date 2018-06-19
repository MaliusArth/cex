#pragma once

#include <malius/core/math/pow2.h>

#include <cassert>

namespace ma
{
	namespace pointer
	{
		template <class T>
		constexpr T* AlignBottom(T* ptr, size_t alignmentMustBePowerOfTwo)
		{
			union
			{
				T* as_T_ptr;
				uintptr_t as_uintptr_t;
			};

			assert(isPowerOfTwo(alignmentMustBePowerOfTwo));
			const size_t mask = ~(alignmentMustBePowerOfTwo - 1u);
			as_T_ptr = ptr;
			as_uintptr_t &= mask;
			return as_T_ptr;
		}

		template <class T>
		constexpr T* AlignTop(T* ptr, size_t alignmentMustBePowerOfTwo)
		{
			union
			{
				T* as_T_ptr;
				uintptr_t as_uintptr_t;
			};

			assert(isPowerOfTwo(alignmentMustBePowerOfTwo));
			const size_t mask = ~(alignmentMustBePowerOfTwo - 1u);
			as_T_ptr = ptr;
			as_uintptr_t += alignmentMustBePowerOfTwo - 1u;
			as_uintptr_t &= mask;
			return as_T_ptr;
		}
	}

	//#if MA_CONSTEXPR_SUPPORTED
	//	// Constexpr function never produces a constant expression
	//	constexpr bool isAligned(const void *MA_RESTRICT ptr, size_t alignment)
	//	{
	//		return (uintptr_t(ptr) % alignment == 0);
	//	}
	//#define MA_IS_ALIGNED(ptr, alignment) isAligned(ptr, alignment)
	//#else
#define MA_IS_ALIGNED(ptr, alignment) (uintptr_t((const void *)(ptr)) % (alignment) == 0)
	//#endif
}
