#ifndef PORTING_H
#define PORTING_H

// System-specific definitions.

#ifdef _WIN32
#include <intrin.h>
#define breakpoint()  __debugbreak()
#else
#define breakpoint()  __builtin_trap()
#endif

#endif