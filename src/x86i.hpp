
#pragma	once
#include	<type_traits>
#include	<new>

#if SIMD_SUPPORTED_LEVEL >= SIMD_LEVEL_x86_AVX2
#	if	defined(__GNUC__)
#		include	<x86intrin.h>
#	else
#		include	<immintrin.h>
#	endif
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_AVX
#	include	<immintrin.h>
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE4_2
#	include	<nmmintrin.h>
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE4_1
#	include	<smmintrin.h>
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSSE3
#	include	<tmmintrin.h>
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE3
#	include	<pmmintrin.h>
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE2
#	include	<emmintrin.h>
#elif	SIMD_SUPPORTED_LEVEL == SIMD_LEVEL_x86_SSE
#	include	<xmmintrin.h>
#endif


#define	__begin_ns_x86i	namespace x86i {
#define	__end_ns_x86i	}
#define	__begin_ns_sse	namespace sse {
#define	__end_ns_sse	}
#define	__begin_ns_avx	namespace avx {
#define	__end_ns_avx	}

#if	defined(__SSE__)
__begin_ns_sse

typedef	__m128	float_t;
typedef	__m128d	double_t;
typedef	__m128i	int_t;

constexpr uint64_t	next_mul(uint64_t value, uint64_t mul)
{
	return (!(value % mul) ? value : uint64_t(value / mul) * mul + mul);
}

__end_ns_sse
#else
__begin_ns_sse

typedef	float	float_t;
typedef	double	double_t;
typedef	int	int_t;

constexpr uint64_t	next_mul(uint64_t value, uint64_t mul)
{
	return (!(value % mul) ? value : uint64_t(value / mul) * mul + mul);
}

__end_ns_sse
#endif

__begin_ns_x86i

static constexpr size_t	align = (alignof(max_align_t) > 16 ? alignof(max_align_t) : 16);
static constexpr std::align_val_t	align_v = std::align_val_t(align);

void	check();

__end_ns_x86i
