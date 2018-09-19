
#pragma	once
#include	<iostream>
#include	<cmath>
#include	<type_traits>
#include	<memory>
#include	<string>

#define	__begin_ns_tsp	namespace	tsp {
#define	__end_ns_tsp	}

__begin_ns_tsp

using size_t = std::size_t;

template	<typename float_type>
static const float_type	inf = float_type(1) / float_type(0);

template	<typename value_type>
constexpr std::enable_if_t<std::is_floating_point_v<value_type>, value_type>
abs(value_type value)
{
	return (value == inf<value_type> || value == -inf<value_type> ? inf<value_type> : std::abs(value));
}

template	<typename value_type>
constexpr std::enable_if_t<std::is_arithmetic_v<value_type> && !std::is_floating_point_v<value_type>, value_type>
abs(value_type value)
{
	return std::abs(value);
}

template	<typename value_type, typename ... types>
constexpr std::enable_if_t<std::is_arithmetic_v<value_type>, value_type>
min(value_type value, types ... values)
{
	return std::min({ value, values... });
}

template	<typename value_type, typename ... types>
constexpr std::enable_if_t<std::is_arithmetic_v<value_type>, value_type>
max(value_type value, types ... values)
{
	return std::max({ value, values... });
}

template	<typename value_type, typename ... types>
constexpr std::enable_if_t<std::is_floating_point_v<value_type>, value_type>
avg(value_type value, types ... values)
{
	std::initializer_list<value_type>	__ilist = { value, values... };
	value_type	__sum = value_type();
	for (const auto& i : __ilist)
		__sum += i;
	__sum /= __ilist.size();
	return __sum;
}

constexpr size_t	factorial(size_t value)
{
	static_assert(sizeof(size_t) == 8);
	if (value > 20)
		throw std::domain_error("Factorial is too large to compute");
	return (!value ? 1 : value * factorial(value - 1));
}

template	<typename string_type>
constexpr size_t str_hash(const string_type& string)
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
constexpr size_t str_hash(const char (&string)[length])
{
	return str_hash(std::string_view(string));
}

__end_ns_tsp
