#include "SetGraph.h"

SetGraph::SetGraph(int vertexNum){
	maps = std::vector<std::map<int,int>>(vertexNum);
};
SetGraph::SetGraph(const IGraph& graph){
	int size = graph.VerticesCount();
	maps = std::vector<std::map<int,int>>(size);

	for(int i = 0; i < size; ++i){
		for(int vertex : graph.GetNextVertices(i))
			AddEdge(i, vertex);
	}
};

SetGraph::~SetGraph(){};

SetGraph SetGraph::operator=(const IGraph& graph){
	int size = graph.VerticesCount();
	SetGraph sGraph(size);

	for(int i = 0; i < size; ++i)
		for(int vertex : graph.GetNextVertices(i))
			sGraph.AddEdge(i, vertex);

	return sGraph;
};

// Добавление ребра от from к to.
void SetGraph::AddEdge(int from, int to){
	if(maps.size() <= from || maps.size() <= to || from < 0 || to < 0) return;
	if(maps[from].contains(to)) return; 		//comment for multiple edges between vertices
	maps[from].insert(std::make_pair(to, 1));
};

int SetGraph::VerticesCount() const{
	return maps.size();
};

std::vector<int> SetGraph::GetNextVertices(int vertex) const{
	if(vertex < 0 || maps.size() <=vertex ) return std::vector<int>();
	
	std::vector<int> vertexes;
	for(std::pair<int,int> vertex : maps[vertex])
			vertexes.push_back(vertex.first);
	return vertexes;
};

std::vector<int> SetGraph::GetPrevVertices(int vertex) const{
	if(vertex < 0 || maps.size() <=vertex ) return std::vector<int>();
	
	std::vector<int> vertexes;
	for(int i = 0; i < maps.size(); ++i)
		if(maps[i].contains(vertex))
			vertexes.push_back(i);
	return vertexes;
};

void SetGraph::print(std::ostream& out) const{
	for(int i = 0; i < maps.size(); ++i){
		out << i << ")";
		for(std::pair<int,int> vertex : maps[i])
			out << " " << vertex.first;
		out << std::endl;
	}
};

