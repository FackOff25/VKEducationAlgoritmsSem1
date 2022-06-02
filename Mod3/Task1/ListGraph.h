#ifndef LISTGRAPH
#define LISTGRAPH

#include "iGraph.h"

struct ListGraph : public IGraph {
	private:
		std::vector<std::vector<int>> lists;
		bool contains(std::vector<int> list, int vertex) const;
	public:
		ListGraph(int vertexNum = 0);
		ListGraph(const IGraph& graph);
		~ListGraph();
		ListGraph operator=(const IGraph& graph);
		
		// Добавление ребра от from к to.
		void AddEdge(int from, int to) override;

		int VerticesCount() const override;

		std::vector<int> GetNextVertices(int vertex) const override;
		std::vector<int> GetPrevVertices(int vertex) const override;
		void print(std::ostream& out) const override;
};

#endif