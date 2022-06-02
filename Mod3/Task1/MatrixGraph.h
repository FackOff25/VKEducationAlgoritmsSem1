#ifndef MATRIXGRAPH
#define MATRIXGRAPH

#include "iGraph.h"

struct MatrixGraph : public IGraph {
	private:
		std::vector<std::vector<int>> matrix;
	public:
		MatrixGraph(int vertexNum = 0);
		MatrixGraph(const IGraph& graph);
		~MatrixGraph();
		MatrixGraph operator=(const IGraph& graph);

		// Добавление ребра от from к to.
		void AddEdge(int from, int to) override;

		int VerticesCount() const override;

		std::vector<int> GetNextVertices(int vertex) const override;
		std::vector<int> GetPrevVertices(int vertex) const override;
		void print(std::ostream& out) const override;
};

#endif