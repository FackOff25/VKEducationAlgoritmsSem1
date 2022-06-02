#include <algorithm>

#include "ListGraph.h"

ListGraph::ListGraph(int vertexNum){
	lists = std::vector<std::vector<int>>(vertexNum);
};

ListGraph::ListGraph(const IGraph& graph){
	lists = std::vector<std::vector<int>>(graph.VerticesCount());
	for(int i = 0; i < lists.size(); ++i)
		lists[i] = graph.GetNextVertices(i);
};

ListGraph::~ListGraph(){};

ListGraph ListGraph::operator=(const IGraph& graph){
	ListGraph newGraph(graph.VerticesCount());
	newGraph.lists = std::vector<std::vector<int>>(graph.VerticesCount());
	for(int i = 0; i < lists.size(); ++i)
		newGraph.lists[i] = graph.GetNextVertices(i);
	return newGraph;
};
		
// Добавление ребра от from к to.
void ListGraph::AddEdge(int from, int to){
	if(lists.size() <= from || lists.size() <= to || from < 0 || to < 0) return;
	if(contains(lists[from], to)) return;
	lists[from].push_back(to);
};

int ListGraph::VerticesCount() const{
	return lists.size();
};

std::vector<int> ListGraph::GetNextVertices(int vertex) const{
	if(vertex < 0 || lists.size() <=vertex ) return std::vector<int>();
	return lists[vertex];
};

bool ListGraph::contains(std::vector<int> list, int vertex) const{
	if(list.empty()) return false;
	if(std::find(list.begin(), list.end(), vertex) != list.end()) return true;
	else return false;
};

std::vector<int> ListGraph::GetPrevVertices(int vertex) const{
	if(vertex < 0 || lists.size() <=vertex ) return std::vector<int>();
	
	std::vector<int> vertexes;
	for(int i = 0; i < lists.size(); ++i)
		if(contains(lists[i], vertex))
			vertexes.push_back(i);
	return vertexes;
};

void ListGraph::print(std::ostream& out) const{
	for(int i = 0; i < lists.size(); ++i){
		out << i << ")";
		for(int vertex : lists[i])
			out << " " << vertex;
		out << std::endl;
	}
};
