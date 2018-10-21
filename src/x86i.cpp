
#include	"__common.hpp"
#include	"x86i.hpp"
#include	<iostream>

__begin_ns_x86i

void	check()
{
	std::clog << "Intel x86 SIMD intrinsics:" << std::endl;

	std::clog << "  * Compiler:";
#if	defined(TSP_COMPILER_CLANG)
#	if	defined(__APPLE__) && (__MACH__)
	std::clog << " Apple LLVM";
#	else
	std::clog << " clang";
#	endif
	std::clog << " (version " << __clang_major__ << ".";
	std::clog << __clang_minor__ << "." << __clang_patchlevel__ << ")";
#elif	defined(TSP_COMPILER_GCC)
	std::clog << " gcc (version " << __GNUC__ << ".";
	std::clog << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << ")";
#elif	defined(TSP_COMPILER_MSVC)
	std::clog << " MSVC (version " << _MSC_VER << ")";
#elif	defined(TSP_COMPILER_INTEL)
	std::clog << " Intel C Compiler (version " << __INTEL_COMPILER << ")";
#else
	std::clog << " unknown";
#endif
	std::clog << std::endl;

	std::clog << "  * AVX:";
#if	defined(__AVX2__)
	std::clog << " version 2";
#elif	defined(__AVX__)
	std::clog << " version 1";
#else
	std::clog << " not supported";
#endif
	std::clog << std::endl;

	std::clog << "  * SSE:";
#if	defined(__SSE4_2__)
	std::clog << " version 4.2";
#elif	defined(__SSE4_1__)
	std::clog << " version 4.1";
#elif	defined(__SSE3__)
	std::clog << " version 3";
#elif	defined(__SSE2__)
	std::clog << " version 2";
#elif	defined(__SSE__)
	std::clog << " version 1";
#else
	std::clog << " not supported" << std::endl;
#endif
	std::clog << std::endl;

	std::clog << "  * SSE Math:";
#if	defined(__SSE2_MATH__)
	std::clog << " version 2";
#elif	defined(__SSE_MATH__)
	std::clog << " version 1";
#else
	std::clog << " not supported";
#endif
	std::clog << std::endl;

	std::clog << std::endl;
}

__end_ns_x86i
