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
	matrix[from][to] = 1;		//for multiple edges between vertices comment this line
	//++matrix[from][to];		//and uncoment this
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

void MatrixGraph::print(std::ostream& out) const{
	int size = matrix.size();

	out << "  ";
	for(int i = 0; i < size; ++i)
		out << " " << i;
	out << std::endl;

	out << "——";
	for(int i = 0; i < size; ++i)
		out << "——";

	out << std::endl;

	for(int i = 0; i < size; ++i){
		out << i << "|";
		for (int j = 0; j < size; ++j)
			out << " " << matrix[i][j];
		out << std::endl;
	}
};
