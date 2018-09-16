
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"vertex.hpp"
#include	"edge.hpp"
#include	<list>
#include	<vector>
#include	<unordered_map>

__begin_ns_tsp

template	<typename __float_type, typename __key_type>
class	__graph_private::__graph_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
	using key_type = __key_type;
protected:
	std::list<edge<float_type>>							__edges;
	std::unordered_map<key_type, vertex<float_type>>	__vertices;
	
	__attribute__((always_inline))
	void	__add_one_edge(const key_type& from, const key_type& to, float_type weight)
	{
		if (from == to)
			throw std::invalid_argument("Cannot manually create self-edge");
		__edges.emplace_back(edge<float_type>(__vertices.at(from), __vertices.at(to), weight));
	}
	__attribute__((always_inline))
	void	__remove_one_edge(const key_type& from, const key_type& to)
	{
		__edges.remove_if([this, &from, &to](const edge<float_type>& edge)
						  {
							  return (from != to &&
									  __vertices.at(from) == edge.from() &&
									  __vertices.at(to) == edge.to());
						  });
	}
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
	void	add_vertex(const key_type& key)
	{
		__vertices.emplace(key, vertex<float_type>(std::to_string(key)));
		__edges.emplace_back(edge<float_type>(__vertices.at(key), __vertices.at(key)));
	}
	__attribute__((always_inline))
	void	remove_vertex(const key_type& key)
	{
		__edges.remove_if([this, &key](const edge<float_type>& edge)
						  {
							  return ((edge.from() == __vertices.at(key) &&
									   edge.to() == __vertices.at(key)));
						  });
		__vertices.erase(__vertices.at(key));
	}
};

template	<typename __float_type, typename __key_type>
class	graph : public __graph_private::__graph_base<__float_type, __key_type>
{
public:
	using __base = __graph_private::__graph_base<__float_type, __key_type>;
	using float_type = typename __base::float_type;
	using key_type = typename __base::key_type;
	graph(size_t size) : __base(size) {  }
	__attribute__((always_inline))
	void	add_edge(const key_type& from_to, const key_type& to_from, float_type weight)
	{
		__base::__add_one_edge(from_to, to_from, weight);
		__base::__add_one_edge(to_from, from_to, weight);
	}
	__attribute__((always_inline))
	void	remove_edge(const key_type& from_to, const key_type& to_from)
	{
		__base::__remove_one_edge(from_to, to_from);
		__base::__remove_one_edge(to_from, from_to);
	}
};

template	<typename __float_type, typename __key_type>
class	digraph : public __graph_private::__graph_base<__float_type, __key_type>
{
public:
	using __base = __graph_private::__graph_base<__float_type, __key_type>;
	using float_type = typename __base::float_type;
	using key_type = typename __base::key_type;
	digraph(size_t size) : __base(size) {  }
	__attribute__((always_inline))
	void	add_edge(const key_type& from, const key_type& to, float_type weight)
	{
		__base::__add_one_edge(from, to, weight);
	}
	__attribute__((always_inline))
	void	remove_edge(const key_type& from, const key_type& to)
	{
		__base::__remove_one_edge(from, to);
	}
};

__end_ns_tsp
