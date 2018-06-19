#pragma once

#define STRINGIFY_2(value) #value
#define STRINGIFY(value) STRINGIFY_2(value)

#ifdef __clang__
// #	define MA_ANNOTATE(value) __attribute__((annotate(STRINGIFY(value))))
// #	define MA_ANNOTATE(value) __attribute__((annotate(#value)))
#	define MA_ANNOTATE(value) __attribute__((annotate(value)))
#else
#	define MA_ANNOTATE(value)
#endif

#define MA_INJECT MA_ANNOTATE("injection_hook")