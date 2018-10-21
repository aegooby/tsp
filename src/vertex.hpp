
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	<functional>
#include	<unordered_map>

__begin_ns_tsp

template	<typename __float_type, typename __key_type>
class	__vertex_private::__vertex_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
	using key_type = __key_type;
protected:
	using edge_refw = std::reference_wrapper<edge<float_type, key_type>>;
	std::unordered_map<key_type, edge_refw>	__edges;
	key_type								__key;
	bool									__visited = false;
	
	__attribute__((always_inline))
	void	add_edge(edge<float_type, key_type>& edge)
	{
		__edges.emplace(edge.to().key(), edge);
		__edges.emplace(edge.to().key(), edge);
	}
	__attribute__((always_inline))
	void	remove_edge(edge<float_type, key_type>& edge)
	{
		__edges.erase(edge.to().key());
	}
public:
	__vertex_base(const key_type& key) : __key(key) {  }
	__attribute__((always_inline))
	const key_type&	key() const
	{
		return __key;
	}
	__attribute__((always_inline))
	edge<float_type, key_type>&	edge(const key_type& key_to)
	{
		return __edges.at(key_to);
	}
	__attribute__((always_inline))
	const auto&	edges() const
	{
		return __edges;
	}
	__attribute__((always_inline))
	bool	linked() const
	{
		return bool(__edges.size());
	}
};
template	<typename __float_type, typename __key_type>
class	vertex : public __vertex_private::__vertex_base<__float_type, __key_type>
{
public:
	using __base = __vertex_private::__vertex_base<__float_type, __key_type>;
	using float_type = typename __base::float_type;
	using key_type = typename __base::key_type;
protected:
	void	visit(bool flag)
	{
		__base::__visited = flag;
	}
	void	visited() const
	{
		return __base::__visited;
	}
public:
	template	<typename float_type, typename key_type>
	friend class	edge;
	template	<typename float_type, typename key_type, size_t size>
	friend class	graph;
	template	<typename float_type, typename key_type>
	friend class	tree;
	vertex(const key_type& name) : __base(name) {  }
	~vertex() = default;
};

template	<typename float_type, typename key_type>
bool	operator ==(const vertex<float_type, key_type>& vertex_a, const vertex<float_type, key_type>& vertex_b)
{
	return (&vertex_a == &vertex_b);
}
template	<typename float_type, typename key_type>
bool	operator !=(const vertex<float_type, key_type>& vertex_a, const vertex<float_type, key_type>& vertex_b)
{
	return !(vertex_a == vertex_b);
}

template	<typename float_type, typename key_type>
auto	operator <<(std::ostream& ostr, const vertex<float_type, key_type>& vertex)
-> decltype(std::string(vertex.key()), ostr)
{
	std::string	str;
	str += "vertex(\"" + std::string(vertex.key()) + "\", links to: ";
	for (const auto& edge : vertex.edges())
	{
		if (edge.second.get().to().key() == vertex.key())
			str += "self, ";
		else
			str += std::string(edge.second.get().to().key()) + ", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ")";
	ostr << str;
	return ostr;
}

template	<typename float_type, typename key_type>
auto	operator <<(std::ostream& ostr, const vertex<float_type, key_type>& vertex)
-> decltype(std::to_string(vertex.key()), ostr)
{
	std::string	str;
	str += "vertex(\"" + std::to_string(vertex.key()) + "\", links to: ";
	for (const auto& edge : vertex.edges())
	{
		if (edge.second.get().to().key() == vertex.key())
			str += "self, ";
		else
			str += std::to_string(edge.second.get().to().key()) + ", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ")";
	ostr << str;
	return ostr;
}

__end_ns_tsp
