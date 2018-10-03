
#include	"__common.hpp"
#include	"graph.hpp"
#include	"tsp_brute.hpp"
#include	"hash.hpp"
#include	"tree.hpp"

int	main(int argc, char** argv)
{
	try
	{
		tsp::graph<float, std::string>	graph(12);
		graph.add_vertex("0");
		graph.add_vertex("1");
		graph.add_vertex("2");
		graph.add_vertex("3");
		graph.add_edge("0", "1", 1);
		graph.add_edge("0", "2", 2);
		graph.add_edge("0", "3", 3);
		graph.add_edge("1", "2", 4);
		graph.add_edge("1", "3", 5);
		graph.add_edge("2", "3", 6);
		tsp::tree<float, std::string>	tree(graph, "0", tsp::brute_force());
		for (auto& i : tree.node(2).lineage())
			std::cout << i << std::endl;
	}
	catch(std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	
	return 0;
}
