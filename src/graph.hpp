
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"vertex.hpp"
#include	"edge.hpp"
#include	"hash.hpp"
#include	<list>
#include	<vector>
#include	<unordered_map>
#include	<unordered_set>

__begin_ns_tsp

template	<typename __float_type, typename __key_type>
class	__graph_private::__graph_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
	using key_type = __key_type;
protected:
	using edge_type = edge<float_type, key_type>;
	std::unordered_set<edge_type, hash_class<edge_type>>		__edges;
	std::unordered_map<key_type, vertex<float_type, key_type>>	__vertices;
	
	inline __attribute__((always_inline))
	void	__add_one_edge(const key_type& from, const key_type& to, float_type weight)
	{
		if (__edges.count(tsp::edge<float_type, key_type>(__vertices.at(from), __vertices.at(to))))
			throw std::invalid_argument("Edge already exists");
		__edges.emplace(__vertices.at(from), __vertices.at(to), weight);
		for (auto& edge : __edges)
		{
			if (edge.from() == __vertices.at(from) && edge.to() == __vertices.at(to))
			{
				const_cast<edge_type&>(edge).link();
			}
		}
	}
	inline __attribute__((always_inline))
	void	__remove_one_edge(const key_type& from, const key_type& to)
	{
		for (auto& edge : __edges)
		{
			if (edge.from() == __vertices.at(from) && edge.to() == __vertices.at(to))
			{
				const_cast<edge_type&>(edge).unlink();
				__edges.erase(edge);
			}
		}
	}
public:
	__graph_base(size_t size)
	{
		__vertices.reserve(size);
	}
	~__graph_base()
	{
		__edges.clear();
	}
	__attribute__((always_inline))
	const vertex<float_type, key_type>&	vertex(const key_type& key) const
	{
		return __vertices.at(key);
	}
	__attribute__((always_inline))
	const edge<float_type, key_type>&	edge(const key_type& from, const key_type& to) const
	{
		for (auto& edge : __edges)
		{
			if (edge.from() == __vertices.at(from) && edge.to() == __vertices.at(to))
			{
				return edge;
			}
		}
		throw std::out_of_range("Edge does not exist");
	}
	__attribute__((always_inline))
	size_t	size() const
	{
		return __vertices.size();
	}
	__attribute__((always_inline))
	const auto&	edges() const
	{
		return __edges;
	}
	__attribute__((always_inline))
	const auto& vertices() const
	{
		return __vertices;
	}
	__attribute__((always_inline))
	void	add_vertex(const key_type& key)
	{
		if (__vertices.count(key))
			throw std::invalid_argument("Vertex with this name already exists");
		__vertices.emplace(key, key);
		__add_one_edge(key, key, inf<float_type>);
	}
	__attribute__((always_inline))
	void	remove_vertex(const key_type& key)
	{
		__remove_one_edge(key, key);
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
	
	template	<typename float_type, typename key_type>
	friend class	tree;
	template	<typename float_type, typename key_type>
	friend void	brute_force(tree<float_type, key_type>& tree, graph<float_type, key_type>& graph, const key_type& start);
	template	<typename float_type, typename key_type>
	friend void	branch_and_bound(tree<float_type, key_type>& tree, graph<float_type, key_type>& graph, const key_type& start);
protected:
	inline __attribute__((always_inline))
	void	visit(const std::vector<key_type>& keys)
	{
		for (auto& key : keys)
		{
			__base::__vertices.at(key).visit(true);
		}
	}
	inline __attribute__((always_inline))
	void	clear_visit()
	{
		for (auto& vertex : __base::__vertices)
		{
			vertex.second.visit(false);
		}
	}
public:
	graph(size_t size) : __base(size) {  }
	__attribute__((always_inline))
	void	add_edge(const key_type& from_to, const key_type& to_from, float_type weight)
	{
		if (from_to == to_from)
			throw std::invalid_argument("Cannot manually create self-edge");
		__base::__add_one_edge(from_to, to_from, weight);
		__base::__add_one_edge(to_from, from_to, weight);
	}
	__attribute__((always_inline))
	void	remove_edge(const key_type& from_to, const key_type& to_from)
	{
		if (from_to == to_from)
			throw std::invalid_argument("Cannot manually remove self-edge");
		__base::__remove_one_edge(from_to, to_from);
		__base::__remove_one_edge(to_from, from_to);
	}
	template	<typename function_t>
	std::enable_if_t<is_stringy_v<key_type>, std::string>	tsp(const key_type& start, function_t function)
	{
		std::string	str;
		tsp::tree<float_type, key_type>	tree(*this, start, function);
		float_type	__minweight = inf<float_type>;
		tsp::node<float_type, key_type>*	__node = nullptr;
		for (auto& node : tree.nodes())
		{
			if (node.leaf() && node.lineage().size() == __base::size() && node.lineage_weight() < __minweight)
			{
				__minweight = node.lineage_weight();
				__node = const_cast<tsp::node<float_type, key_type>*>(&node);
			}
		}
		str += "(" + std::to_string(__node->lineage_weight()) + ")\t";
		for (auto& pt : __node->lineage())
		{
			str += std::string(pt) + "< ";
		}
		str = str.substr(0, str.length() - 2);
		return str;
	}
//	template	<typename function_t>
//	std::enable_if_t<!is_stringy_v<key_type>, std::string>	tsp(const key_type& start, function_t function)
//	{
//		std::string	str;
//		tsp::tree<float_type, key_type>	tree(*this, start, function);
//		float_type	__minweight = inf<float_type>;
//		tsp::node<float_type, key_type>*	__node = nullptr;
//		for (auto& node : tree.nodes())
//		{
//			if (node.leaf() && node.lineage().size() == __base::size() && node.lineage_weight() < __minweight)
//			{
//				__minweight = node.lineage_weight();
//				__node = &node;
//			}
//		}
//		str += "(" + std::to_string(__node->lineage_weight()) + ")\t";
//		for (auto& pt : __node->lineage())
//		{
//			str += std::to_string(pt) + "< ";
//		}
//		str = str.substr(0, str.length() - 2);
//		return str;
//	}
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
		if (from == to)
			throw std::invalid_argument("Cannot manually create self-edge");
		__base::__add_one_edge(from, to, weight);
	}
	__attribute__((always_inline))
	void	remove_edge(const key_type& from, const key_type& to)
	{
		if (from == to)
			throw std::invalid_argument("Cannot manually remove self-edge");
		__base::__remove_one_edge(from, to);
	}
};

__end_ns_tsp
