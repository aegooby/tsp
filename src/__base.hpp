
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
	template	<typename float_type, typename key_type>
	class	__graph_base;
public:
	template	<typename float_type, typename key_type>
	friend class	graph;
	template	<typename float_type, typename key_type>
	friend class	digraph;
};

template	<typename float_type, typename key_type>
class	graph;
template	<typename float_type, typename key_type>
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
class node;

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

__end_ns_tsp
