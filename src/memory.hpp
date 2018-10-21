
#pragma	once
#include	"__common.hpp"
#include	<new>
#include	<memory>
#include	<cstdlib>

#define	__begin_ns_memory	namespace	memory {
#define	__end_ns_memory		}

void*	operator new(std::size_t bytes);
void	operator delete(void* ptr) noexcept;

__begin_ns_tsp

using align_t = std::align_val_t;
using max_align_t = std::max_align_t;

__end_ns_tsp

__begin_ns_tsp
__begin_ns_memory

class	__memory_private
{
private:
	static void*	allocate(size_t bytes, align_t align);
	static void		deallocate(void* ptr, align_t align);
public:
	template	<class type>
	friend type*	allocate(type*&, size_t, align_t);
	template	<class type>
	friend type*	allocate(type*&);
	template	<class type>
	friend type*	allocate(type*&, size_t);
	template	<class type>
	friend type*	allocate(type*&, align_t);
	template	<class type>
	friend void		deallocate(type*&, align_t);
	template	<class type>
	friend void		deallocate(type*&);
	
	__memory_private() = delete;
	__memory_private(const __memory_private&) = delete;
	__memory_private(__memory_private&&) = delete;
	__memory_private&	operator =(const __memory_private&) = delete;
	__memory_private&	operator =(__memory_private&&) = delete;
};

template	<class type>
inline __attribute__((always_inline))
type* 	allocate(type* ptr, size_t count, align_t align)
{
	//	Allocation and assignment to parameter "ptr" is already done inside this
	//	function, but it returns "ptr" for ease of use.
	return static_cast<type*>(__memory_private::allocate(count * sizeof(type), align));
}
template	<class type>
inline __attribute__((always_inline))
type* 	allocate(type*& ptr)
{
	ptr = static_cast<type*>(__memory_private::allocate(sizeof(type), x86i::align_v));
	return ptr;
}
template	<class type>
inline __attribute__((always_inline))
type* 	allocate(type*& ptr, size_t count)
{
	ptr = static_cast<type*>(__memory_private::allocate(count * sizeof(type), x86i::align_v));
	return ptr;
}
template	<class type>
inline __attribute__((always_inline))
type* 	allocate(type*& ptr, align_t align)
{
	ptr = static_cast<type*>(__memory_private::allocate(sizeof(type), align));
	return ptr;
}
template	<class type, class ... types>
inline __attribute__((always_inline))
type* 	construct(type* ptr, types&& ... args)
{
	//	Construction should always be done inside of a RAII container,
	//	and should always be implemented in sequential order.

	//	Conditional static_assert to improve error readibility when attempting
	//	to default-initialize a class with a deleted default constructor.
	if constexpr(!sizeof...(args))
		static_assert(std::is_default_constructible_v<type>);

	//	Placement-new on selected block of memory.
	//	Type "type" may need to be typecasted if working with nested containers.
	new(ptr) type(std::forward<types>(args)...);
	return ptr;
}
template	<class type>
inline __attribute__((always_inline))
void 	destruct(type* ptr)
{
	//	Destructs in reverse order, which is why construct() should always be
	//	implemented in sequential order.
	ptr->~type();
}
template	<class type>
inline __attribute__((always_inline))
void 	deallocate(type*& ptr, align_t align)
{
	//	Always call after destruct()
	__memory_private::deallocate((void*)const_cast<type*>(ptr), align);
	ptr = nullptr;
}
template	<class type>
inline __attribute__((always_inline))
void 	deallocate(type*& ptr)
{
	__memory_private::deallocate((void*)const_cast<type*>(ptr), x86i::align_v);
	ptr = nullptr;
}

__end_ns_memory
__end_ns_tsp
