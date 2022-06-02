#include "iGraph.h"

struct ListGraph : public IGraph {
	ListGraph();
	ListGraph(const IGraph& graph);
	~ListGraph();
	ListGraph operator=(const IGraph& graph);
    
    // Добавление ребра от from к to.
	void AddEdge(int from, int to) = 0;

    int VerticesCount() const;

	std::vector<int> GetNextVertices(int vertex) const;
	std::vector<int> GetPrevVertices(int vertex) const;
};