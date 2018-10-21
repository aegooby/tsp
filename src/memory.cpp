
#include	"__common.hpp"
#include	"memory.hpp"

__attribute__((always_inline))
void*	operator new(std::size_t bytes)
{
	return ::operator new(bytes, x86i::align_v);
}
__attribute__((always_inline))
void	operator delete(void* ptr) noexcept
{
	::operator delete(ptr, x86i::align_v);
}

__begin_ns_tsp
__begin_ns_memory

__attribute__((always_inline))
void*	__memory_private::allocate(size_t bytes, align_t align)
{
	return operator new(bytes, align);
}
__attribute__((always_inline))
void	__memory_private::deallocate(void* ptr, align_t align)
{
	operator delete(ptr, align);
}

__end_ns_memory
__end_ns_tsp
