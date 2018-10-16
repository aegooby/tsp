
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

template	<typename container_type, typename value_type>
auto	contains(const container_type& container, const value_type& value) -> decltype(container.begin(), container.end(), bool())
{
	for (const auto& i : container)
	{
		if (i == value)
			return true;
	}
	return false;
}

__end_ns_tsp
