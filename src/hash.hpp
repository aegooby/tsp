
#pragma	once
#include	"__common.hpp"
#include	"edge.hpp"

__begin_ns_tsp

class	__hash_private
{
private:
	template	<size_t length>
	static constexpr size_t	__str_hash(const char (&string)[length]);
	template	<typename string_type>
	static constexpr size_t	__str_hash(const string_type& string);
public:
	template	<size_t length>
	friend constexpr size_t	hash(const char (&string)[length]);
	friend constexpr size_t	hash(const char* string);
	template	<typename string_type>
	friend auto	hash(const string_type& string) -> decltype(std::string(string), size_t());
	template	<typename type>
	friend auto	hash(const type& instance) -> decltype(std::hash<type>(), size_t());
};

template	<typename string_type>
constexpr size_t	__hash_private::__str_hash(const string_type& string)
{
	static_assert(sizeof(size_t) == 8);
	size_t	__result = 0xcbf29ce484222325;
	
	for (char character : string)
	{
		__result *= 1099511628211;
		__result ^= character;
	}
	
	return	__result;
}

template	<size_t length>
constexpr size_t	__hash_private::__str_hash(const char (&string)[length])
{
	return __str_hash(std::string_view(string));
}

template	<size_t length>
constexpr size_t	hash(const char (&string)[length])
{
	return __hash_private::__str_hash(std::string_view(string));
}

constexpr size_t	hash(const char* string)
{
	return __hash_private::__str_hash(std::string_view(string));
}

template	<typename string_type>
auto	hash(const string_type& string) -> decltype(std::string(string), size_t())
{
	return __hash_private::__str_hash(string);
}

template	<typename type>
auto	hash(const type& instance) -> decltype(std::hash<type>(), size_t())
{
	return std::hash<type>()(instance);
}

template	<typename float_type, typename key_type>
size_t	hash(const edge<float_type, key_type>& edge)
{
	size_t	__from = size_t(&edge.from());
	size_t	__to = size_t(&edge.to());
	return (((__from + __to) * (__from + __to + 1)) / 2) + __to;
}

template	<class type>
class	hash_class
{
public:
	size_t	operator()(const type& instance) const
	{
		return hash(instance);
	}
};

__end_ns_tsp
