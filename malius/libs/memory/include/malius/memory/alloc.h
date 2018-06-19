#pragma once

#include <malius/core/pointerUtil.h>

#include <malloc.h>

namespace ma
{
#define MA_STD_ALIGN 0

	// TODO: understand this
	/// Reference: https://stackoverflow.com/questions/32133203/what-can-i-use-instead-of-stdaligned-alloc-in-ms-visual-studio-2013
	inline void* alignedAlloc(size_t size, size_t alignment)
	{
		if (alignment < alignof(void*))
		{
			alignment = alignof(void*);
		}
		size_t const space = size + alignment - 1;
		void* allocatedMemory = malloc(space + sizeof(void*));
		void* alignedMemory = static_cast<void*>(static_cast<char*>(allocatedMemory) + sizeof(void*));
		////////////// #1 ///////////////
#if MA_STD_ALIGN
		std::align(alignment, size, alignedMemory, MA_OUT space);
#else
		alignedMemory = pointer::AlignTop(alignedMemory, alignment);
#endif
		////////////// #2 ///////////////
		*(static_cast<void**>(alignedMemory) - 1) = allocatedMemory;
		////////////// #3 ///////////////
		return alignedMemory;
	}

	inline void alignedFree(void* p) noexcept
	{
		//::operator delete(*(static_cast<void**>(p) - 1));
		free(*(static_cast<void**>(p) - 1));
	}

#define MA_ALIGNED_ALLOC_MVC 0
#define MA_ALIGNED_ALLOC_CPP17 0

#if MA_ALIGNED_ALLOC_MVC
#define MA_ALIGNED_ALLOC(size, alignment) _aligned_malloc(size, alignment)
#define MA_ALIGNED_FREE(ptr) _aligned_free(ptr)
#elif MA_ALIGNED_ALLOC_CPP17
	//#ifndef _MSC_VER
	//#include <cstdlib>
	//#endif
#define MA_ALIGNED_ALLOC(size, alignment) std::aligned_alloc(alignment, size)
#define MA_ALIGNED_FREE(ptr) std::free(ptr)
#else
#define MA_ALIGNED_ALLOC(size, alignment) alignedAlloc(size, alignment)
#define MA_ALIGNED_FREE(ptr) alignedFree(ptr)
#endif
}
