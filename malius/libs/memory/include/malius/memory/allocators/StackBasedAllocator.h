//Fischer Thomas, Was Viktor, Winkler Roman
#pragma once

#include <malius/core/lang.hpp>
#include <malius/core/pointerUtil.h>
#include <malius/memory/alloc.h>
// #include "core.h"
// #include "core/PointerUtil.h"
// #include "memory/Malloc.h"

#include <iostream>
//#include <memory>
#include <cassert>
#include <bitset>
#include <cstring>


#define MA_USE_CANARIES 1
#define MA_CANARY_CODE 0xCDCDCDCD
#if MA_USE_CANARIES
#define MA_CANARY_SIZE 4
#else
#define MA_CANARY_SIZE 0
#endif

namespace ma
{
	class StackBasedAllocator
	{
		size_t m_size, m_alignment;
		char* m_memory;
		char* m_freePtr;
		uint32_t m_counter;

		static constexpr size_t SIZE_OF_ALLOCATION_OFFSET = sizeof(uint32_t);
		static constexpr size_t SIZE_OF_COUNTER_OFFSET = sizeof(uint32_t);

		constexpr char* begin(void) const { return pointer::AlignTop(m_memory, m_alignment); }
		constexpr char* end(void) const { return m_memory + m_size; }

	public:
		// es wird sichergestellt dass mindestens eine size gro�e allocation ohne zus�tzliches alignment gemacht werden kann
		explicit StackBasedAllocator(size_t size, size_t alignment)
			:
			m_size(size + alignment - 1u + SIZE_OF_ALLOCATION_OFFSET + SIZE_OF_COUNTER_OFFSET + MA_CANARY_SIZE * 2u),
			m_alignment(alignment),
			m_memory(static_cast<char*>(malloc(m_size)))
			//: m_memory(static_cast<char*>(_aligned_malloc(size, alignment))),
			////: m_memory(static_cast<char*>(std::aligned_alloc(alignment, size))),
			////: m_memory(static_cast<char*>(MA_ALIGNED_ALLOC(size, alignment))),
			//m_freePtr(m_memory),
			//m_counter(0)
		{
			//m_memory = static_cast<char*>(malloc(m_size));
			assert("malloc failed to allocate memory" && m_memory != nullptr);
			//assert(MA_IS_ALIGNED(m_memory, alignment));

			Reset();
			//assert(KPF_IS_ALIGNED(m_freePtr, alignment));
			//#if MA_DEBUG
			//			memset(m_memory, static_cast<int>(0xAFAFAFAF), m_size);
			//#endif //MA_DEBUG
		}

		~StackBasedAllocator()
		{
			//MA_ALIGNED_FREE(m_memory);
			free(m_memory);
		}

		void* Alloc(size_t size, size_t alignment)
		{
			// a unique address needs to be returned if size == 0
			// alternatively nullptr can be returned since this is implementation-defined
			if (size == 0)
			{
				return nullptr;
				size = 1;
				alignment = 1;
			}

			//calculate alignment offset
			char* resultAsCharPtr = pointer::AlignTop(m_freePtr + SIZE_OF_ALLOCATION_OFFSET + SIZE_OF_COUNTER_OFFSET + MA_CANARY_SIZE, alignment);

			//overflow check
			assert("allocation would overflow!" && resultAsCharPtr + size + MA_CANARY_SIZE <= end());

			ptrdiff_t const allocationOffset = m_freePtr - m_memory;

			//adjust current ptr position regarding alignment
			m_freePtr = resultAsCharPtr/* - SIZE_OF_ALLOCATION_OFFSET - SIZE_OF_COUNTER_OFFSET*/;

#if MA_USE_CANARIES
			m_freePtr -= MA_CANARY_SIZE;
			memset(m_freePtr, static_cast<int>(MA_CANARY_CODE), MA_CANARY_SIZE);
#endif

			//adjust current ptr position for counter used in deallocation
			m_freePtr -= SIZE_OF_COUNTER_OFFSET;

			//increment counter for stack like de/alloc
			memcpy(m_freePtr, &(++m_counter), sizeof(uint32_t));

			//adjust current ptr position for counter used in deallocation
			m_freePtr -= SIZE_OF_ALLOCATION_OFFSET;

			//write actual allocation startposition
			//explicit 4 bytes because we won't need more, not even on x64 architectures
			memcpy(m_freePtr, &allocationOffset, sizeof(uint32_t));

			//adjust left ptr for next allocation
			m_freePtr = resultAsCharPtr + size;

#if MA_USE_CANARIES
			memset(m_freePtr, static_cast<int>(MA_CANARY_CODE), MA_CANARY_SIZE);
			m_freePtr += MA_CANARY_SIZE;
#endif

			// implicit void cast
			return resultAsCharPtr;
		}

