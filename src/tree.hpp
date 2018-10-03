
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"node.hpp"
#include	"graph.hpp"

__begin_ns_tsp

enum class	brute_force {  };

template	<typename __float_type, typename __key_type>
class	__tree_private::__tree_base
{
	static_assert(std::is_floating_point_v<__float_type>);
public:
	using float_type = __float_type;
	using key_type = __key_type;
protected:
	std::vector<node<float_type, key_type>>	__nodes;
public:
	__tree_base(size_t size)
	{
		__nodes.reserve(size);
	}
	__tree_base(size_t size, const key_type& root_key)
	{
		__nodes.reserve(size);
		__nodes.emplace_back(root_key);
	}
	__attribute__((always_inline))
	const std::vector<node<float_type, key_type>>&	nodes() const
	{
		return __nodes;
	}
	__attribute__((always_inline))
	const node<float_type, key_type>&	node(size_t index) const
	{
		return __nodes.at(index);
	}
	__attribute__((always_inline))
	size_t	add_node(const key_type& key, size_t parent_index, float_type weight)
	{
		__nodes.emplace_back(key, __nodes.at(size_t(parent_index)), weight);
		if (!__nodes.back().root())
		{
			__nodes.at(parent_index).add_child(__nodes.back(), weight);
		}
		return __nodes.size() - 1;
	}
	__attribute__((always_inline))
	size_t	add_node(const key_type& key, std::nullptr_t null)
	{
		__nodes.emplace_back(key);
		return __nodes.size() - 1;
	}
	__attribute__((always_inline))
	size_t	add_node(const key_type& key, tsp::node<float_type, key_type>& parent, float_type weight)
	{
		__nodes.emplace_back(key, parent, weight);
		if (!__nodes.back().root())
		{
			parent.add_child(__nodes.back(), weight);
		}
		return __nodes.size() - 1;
	}
	__attribute__((always_inline))
	void	remove_node(size_t index)
	{
		auto	__pred = [this, &index](const tsp::node<float_type, key_type>& node)
		{
			return (__nodes.at(index) == node);
		};
		if (!__nodes.at(index).root())
		{
			__nodes.at(index).__parent.remove_child(__nodes.at(index));
			__nodes.erase(std::remove_if(__nodes.begin(), __nodes.end(), __pred));
		}
	}
	
};

template	<typename __float_type, typename __key_type>
class	tree : public __tree_private::__tree_base<__float_type, __key_type>
{
public:
	using __base = __tree_private::__tree_base<__float_type, __key_type>;
	using float_type = typename __base::float_type;
	using key_type = typename __base::key_type;
protected:
	size_t	__nodec_graph(size_t graph_size)
	{
		size_t	__res = 1, __term = 1;
		for (size_t __sz = graph_size - 1; __sz > 1; --__sz)
		{
			__term *= __sz;
			__res += __term;
		}
		__res += __term;
		return __res;
	}
public:
	tree(size_t size, const key_type& root_key) : __base(size, root_key) {  }
	tree(graph<float_type, key_type>& graph, const key_type& start, brute_force flag) : __base(__nodec_graph(graph.size()), start)
	{
		bool	__done = false;
		size_t	__desired = graph.size() - 1;
		while (!__done)
		{
			__done = true;
			for (auto& node : __base::__nodes)
			{
				if (node.leaf() && node.lineage().size() < __desired)
					__done = false;
			}
			for (auto& node : __base::__nodes)
			{
				if (node.leaf())
				{
					graph.visit(node.lineage());
					for (auto& edge : graph.vertex(node.key()).edges())
					{
						if (!edge.second.get().self_edge())
							__base::add_node(edge.second.get().to().key(), node, edge.second.get().weight());
					}
				}
				graph.clear_visit();
			}
		}
	}
	
};

__end_ns_tsp
