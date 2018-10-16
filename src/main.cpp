
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
		graph.add_edge("0", "1", 55);
		graph.add_edge("0", "2", 10);
		graph.add_edge("0", "3", 13);
		graph.add_edge("1", "2", 45);
		graph.add_edge("1", "3", 2);
		graph.add_edge("2", "3", 8);
		tsp::tree<float, std::string>	nn(graph, "0", tsp::nearest_neighbor<float, std::string>);
		for (auto& i : nn.nodes())
		{
			if (i.leaf())
			{
				std::cout << "(" << i.lineage_weight() << ")\t";
				for (auto& r : i.lineage())
					std::cout << r << " ";
				std::cout << std::endl;
			}
		}
		
		std::cout << std::endl;
		
		tsp::tree<float, std::string>	bf(graph, "0", tsp::brute_force<float, std::string>);
		for (auto& i : bf.nodes())
		{
			if (i.leaf())
			{
				std::cout << "(" << i.lineage_weight() << ")\t";
				for (auto& r : i.lineage())
					std::cout << r << " ";
				std::cout << std::endl;
			}
		}
		
		std::cout << std::endl;
		
		tsp::tree<float, std::string>	bnb(graph, "0", tsp::branch_and_bound<float, std::string>);
		for (auto& i : bnb.nodes())
		{
			if (i.leaf() && i.lineage().size() == graph.size())
			{
				std::cout << "(" << i.lineage_weight() << ")\t";
				for (auto& r : i.lineage())
					std::cout << r << " ";
				std::cout << std::endl;
			}
		}
	}
	catch(std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	
	return 0;
}
