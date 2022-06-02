#ifndef SETGRAPH
#define SETGRAPH

#include "iGraph.h"
#include <map>

struct SetGraph : public IGraph {
	private:
		std::vector<std::map<int,int>> maps;
	public:
		SetGraph(int vertexNum = 0);
		SetGraph(const IGraph& graph);
		~SetGraph();
		SetGraph operator=(const IGraph& graph);

		// Добавление ребра от from к to.
		void AddEdge(int from, int to) override;

		int VerticesCount() const override;

		std::vector<int> GetNextVertices(int vertex) const override;
		std::vector<int> GetPrevVertices(int vertex) const override;
		void print(std::ostream& out) const override;
};

#endif