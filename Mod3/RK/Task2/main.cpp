#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

struct IGraph {
	virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

struct ListGraph : public IGraph {
	private:
		std::vector<std::vector<int>> lists;
		bool contains(std::vector<int> list, int vertex) const{
			if(list.empty()) return false;
			if(std::find(list.begin(), list.end(), vertex) != list.end()) return true;
			else return false;
		};
	public:
		ListGraph(int vertexNum = 0){
			lists = std::vector<std::vector<int>>(vertexNum);
		};
		ListGraph(const IGraph& graph){
			lists = std::vector<std::vector<int>>(graph.VerticesCount());
			for(int i = 0; i < lists.size(); ++i)
				lists[i] = graph.GetNextVertices(i);
		};
		~ListGraph(){};
		ListGraph operator=(const IGraph& graph){
			ListGraph newGraph(graph.VerticesCount());
			newGraph.lists = std::vector<std::vector<int>>(graph.VerticesCount());
			for(int i = 0; i < lists.size(); ++i)
				newGraph.lists[i] = graph.GetNextVertices(i);
			return newGraph;
		};
		
		// Добавление ребра от from к to.
		void AddEdge(int from, int to) override {
			if(lists.size() <= from || lists.size() <= to || from < 0 || to < 0) return;
			lists[from].push_back(to);
			lists[to].push_back(from);
		};


		int VerticesCount() const override {
			return lists.size();
		};

		std::vector<int> GetNextVertices(int vertex) const override{
			if(vertex < 0 || lists.size() <=vertex ) return std::vector<int>();
			return lists[vertex];
		};

};


//necessary and sufficient condition for Euler graph is all vertecies have even 

bool isEuler(const IGraph& graph){
	int size = graph.VerticesCount();
	bool isThereCycle = false;
	std::queue<int> vertexQueue;
	std::vector<int> parents(size, -1), next;
	std::vector<bool> visited(size, false);
	
	vertexQueue.push(0);
	parents[0] = 0;
	int vertex, count = 0;
	while(!vertexQueue.empty()){
		vertex = vertexQueue.front(); vertexQueue.pop();
		visited[vertex] = true;
		next = graph.GetNextVertices(vertex);
		if (next.size() % 2 != 0) return false;					//if vertex's degree is odd the graph isn't Euler one
		for(int vert : next){
			if(!visited[vert]) {
				vertexQueue.push(vert);
				parents[vert] = vertex;
			}
		};
	}

	for(bool visit : visited)
		if(!visit) return false;

	return true;
};

int main(){
	int N, M, from, to;

	std::cin >> N >> M;
	ListGraph graph(N);
	for(int i = 0; i < M; ++i){
		std::cin >> from >> to;
		graph.AddEdge(from, to);
	}
	std::cout << (isEuler(graph)? 1 : 0) << std::endl;
}