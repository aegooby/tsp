
#pragma	once
#include	"__common.hpp"

__begin_ns_tsp

class	__edge_private
{
private:
	template	<typename float_type, typename key_type>
	class	__edge_base;
public:
	__edge_private() = delete;
	template	<typename float_type, typename key_type>
	friend class	edge;
	template	<typename float_type, typename key_type>
	friend class	vertex;
};

template	<typename float_type, typename key_type>
class	edge;

class	__vertex_private
{
private:
	template	<typename float_type, typename key_type>
	class	__vertex_base;
public:
	__vertex_private() = delete;
	template	<typename float_type, typename key_type>
	friend class	vertex;
};

template	<typename float_type, typename key_type>
class	vertex;

class	__graph_private
{
private:
	template	<class derived, typename float_type, typename key_type, size_t size>
	class	__graph_base;
public:
	template	<typename float_type, typename key_type, size_t size>
	friend class	graph;
	template	<typename float_type, typename key_type, size_t size>
	friend class	digraph;
};

template	<typename float_type, typename key_type, size_t size>
class	graph;
template	<typename float_type, typename key_type, size_t size>
class	digraph;

class	__node_private
{
private:
	class	__node_base;
public:
	__node_private() = delete;
	template	<typename float_type, typename key_type>
	friend class	node;
};

template	<typename float_type, typename key_type>
class	node;

class	__tree_private
{
private:
	template	<typename float_type, typename key_type>
	class	__tree_base;
public:
	__tree_private() = delete;
	template	<typename float_type, typename key_type>
	friend class	tree;
};

template	<typename float_type, typename key_type>
class	tree;

template	<typename value_type, size_t size>
class	array;
template	<typename value_type, size_t size>
class	st_array;
template	<typename value_type, size_t rows, size_t cols>
class	table;
template	<typename value_type, size_t rows, size_t cols>
class	st_table;

__end_ns_tsp
