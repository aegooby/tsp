
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"vertex.hpp"
#include	<type_traits>

__begin_ns_tsp

template	<typename __float_type, typename __key_type>
class	__edge_private::__edge_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
	using key_type = __key_type;
	template	<class derived, typename float_type, typename key_type, size_t size>
	friend class	__graph_private::__graph_base;
	template	<typename float_type, typename key_type, size_t>
	friend class	graph;
protected:
	using vertex_ref = vertex<float_type, key_type>&;
	using const_vertex_ref = const vertex<float_type, key_type>&;
	bool								__visited = false;
	float_type							__weight = float_type();
	std::pair<vertex_ref, vertex_ref>	__vertex_pair;
public:
	__edge_base(const std::pair<vertex_ref, vertex_ref>& pair)
	: __vertex_pair(pair) {  }
	__edge_base(const std::pair<vertex_ref, vertex_ref>& pair, float_type weight)
	: __weight(weight), __vertex_pair(pair) {  }
	__edge_base(vertex_ref from, vertex_ref to)
	: __vertex_pair(from, to)
	{
		if (from == to)
			__weight = inf<float_type>;
	}
	__edge_base(vertex_ref from, vertex_ref to, float_type weight)
	: __weight(weight), __vertex_pair(from, to)
	{
		if (from == to)
			__weight = inf<float_type>;
	}
	__attribute__((always_inline))
	bool	visited() const
	{
		return __visited;
	}
	__attribute__((always_inline))
	void	visited(bool visited)
	{
		__visited = visited;
	}
	__attribute__((always_inline))
	bool	self_edge() const
	{
		return (__vertex_pair.first == __vertex_pair.second);
	}
	__attribute__((always_inline))
	const auto&	vertex_pair() const
	{
		return __vertex_pair;
	}
	__attribute__((always_inline))
	const auto&	from() const
	{
		return __vertex_pair.first;
	}
	__attribute__((always_inline))
	const auto&	to() const
	{
		return __vertex_pair.second;
	}
	__attribute__((always_inline))
	float_type	weight() const
	{
		return __weight;
	}
	__attribute__((always_inline))
	void	weight(int weight)
	{
		__weight = tsp::abs(weight);
	}
};

template	<typename __float_type, typename __key_type>
class	edge : public __edge_private::__edge_base<__float_type, __key_type>
{
public:
	using __base = __edge_private::__edge_base<__float_type, __key_type>;
	using float_type = typename __base::float_type;
	using key_type = typename __base::key_type;
	using vertex_ref = typename __base::vertex_ref;
	template	<class derived, typename float_type, typename key_type, size_t size>
	friend class	__graph_private::__graph_base;
	template	<typename float_type, typename key_type, size_t size>
	friend class	graph;
protected:
	using pair_ref = std::pair<vertex_ref, vertex_ref>&;
	using const_pair_ref = const std::pair<vertex_ref, vertex_ref>&;
private:
	__attribute__((always_inline))
	void	link()
	{
		__base::__vertex_pair.first.add_edge(*this);
	}
	__attribute__((always_inline))
	void	unlink()
	{
		__base::__vertex_pair.first.remove_edge(*this);
	}
public:
	edge(const_pair_ref pair) : __base(pair) {  }
	edge(const_pair_ref pair, float_type weight) : __base(pair, weight) {  }
	edge(vertex_ref from, vertex_ref to) : __base(from, to) {  }
	edge(vertex_ref from, vertex_ref to, float_type weight) : __base(from, to, weight) {  }
	~edge() = default;
	edge(const edge& other) : __base(other.__vertex_pair, other.__weight) {  }
	edge(edge&& other) : __base(other.__vertex_pair, other.__weight) {  }
};

template	<typename float_type, typename key_type>
bool	operator ==(const edge<float_type, key_type>& edge_a, const edge<float_type, key_type>& edge_b)
{
	return (edge_a.vertex_pair() == edge_b.vertex_pair());
}
template	<typename float_type, typename key_type>
bool	operator !=(const edge<float_type, key_type>& edge_a, const edge<float_type, key_type>& edge_b)
{
	return !(edge_a == edge_b);
}

template	<typename float_type, typename key_type>
std::ostream&	operator <<(std::ostream& ostr, const edge<float_type, key_type>& edge)
{
	ostr << "edge(" << edge.from().key() << " -> " << edge.to().key() << ", weight: " << edge.weight() << ")";
	return ostr;
}

__end_ns_tsp
