#include "iGraph.h"

struct ArcGraph : public IGraph {
	ArcGraph();
	ArcGraph(const IGraph& graph);
	~ArcGraph();
	ArcGraph operator=(const IGraph& graph);
    
    // Добавление ребра от from к to.
	void AddEdge(int from, int to) = 0;

    int VerticesCount() const;

	std::vector<int> GetNextVertices(int vertex) const;
	std::vector<int> GetPrevVertices(int vertex) const;
};