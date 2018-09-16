
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	<list>
#include	<functional>

__begin_ns_tsp

template	<typename __float_type>
class	__vertex_private::__vertex_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
protected:
	using edge_refw = std::reference_wrapper<edge<float_type>>;
	std::list<edge_refw>	__edges;
	std::string				__name;
	
	__attribute__((always_inline))
	void	add_edge(edge<float_type>& edge)
	{
		__edges.push_back(edge);
	}
	__attribute__((always_inline))
	void	remove_edge(edge<float_type>& edge)
	{
		size_t	__removals = 0;
		__edges.remove_if([&edge, &__removals](const tsp::edge<float_type>& check)
						  {
							  return (edge == check) && !__removals++;
						  });
	}
public:
	__vertex_base(const std::string& name) : __name(name) {  }
	__attribute__((always_inline))
	const std::string&	name() const	{ return __name; }
	__attribute__((always_inline))
	auto&	edges()	{ return __edges; }
	__attribute__((always_inline))
	const auto&	edges() const	{ return __edges; }
	__attribute__((always_inline))
	bool	linked() const	{ return bool(__edges.size()); }
};
template	<typename __float_type>
class	vertex : public __vertex_private::__vertex_base<__float_type>
{
public:
	using __base = __vertex_private::__vertex_base<__float_type>;
	using float_type = typename __base::float_type;
	template	<typename float_type>
	friend class	edge;
	vertex(const std::string& name) : __base(name) {  }
};

template	<typename float_type>
bool	operator ==(const vertex<float_type>& vertex_a, const vertex<float_type>& vertex_b)
{
	return (&vertex_a == &vertex_b);
}
template	<typename float_type>
bool	operator !=(const vertex<float_type>& vertex_a, const vertex<float_type>& vertex_b)
{
	return !(vertex_a == vertex_b);
}

template	<typename float_type>
std::ostream&	operator <<(std::ostream& ostr, const vertex<float_type>& vertex)
{
	std::string	str;
	str += "vertex(\"" + vertex.name() + "\", links to: ";
	for (const auto& edge : vertex.edges())
	{
		if (edge.get().to().name() == vertex.name())
			str += "self, ";
		else
			str += edge.get().to().name() + ", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ")";
	ostr << str;
	return ostr;
}

__end_ns_tsp
