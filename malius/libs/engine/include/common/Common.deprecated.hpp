/*license info*/

/// TODO: might not be supported by some compilers
#pragma once

// Reference: Flatbuffers: flatbuffers.h

#if __cplusplus <= 199711L && \
    (!defined(_MSC_VER) || _MSC_VER < 1600) && \
    (!defined(__GNUC__) || \
      (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ < 40400))
#error A C++11 compatible compiler with support for the auto typing is required for MasterEngine.
#error __cplusplus _MSC_VER __GNUC__  __GNUC_MINOR__  __GNUC_PATCHLEVEL__
#endif

#if !defined(__clang__) && \
    defined(__GNUC__) && \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ < 40600)
// Backwards compatability for g++ 4.4, and 4.5 which don't have the nullptr and constexpr
// keywords. Note the __clang__ check is needed, because clang presents itself as an older GNUC
// compiler.
#ifndef nullptr_t
const class nullptr_t
{
public:
    template<class T> inline operator T*() const { return 0; }
private:
    void operator&() const;
} nullptr = {};
#endif

#ifndef constexpr
#define constexpr const
#endif

#endif

#if (!defined(_MSC_VER) || _MSC_VER >= 1900) && \
    (!defined(__GNUC__) || (__GNUC__ * 100 + __GNUC_MINOR__ >= 406))
#define  MA_CONSTEXPR constexpr
#else
#define  MA_CONSTEXPR
#endif



// Reference: https://blog.molecular-matters.com/2011/07/12/a-plethora-of-macros/

#if defined(_MSC_VER) && _MSC_VER >= 1900
/// allows member functions to be made abstract. uses nonstandard C++ extensions provided by MSVC
#define  MA_ABSTRACT abstract
#else 
#define  MA_ABSTRACT
#endif
/// marks member functions as being an override of a base class virtual function. uses nonstandard C++ extensions provided by MSVC
/// C++11 also has override available since MSVC 12 (VS2013)
#define  MA_OVERRIDE override

#if (!defined(_MSC_VER) || _MSC_VER > 1600) && \
    (!defined(__GNUC__) || (__GNUC__ * 100 + __GNUC_MINOR__ >= 407))
#define  MA_FINAL final
#elif (defined(_MSC_VER) && _MSC_VER <= 1600)
//#if defined(_MSC_EXTENSIONS) && _MSC_EXTENSIONS == TODO
/// allows classes and member functions to be made sealed. uses nonstandard C++ extensions provided by MSVC
#define  MA_FINAL sealed
#else
#define  MA_FINAL
#endif


/// allows to emit pragmas from within macros
#define  MA_PRAGMA(pragma) __pragma(pragma)

/// support for C99 restrict keyword
#define  MA_RESTRICT __restrict

/// tells the compiler that the return value (RV) of a function is an object that will not be aliased with any other pointers
#define  MA_RESTRICT_RV __declspec(restrict)

/// tells the compiler that a function call does not modify or reference visible global state and only modifies the memory pointed to directly by pointer parameters
#define  MA_NO_ALIAS __declspec(noalias)

/// forces a function to be inlined
#ifdef _MSC_VER
#define  MA_INLINE __forceinline
#elif __GNUC__
#define  MA_INLINE __attribute__((always_inline))
#else
#define  MA_INLINE inline
#endif

/// tells the compiler to never inline a particular function
#define  MA_NO_INLINE __declspec(noinline)

/// passes optimization hints to the compiler
#define  MA_HINT(hint) __assume(hint)

/// used in switch-statements whose default-case can never be reached, resulting in more optimal code
#define  MA_NO_SWITCH_DEFAULT  MA_HINT(0)



//#include <malius/preprocessor.hpp>
// actually only works with literal 0 for false
//#define  MA_UNUSED(boolean)   MA_PP_IF(boolean)((void)0, (void)1)
#define  MA_UNUSED(boolean)  (boolean) ? (void)0 : (void)1     // if the boolean is const the compiler can optimize this
