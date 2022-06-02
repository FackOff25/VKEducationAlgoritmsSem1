#ifndef ARCGRAPH
#define ARCGRAPH

#include <utility>
#include "iGraph.h"

struct ArcGraph : public IGraph {
	private:
		std::vector<std::pair<int, int>> edges;
		bool contains(std::vector<std::pair<int, int>> list, std::pair<int, int> edge) const;
		bool contains(std::vector<int> list, int vertex) const;
	public:
		ArcGraph(int vertexNum = 0);
		ArcGraph(const IGraph& graph);
		~ArcGraph();
		ArcGraph operator=(const IGraph& graph) ;
		
		// Добавление ребра от from к to.
		void AddEdge(int from, int to)  override;

		int VerticesCount() const  override;

		std::vector<int> GetNextVertices(int vertex) const  override;
		std::vector<int> GetPrevVertices(int vertex) const  override;
		void print(std::ostream& out) const override;
};

#endif