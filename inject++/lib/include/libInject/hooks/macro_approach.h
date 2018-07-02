#pragma once

#define STRINGIFY_2(value) #value
#define STRINGIFY(value) STRINGIFY_2(value)

#ifdef __clang__
#	if defined(MA_COMPILE_TIME_RUN)
// #	define MA_ANNOTATE(value) __attribute__((annotate(STRINGIFY(value))))
// #	define MA_ANNOTATE(value) __attribute__((annotate(#value)))
// #	define MA_ANNOTATE(value) __attribute__((annotate(value)))
#		define MA_ANNOTATE(...) __attribute__((annotate(#__VA_ARGS__)))
#	else
#		define MA_ANNOTATE(...)
#	endif //MA_COMPILE_TIME_RUN

#endif //__clang__

#define MA_RUN MA_ANNOTATE(ma_run)