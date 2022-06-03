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
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
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

		std::vector<int> GetPrevVertices(int vertex) const override{
			if(vertex < 0 || lists.size() <=vertex ) return std::vector<int>();
			return lists[vertex];
		};

};

int ShortestWaysCount(int start, int end, const IGraph& graph){
	int size = graph.VerticesCount();
	std::queue<int> vertexQueue;
	std::vector<int> paths(size, size);
	std::vector<int> k(size, 0);
	paths[start] = 0;
	k[start] = 1;
	
	vertexQueue.push(start);
	int vertex, count = 0;
	while(!vertexQueue.empty()){
		vertex = vertexQueue.front(); vertexQueue.pop();
		for(int vert : graph.GetNextVertices(vertex)){
			if(paths[vertex] + 1 < paths[vert]) {
				paths[vert] = paths[vertex] + 1;
				k[vert] = k[vertex];
				vertexQueue.push(vert);
			}else if(paths[vertex] + 1 == paths[vert]) k[vert] += k[vertex];
		};
	}

	return k[end];
};

int main(){
	int v, n, u, w;

	std::cin >> v >> n;
	ListGraph graph(v);
	for(int i = 0; i < n; ++i){
		std::cin >> u >> w;
		graph.AddEdge(u, w);
	}
	std::cin >> u >> w;
	std::cout << ShortestWaysCount(u, w, graph) << std::endl;
}