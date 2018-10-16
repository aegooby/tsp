
#pragma	once
#include	"__common.hpp"
#include	"__base.hpp"

__begin_ns_tsp

template	<typename float_type, typename key_type>
bool	operator ==(const node<float_type, key_type>& node_a, const node<float_type, key_type>& node_b)
{
	return (&node_a == &node_b);
}
template	<typename float_type, typename key_type>
bool	operator !=(const node<float_type, key_type>& node_a, const node<float_type, key_type>& node_b)
{
	return !(node_a == node_b);
}

template	<typename __float_type, typename __key_type>
class	node
{
	static_assert(std::is_arithmetic_v<__float_type>);
public:
	using float_type = __float_type;
	using key_type = __key_type;
	template	<typename float_type, typename key_type>
	friend class	__tree_private::__tree_base;
	template	<typename float_type, typename key_type>
	friend class	tree;
	template	<class ForwardIt, class UnaryPredicate>
	friend ForwardIt	std::remove_if(ForwardIt, ForwardIt, UnaryPredicate);
	template <class _InputIterator, class _OutputIterator>
	friend _OutputIterator	std::__move(_InputIterator, _InputIterator, _OutputIterator);
	template	<typename float_type, typename key_type>
	friend auto	operator <<(std::ostream& ostr, const node<float_type, key_type>& node) -> decltype((std::to_string(node.key()), ostr));
	template	<typename float_type, typename key_type>
	friend auto	operator <<(std::ostream& ostr, const node<float_type, key_type>& node) -> decltype((std::string(node.key()), ostr));
protected:
	using node_refw = std::reference_wrapper<node<float_type, key_type>>;
	node<float_type, key_type>&			__parent;
	std::unordered_map<key_type, node_refw>	__children;
	float_type								__weight = inf<float_type>;
	key_type								__key;
	__attribute__((always_inline))
	void	weight(float_type weight)
	{
		__weight = weight;
	}
	__attribute__((always_inline))
	void	add_child(node<float_type, key_type>& child, float_type weight)
	{
		for (auto& child_it : __children)
		{
			if (child.key() == child_it.second.get().key())
				throw std::invalid_argument("Child is already appended to this node");
		}
		child.weight(weight);
		__children.emplace(child.key(), child);
	}
	__attribute__((always_inline))
	void	remove_child(node<float_type, key_type>& child)
	{
		__children.erase(child.key());
	}
	inline __attribute__((always_inline))
	node<float_type, key_type>&	operator =(const node<float_type, key_type>& other)
	{
		__children = other.__children;
		__weight = other.__weight;
		__key = other.__key;
		
		return *this;
	}
	void	__lineage_recur(const node<float_type, key_type>& node, std::vector<key_type>& keys) const
	{
		if (node.root())
		{
			keys.emplace_back(node.key());
			return;
		}
		keys.emplace_back(node.key());
		__lineage_recur(node.parent(), keys);
	}
	void	__lineage_weight_recur(const node<float_type, key_type>& node, float_type& weight) const
	{
		if (node.root())
		{
			return;
		}
		weight += node.weight();
		__lineage_weight_recur(node.parent(), weight);
	}
public:
	node(const key_type& key) : __parent(*this), __key(key) {  }
	node(const key_type& key, node<float_type, key_type>& parent, float_type weight)
	: __parent(parent), __key(key) {  }
	~node() = default;
	inline __attribute__((always_inline))
	std::vector<key_type>	lineage() const
	{
		std::vector<key_type>	__keys;
		__lineage_recur(*this, __keys);
		return __keys;
	}
	inline __attribute__((always_inline))
	float_type	lineage_weight() const
	{
		float_type	__weight = float_type();
		__lineage_weight_recur(*this, __weight);
		return __weight;
	}
	inline __attribute__((always_inline))
	float_type	weight() const
	{
		return __weight;
	}
	inline __attribute__((always_inline))
	const key_type&	key() const
	{
		return __key;
	}
	inline __attribute__((always_inline))
	const node<float_type, key_type>&	parent() const
	{
		return __parent;
	}
	inline __attribute__((always_inline))
	const std::unordered_map<key_type, node<float_type, key_type>>	children() const
	{
		std::unordered_map<key_type, node<float_type, key_type>>	__copy;
		for (auto& child : __children)
		{
			__copy.emplace(child.second.get().key(), child.second.get());
		}
		return __copy;
	}
	inline __attribute__((always_inline))
	const node<float_type, key_type>&	child(const key_type& key) const
	{
		return __children.at(key);
	}
	inline __attribute__((always_inline))
	bool	root() const
	{
		return (__parent == *this);
	}
	inline __attribute__((always_inline))
	bool	leaf() const
	{
		return !bool(__children.size());
	}
};

template	<typename float_type, typename key_type>
auto	operator <<(std::ostream& ostr, const node<float_type, key_type>& node)
-> decltype((std::string(node.key()), ostr))
{
	std::string	str;
	str += "node(\"" + std::string(node.key()) + "\", parent: ";
	if (!node.root())
		str += "\"" + std::string(node.parent().key()) + "\", ";
	else
		str += "self, ";
	str += "children: ";
	if (!node.__children.size())
		str += "none, ";
	for (auto& child : node.__children)
	{
		str += "\"" + std::string(child.second.get().key()) + "\", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ")";
	ostr << str;
	return ostr;
}

template	<typename float_type, typename key_type>
auto	operator <<(std::ostream& ostr, const node<float_type, key_type>& node)
-> decltype((std::to_string(node.key()), ostr))
{
	std::string	str;
	str += "node(\"" + std::to_string(node.key()) + "\", parent: ";
	if (!node.root())
		str += "\"" + std::string(node.parent().key()) + "\", ";
	else
		str += "self, ";
	str += "children: ";
	if (!node.__children.size())
		str += "none, ";
	for (auto& child : node.__children)
	{
		str += "\"" + std::to_string(child.second.get().key()) + "\", ";
	}
	str = str.substr(0, str.length() - 2);
	str += ")";
	ostr << str;
	return ostr;
}

__end_ns_tsp
