
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"
#include	"node.hpp"
#include	"graph.hpp"

__begin_ns_tsp

template	<typename float_type, typename key_type, size_t size>
void	brute_force(tree<float_type, key_type>& tree, graph<float_type, key_type, size>& graph, const key_type& start)
{
	bool		__done = false;
	size_t		__size = graph.size();
	while (!__done)
	{
		__done = true;
		for (auto& node : tree.__nodes)
		{
			if (node.leaf() && node.lineage().size() < __size)
				__done = false;
		}
		for (auto& node : tree.__nodes)
		{
			if (node.leaf())
			{
				graph.visit(node.lineage());
				for (auto& edge : graph.vertex(node.key()).edges())
				{
					if (!edge.second.get().self_edge() && !contains(node.lineage(), edge.second.get().to().key()))
					{
						tree.add_node(edge.second.get().to().key(), node, edge.second.get().weight());
					}
				}
			}
			graph.clear_visit();
		}
	}
	for (auto& node : tree.__nodes)
	{
		if (node.leaf())
		{
			tree.add_node(start, node, graph.edge(node.key(), start).weight());
		}
	}
}
template	<typename float_type, typename key_type, size_t size>
void	nearest_neighbor(tree<float_type, key_type>& tree, graph<float_type, key_type, size>& graph, const key_type& start)
{
	auto*		__current = &graph.vertex(start);
	edge<float_type, key_type>*	__cedge = nullptr;
	size_t		__size = graph.size();
	while (tree.size() < __size)
	{
		float_type	__minweight = inf<float_type>;
		for (auto& edge : __current->edges())
		{
			if (edge.second.get().weight() < __minweight && !contains(tree.node(tree.size() - 1).lineage(), edge.second.get().to().key()))
			{
				__minweight = edge.second.get().weight();
				__cedge = &edge.second.get();
			}
		}
		if (__minweight == inf<float_type>)
			throw std::domain_error("No viable path");
		tree.add_node(__cedge->to().key(), tree.size() - 1, __minweight);
		__current = &__cedge->to();
	}
	for (auto& node : tree.__nodes)
	{
		if (node.leaf())
		{
			tree.add_node(start, tree.size() - 1, graph.edge(node.key(), start).weight());
		}
	}
}
template	<typename float_type, typename key_type, size_t size>
void	branch_and_bound(tree<float_type, key_type>& tree, graph<float_type, key_type, size>& graph, const key_type& start)
{
	tsp::tree<float_type, key_type>	__bound(graph, start, nearest_neighbor<float_type, key_type, size>);
	float_type	__upper = inf<float_type>;
	key_type	__final = key_type();
	for (auto& node : __bound.nodes())
	{
		if (node.leaf())
		{
			__upper = node.lineage_weight();
		}
	}
	
	bool	__done = false;
	size_t	__size = graph.size();
	while (!__done)
	{
		__done = true;
		for (auto& node : tree.__nodes)
		{
			if (node.leaf() && node.lineage().size() < __size && node.lineage_weight() < __upper)
				__done = false;
		}
		for (auto& node : tree.__nodes)
		{
			if (node.leaf() && node.lineage_weight() < __upper)
			{
				graph.visit(node.lineage());
				for (auto& edge : graph.vertex(node.key()).edges())
				{
					if (!edge.second.get().self_edge() && !contains(node.lineage(), edge.second.get().to().key()))
						tree.add_node(edge.second.get().to().key(), node, edge.second.get().weight());
				}
			}
			graph.clear_visit();
		}
	}
	for (auto& node : tree.__nodes)
	{
		if (node.leaf() && node.lineage().size() == __size)
		{
			tree.add_node(start, node, graph.edge(node.key(), start).weight());
		}
	}
	std::cout << tree.size() << std::endl;
}

