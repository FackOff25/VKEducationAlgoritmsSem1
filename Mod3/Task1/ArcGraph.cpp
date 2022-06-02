#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertexNum){};

ArcGraph::ArcGraph(const IGraph& graph){
	int size = graph.VerticesCount();
	std::vector<int> vertices;
	for(int i = 0; i < size; ++i){
		vertices = graph.GetNextVertices(i);
		for(int vertex : vertices)
			AddEdge(i, vertex);
	}
};

ArcGraph::~ArcGraph(){};

ArcGraph ArcGraph::operator=(const IGraph& graph){
	int size = graph.VerticesCount();
	ArcGraph aGraph(size);
	std::vector<int> vertices;
	for(int i = 0; i < size; ++i){
		vertices = graph.GetNextVertices(i);
		for(int vertex : vertices)
			aGraph.AddEdge(i, vertex);
	}
	return aGraph;
};
		
// Добавление ребра от from к to.
void ArcGraph::AddEdge(int from, int to){
	std::pair<int, int> newEdge = std::make_pair(from, to);
	if(contains(edges, newEdge)) return;
	edges.push_back(newEdge);
};

int ArcGraph::VerticesCount() const{
	std::vector<int> vertices;
	for(std::pair<int, int> edge : edges){
		if(contains(vertices, edge.first))	vertices.push_back(edge.first);
		if(contains(vertices, edge.second))	vertices.push_back(edge.second);
	}
	return vertices.size();
};

bool ArcGraph::contains(std::vector<std::pair<int, int>> list, std::pair<int, int> edge) const{
	if(list.empty()) return false;
	if(std::find(list.begin(), list.end(), edge) != list.end()) return true;
	else return false;
};

bool ArcGraph::contains(std::vector<int> list, int vertex) const{
	if(list.empty()) return false;
	if(std::find(list.begin(), list.end(), vertex) != list.end()) return true;
	else return false;
};


std::vector<int> ArcGraph::GetNextVertices(int vertex) const{
	std::vector<int> vertices;
	for(std::pair<int, int> edge : edges)
		if(edge.first == vertex)
			vertices.push_back(edge.second);
	return vertices;
};

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const{
	std::vector<int> vertices;
	for(std::pair<int, int> edge : edges)
		if(edge.second == vertex)
			vertices.push_back(edge.first);
	return vertices;
};

void ArcGraph::print(std::ostream& out) const{
	for(std::pair<int, int> edge : edges)
		out << " (" << edge.first << "," << edge.second << ")";
	out << std::endl;
};