#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexNum){
	matrix = std::vector(vertexNum, std::vector(vertexNum, 0));
};

MatrixGraph::MatrixGraph(const IGraph& graph){
	int vertexNum = graph.VerticesCount();
	matrix = std::vector(vertexNum, std::vector(vertexNum, 0));
	std::vector<int> vertices;
	for(int i = 0; i < vertexNum; ++i){
		vertices = graph.GetNextVertices(i);
		for(int vertex : vertices)
			matrix[i][vertex] = 1;
	}
};

MatrixGraph::~MatrixGraph(){};

MatrixGraph MatrixGraph::operator=(const IGraph& graph){
	int vertexNum = graph.VerticesCount();
	MatrixGraph mGraph(vertexNum);
	std::vector<int> vertices;
	for(int i = 0; i < vertexNum; ++i){
		vertices = graph.GetNextVertices(i);
		for(int vertex : vertices)
			mGraph.matrix[i][vertex] = 1;
	}
	return mGraph;
};

// Добавление ребра от from к to.
void MatrixGraph::AddEdge(int from, int to){
	if(matrix.size() <= from || matrix.size() <= to || from < 0 || to < 0) return;
	matrix[from][to] = 1;
};

int MatrixGraph::VerticesCount() const{
	return matrix.size();
};

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const{
	std::vector<int> vertices;
	for(int i = 0; i < matrix.size(); ++i)
		if(matrix[vertex][i] == 1) vertices.push_back(i);
	return vertices;
};
std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const{
	std::vector<int> vertices;
	for(int i = 0; i < matrix.size(); ++i)
		if(matrix[i][vertex] == 1) vertices.push_back(i);
	return vertices;
};