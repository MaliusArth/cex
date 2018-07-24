#pragma once

#define STRINGIFY_2(value) #value
#define STRINGIFY(value) STRINGIFY_2(value)

#ifdef __clang__
#	if defined(CEX_RUN_USE)
// #	define MA_ANNOTATE(value) __attribute__((annotate(STRINGIFY(value))))
// #	define MA_ANNOTATE(value) __attribute__((annotate(#value)))
// #	define MA_ANNOTATE(value) __attribute__((annotate(value)))
#		define MA_ANNOTATE(...) __attribute__((annotate(#__VA_ARGS__)))
#	else
#		define MA_ANNOTATE(...)
#	endif //CEX_RUN_USE

#endif //__clang__

#define CEX_RUN MA_ANNOTATE(cex_run)