		void Free(void* MA_RESTRICT ptr)
		{
			//is ptr valid?
			assert("ptr is outside of aligned buffer; ptr <= begin!" && ptr > begin());
			assert("ptr is outside of aligned buffer; ptr >= end!" && ptr < m_freePtr);
			if (ptr == nullptr)
			{
				return;
			}

			char* userPtrAsCharPtr = static_cast<char*>(ptr);

#if MA_USE_CANARIES
			{	// check var ist nur in diesem scope und dann kann man ausserhalb auch eine var namens check haben
				uint32_t const check = MA_CANARY_CODE;
				bool const isLeftCanaryIntact = memcmp(m_freePtr - MA_CANARY_SIZE, &check, MA_CANARY_SIZE) == 0;
				bool const isRightCanaryIntact = memcmp(userPtrAsCharPtr - MA_CANARY_SIZE, &check, MA_CANARY_SIZE) == 0;
				assert("canaries are corrupted!" && isLeftCanaryIntact && isRightCanaryIntact);
			}
#endif //MA_USE_CANARIES

			//get counter var ptr position
			userPtrAsCharPtr -= SIZE_OF_COUNTER_OFFSET + MA_CANARY_SIZE;

			//is last element?
			//assert(ReadMemory<uint32_t>(user_ptr_as_char_ptr) == m_counter);
			assert("ptr is not the last element!" && memcmp(userPtrAsCharPtr, &m_counter, SIZE_OF_COUNTER_OFFSET) == 0);
			//if (*reinterpret_cast<uint32_t*>(user_ptr_as_char_ptr) != m_counter)
			//	return;

			//get allocation offset (starting from left) ptr position
			userPtrAsCharPtr -= SIZE_OF_ALLOCATION_OFFSET;

#if MA_DEBUG
			char* allocEnd = m_freePtr;
#endif //MA_DEBUG

			//adjust current leftPtr position
			m_freePtr = m_memory + ReadMemory<uint32_t>(userPtrAsCharPtr);
			--m_counter;

#if MA_DEBUG
			memset(userPtrAsCharPtr, 0, allocEnd - userPtrAsCharPtr);
#endif //MA_DEBUG
		}

		void Reset()
		{
			m_freePtr = begin();
			//m_freePtr = m_memory;
			m_counter = 0;
#if MA_DEBUG
			memset(m_memory, static_cast<int>(0xAFAFAFAF), m_size);
#endif
		}
	};

	inline void StackBasedAllocatorTest()
	{
		StackBasedAllocator* test = new StackBasedAllocator(32u * sizeof(int), 16u);

		int* ptr1 = static_cast<int*>(test->Alloc(sizeof(int), 4u));
		//*ptr1 = 0b11111111111111111111111111111111;
		*ptr1 = 0xDEADBEEF;
		int* ptr2 = static_cast<int*>(test->Alloc(sizeof(int), 8u));
		//*ptr2 = 0b01010101010101010101010101010101;
		*ptr2 = 0x1C0FFEE;
		int* ptr3 = static_cast<int*>(test->Alloc(sizeof(int), 2u));
		//*ptr3 = 0b01100110011001100110011001100110;
		*ptr3 = 0xABADCAFE;

		//std::cout << "&ptr1 = " << size_t(ptr1) << " set bits: " << std::bitset<sizeof(int)>(*ptr1) << std::endl;
		//std::cout << "&ptr2 = " << size_t(ptr2) << " set bits: " << std::bitset<sizeof(int)>(*ptr2) << std::endl;
		//std::cout << "&ptr3 = " << size_t(ptr3) << " set bits: " << std::bitset<sizeof(int)>(*ptr3) << std::endl;

		std::cout << "&ptr1 = " << size_t(ptr1) << " set bits: " << std::hex << static_cast<int>(*ptr1) << std::endl;
		std::cout << "&ptr2 = " << size_t(ptr2) << " set bits: " << std::hex << static_cast<int>(*ptr2) << std::endl;
		std::cout << "&ptr3 = " << size_t(ptr3) << " set bits: " << std::hex << static_cast<int>(*ptr3) << std::endl;

		std::cout << "free all" << std::endl;
		test->Free(ptr3);
		test->Free(ptr2);
		test->Free(ptr1);

		std::cout << "alloc 2" << std::endl;

		ptr1 = static_cast<int*>(test->Alloc(sizeof(int), 1));
		ptr2 = static_cast<int*>(test->Alloc(sizeof(int), 1));

		std::cout << "&ptr1 = " << uintptr_t(ptr1) << " value: " << std::hex << static_cast<int>(*ptr1) << std::endl;
		std::cout << "&ptr2 = " << uintptr_t(ptr2) << " value: " << std::hex << static_cast<int>(*ptr2) << std::endl;

		//std::cout << "&ptr1 = " << size_t(ptr1) << std::endl;
		//std::cout << "&ptr2 = " << size_t(ptr2) << std::endl;

		*ptr1 = 0;
		*ptr2 = 0;

		std::cout << "ptr1 = " << *ptr1 << std::endl;
		std::cout << "ptr2 = " << *ptr2 << std::endl;

		*ptr1 = 0xCAFEFEED;
		*ptr2 = 0xCAFEBABE;

		std::cout << "ptr1 = " << *ptr1 << std::endl;
		std::cout << "ptr2 = " << *ptr2 << std::endl;

		test->Free(ptr2);
		//test->Free(ptr1);

		ptr3 = static_cast<int*>(test->Alloc(sizeof(int), 1u));
		test->Free(ptr3);
		test->Free(ptr1);

		//memset(ptr1, 0x00, 4);
		// should match exactly the size of the buffer (if alignment is 1u)
		ptr1 = static_cast<int*>(test->Alloc(32u * sizeof(int), 16u));
		memset(ptr1, 0, 32u * sizeof(int));

		test->Free(ptr1);

		//*** KILLTESTS
		ptr1 = static_cast<int*>(test->Alloc(32u * sizeof(int) + 1u, 16u));
		memset(ptr1, 1, 32u * sizeof(int) + 1u);

		test->Free(ptr1);

		// should fail because of 8 bytes overhead + 4 bytes canaries per alloc
		//ptr1 = static_cast<int*>(test->Alloc(34u * sizeof(int), 16u));
		//test->Free(ptr1);

		//should fail because the canaries get overwritten
		//ptr1 = static_cast<int*>(test->Alloc(sizeof(int), 4));
		//*(reinterpret_cast<double*>(ptr1)) = 0xDEADBEEFDEAD;
		//test->Free(ptr1);
		//***

		delete test;

		std::cout << "finished...\n";
		std::cin.ignore();
	}
}
