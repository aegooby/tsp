
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"vertex.hpp"
#include	<type_traits>

__begin_ns_tsp

template	<typename __float_type>
class	__edge_private::__edge_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
protected:
	bool												__visited = false;
	float_type											__weight = float_type();
	std::pair<vertex<float_type>&, vertex<float_type>&>	__vertex_pair;
public:
	__edge_base(const std::pair<vertex<float_type>&, vertex<float_type>&>& pair)
	: __vertex_pair(pair) {  }
	__edge_base(const std::pair<vertex<float_type>&, vertex<float_type>&>& pair, float_type weight)
	: __weight(weight), __vertex_pair(pair) {  }
	__edge_base(vertex<float_type>& from, vertex<float_type>& to)
	: __vertex_pair(from, to)
	{
		if (from == to)
			__weight = inf<float_type>;
	}
	__edge_base(vertex<float_type>& from, vertex<float_type>& to, float_type weight)
	: __weight(weight), __vertex_pair(from, to)
	{
		if (from == to)
			__weight = inf<float_type>;
	}
	__attribute__((always_inline))
	bool	visited() const	{ return __visited; }
	__attribute__((always_inline))
	void	visited(bool visited)	{ __visited = visited; }
	__attribute__((always_inline))
	bool	self_edge() const	{ return (__vertex_pair.first == __vertex_pair.second); }
	__attribute__((always_inline))
	const auto&	vertex_pair() const	{ return __vertex_pair; }
	__attribute__((always_inline))
	const auto&	from() const	{ return __vertex_pair.first; }
	__attribute__((always_inline))
	const auto&	to() const	{ return __vertex_pair.second; }
	__attribute__((always_inline))
	float_type	weight() const	{ return __weight; }
	__attribute__((always_inline))
	void	weight(int weight)	{ __weight = tsp::abs(weight); }
};

template	<typename __float_type>
class	edge : public __edge_private::__edge_base<__float_type>
{
public:
	using __base = __edge_private::__edge_base<__float_type>;
	using float_type = typename __base::float_type;
private:
	__attribute__((always_inline))
	void	__link_edges(const std::pair<vertex<float_type>&, vertex<float_type>&>& pair)
	{
		pair.first.add_edge(*this);
	}
	__attribute__((always_inline))
	void	__unlink_edges(const std::pair<vertex<float_type>&, vertex<float_type>&>& pair)
	{
		pair.first.remove_edge(*this);
	}
public:
	edge(const std::pair<vertex<float_type>&, vertex<float_type>&>& pair)
	: __base(pair)
	{
		__link_edges(__base::__vertex_pair);
	}
	edge(const std::pair<vertex<float_type>&, vertex<float_type>&>& pair, float_type weight)
	: __base(pair, weight)
	{
		__link_edges(__base::__vertex_pair);
	}
	edge(vertex<float_type>& from, vertex<float_type>& to)
	: __base(from, to)
	{
		__link_edges(__base::__vertex_pair);
	}
	edge(vertex<float_type>& from, vertex<float_type>& to, float_type weight)
	: __base(from, to, weight)
	{
		__link_edges(__base::__vertex_pair);
	}
	~edge()
	{
		__unlink_edges(__base::__vertex_pair);
	}
	edge(const edge& other) : __base(other.__vertex_pair, other.__weight)
	{
		__link_edges(__base::__vertex_pair);
	}
	edge(edge&& other) : __base(other.__vertex_pair, other.__weight)
	{
		__link_edges(__base::__vertex_pair);
	}
};

template	<typename float_type>
bool	operator ==(const edge<float_type>& edge_a, const edge<float_type>& edge_b)
{
	return (edge_a.vertex_pair() == edge_b.vertex_pair()) && edge_a.weight() == edge_b.weight();
}
template	<typename float_type>
bool	operator !=(const edge<float_type>& edge_a, const edge<float_type>& edge_b)
{
	return !(edge_a == edge_b);
}

template	<typename float_type>
std::ostream&	operator <<(std::ostream& ostr, const edge<float_type>& edge)
{
	ostr << "edge(" << edge.from().name() << " -> " << edge.to().name() << ", weight: " << edge.weight() << ")";
	return ostr;
}

__end_ns_tsp
