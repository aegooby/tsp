
#pragma	once
#include	"__common.hpp"

__begin_ns_tsp

class	__edge_private
{
private:
	template	<typename float_type>
	class	__edge_base;
public:
	__edge_private() = delete;
	template	<typename float_type>
	friend class	edge;
	template	<typename float_type>
	friend class	vertex;
};

template	<typename float_type>
class	edge;

class	__vertex_private
{
private:
	template	<typename float_type>
	class	__vertex_base;
public:
	__vertex_private() = delete;
	template	<typename float_type>
	friend class	vertex;
};

template	<typename float_type>
class	vertex;

class	__graph_private
{
private:
	template	<typename float_type>
	class	__graph_base;
public:
	template	<typename float_type>
	friend class	graph;
};

template	<typename float_type>
class	graph;

__end_ns_tsp
