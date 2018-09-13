
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"vertex.hpp"
#include	"edge.hpp"
#include	<list>
#include	<vector>

__begin_ns_tsp

template	<typename __float_type>
class	__graph_private::__graph_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
protected:
	std::list<edge<float_type>>		__edges;
	std::vector<vertex<float_type>>	__vertices;
public:
	__graph_base(size_t size)
	{
		__vertices.reserve(size);
	}
	~__graph_base()
	{
		__edges.remove_if([](const edge<float_type>& edge)
						  {
							  return (edge.self_edge());
						  });
	}
	__attribute__((always_inline))
	const auto&	edges() const	{ return __edges; }
	__attribute__((always_inline))
	const auto& vertices() const	{ return __vertices; }
	__attribute__((always_inline))
	void	add_vertex(const std::string& name)
	{
		__vertices.emplace_back(vertex<float_type>(name));
		__edges.emplace_back(edge<float_type>(__vertices.back(), __vertices.back()));
	}
	__attribute__((always_inline))
	void	remove_vertex(size_t index)
	{
		__edges.remove_if([this, &index](const edge<float_type>& edge)
						  {
							  return ((edge.vertex_pair().first == __vertices.at(index) &&
									   edge.vertex_pair().second == __vertices.at(index)));
						  });
		__vertices.erase(__vertices.at(index));
	}
	__attribute__((always_inline))
	void	add_edge(size_t index_a, size_t index_b, float_type weight)
	{
		if (index_a == index_b)
			throw std::invalid_argument("Cannot manually create self-edge");
		__edges.emplace_back(edge<float_type>(__vertices.at(index_a), __vertices.at(index_b), weight));
	}
	__attribute__((always_inline))
	void	remove_edge(size_t index_a, size_t index_b)
	{
		__edges.remove_if([this, &index_a, &index_b](const edge<float_type>& edge)
						  {
							  return (index_a != index_b &&
									  ((edge.vertex_pair().first == __vertices.at(index_a) &&
										edge.vertex_pair().second == __vertices.at(index_b)) ||
									   (edge.vertex_pair().first == __vertices.at(index_b) &&
										edge.vertex_pair().second == __vertices.at(index_a))));
						  });
	}
};

template	<typename __float_type>
class	graph : public __graph_private::__graph_base<__float_type>
{
public:
	using __base = __graph_private::__graph_base<__float_type>;
	using float_type = typename __base::float_type;
	graph(size_t size) : __base(size) {  }
};

__end_ns_tsp