template	<typename key_type>
std::vector<key_type>	__two_opt_swap(std::vector<key_type>& __tour, size_t __xi, size_t __yi, const key_type& start)
{
	const key_type&	__x = __tour.at(__xi);
	const key_type& __y = __tour.at(__yi);
	if (__x == start || __y == start)
		throw std::runtime_error("Vertices x and y cannot be start vertex");
	std::vector<key_type>	__temp;
	size_t	__size = __tour.size();
	if (!__yi || !__xi)
		throw std::runtime_error("Could not find indices of x and y.");
	if (!(__yi > __xi))
		throw std::runtime_error("Invalid comparative indices of x and y");
	for (size_t i = 0; i < __xi; ++i)
		__temp.push_back(__tour.at(i));
	for (size_t i = __yi; i >= __xi; --i)
		__temp.push_back(__tour.at(i));
	for (size_t i = __yi + 1; i < __size; ++i)
		__temp.push_back(__tour.at(i));
	return __temp;
}

template	<typename float_type, typename key_type, size_t size>
size_t	__tour_cost(const std::vector<key_type>& __tour, const graph<float_type, key_type, size>& __graph)
{
	size_t	__cost = 0;
	for (size_t i = 0; i < __tour.size() - 1; ++i)
	{
		__cost += __graph.edge(__tour.at(i), __tour.at(i + 1)).weight();
	}
	return __cost;
}

template	<typename float_type, typename key_type, size_t size>
void	two_opt(graph<float_type, key_type, size>& graph, const key_type& start)
{
	std::vector<key_type>	tour;
	tour.push_back(start);
	for (auto& vertex : graph.vertices())
	{
		if (vertex.second.key() != start)
			tour.push_back(vertex.second.key());
	}
	tour.push_back(start);
	size_t	__size = tour.size();
	size_t	__new_cost = __tour_cost(tour, graph), __best_cost = 0;
	do
	{
		__best_cost = __new_cost;
		for (size_t __xi = 1; __xi < __size - 1; ++__xi)
		{
			for (size_t __yi = 1; __yi < __size - 1; ++__yi)
			{
				if (__yi > __xi)
				{
					auto	__swapped = __two_opt_swap(tour, __xi, __yi, start);
					if (__tour_cost(__swapped, graph) < __best_cost)
					{
						tour = __swapped;
						__new_cost = __tour_cost(__swapped, graph);
					}
				}
			}
		}
	}
	while (__new_cost < __best_cost);
	std::string	__out;
	for (auto& i : tour)
	{
		__out += i + " -> ";
	}
	__out = __out.substr(0, __out.length() - 3);
	std::cout << __out << std::endl;
	std::cout << __new_cost << std::endl;
}

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
	size_t	size() const
	{
		return __nodes.size();
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
	
	template	<typename float_type, typename key_type, size_t size>
	friend void	brute_force(tree<float_type, key_type>& tree, graph<float_type, key_type, size>& graph, const key_type& start);
	template	<typename float_type, typename key_type, size_t size>
	friend void	nearest_neighbor(tree<float_type, key_type>& tree, graph<float_type, key_type, size>& graph, const key_type& start);
	template	<typename float_type, typename key_type, size_t size>
	friend void	branch_and_bound(tree<float_type, key_type>& tree, graph<float_type, key_type, size>& graph, const key_type& start);
protected:
	size_t	__nodec_graph(size_t graph_size)
	{
		size_t	__res = 1, __term = 1;
		for (size_t __sz = graph_size - 1; __sz > 0; --__sz)
		{
			__term *= __sz;
			__res += __term;
		}
		__res += __term;
		return __res;
	}
public:
	tree(size_t size, const key_type& root_key) : __base(size, root_key) {  }
	template	<typename function_t, size_t size>
	tree(graph<float_type, key_type, size>& graph, const key_type& start, function_t function) : __base(__nodec_graph(graph.size()), start)
	{
		function(*this, graph, start);
	}
	
};

__end_ns_tsp
