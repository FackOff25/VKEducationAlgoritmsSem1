#include "iGraph.h"

struct SetGraph : public IGraph {
	SetGraph();
	SetGraph(const IGraph& graph);
	~SetGraph();
    SetGraph operator=(const IGraph& graph);

    // Добавление ребра от from к to.
	void AddEdge(int from, int to) = 0;

    int VerticesCount() const;

	std::vector<int> GetNextVertices(int vertex) const;
	std::vector<int> GetPrevVertices(int vertex) const;
};