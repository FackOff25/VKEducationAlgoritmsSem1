#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

struct IGraph {
	virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
	virtual void AddEdge(int from, int to, int length) = 0;

    virtual int VerticesCount() const  = 0;

	virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
	virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph : public IGraph {
	private:
		std::vector<std::vector<std::pair<int, int>>> lists;
		bool contains(std::vector<std::pair<int, int>> list, std::pair<int, int> vertex) const{
			if(list.empty()) return false;
			if(std::find(list.begin(), list.end(), vertex) != list.end()) return true;
			else return false;
		};
	public:
		ListGraph(int vertexNum = 0){
			lists = std::vector<std::vector<std::pair<int, int>>>(vertexNum);
		};
		ListGraph(const IGraph& graph){
			lists = std::vector<std::vector<std::pair<int, int>>>(graph.VerticesCount());
			for(int i = 0; i < lists.size(); ++i)
				lists[i] = graph.GetNextVertices(i);
		};
		~ListGraph(){};
		ListGraph operator=(const IGraph& graph){
			ListGraph newGraph(graph.VerticesCount());
			newGraph.lists = std::vector<std::vector<std::pair<int, int>>>(graph.VerticesCount());
			for(int i = 0; i < lists.size(); ++i)
				newGraph.lists[i] = graph.GetNextVertices(i);
			return newGraph;
		};
		
		// Добавление ребра от from к to.
		void AddEdge(int from, int to, int length) override {
			if(lists.size() <= from || lists.size() <= to || from < 0 || to < 0) return;
			lists[from].push_back(std::make_pair(to, length));
			lists[to].push_back(std::make_pair(from, length));
		};

		int VerticesCount() const override {
			return lists.size();
		};

		std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override{
			if(vertex < 0 || lists.size() <=vertex ) return std::vector<std::pair<int, int>>();
			return lists[vertex];
		};
		
		std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override{
			if(vertex < 0 || lists.size() <=vertex ) return std::vector<std::pair<int, int>>();
			return lists[vertex];
		};
};

int ShortestWayCount(int start, int end, const IGraph& graph){
	int size = graph.VerticesCount();
	std::set<std::pair<int, int>> vertexQueue;
	std::vector<int> paths(size, INT32_MAX);
	paths[start] = 0;

	vertexQueue.insert(std::make_pair(0, start));
	std::pair<int, int> vertex;
	while(!vertexQueue.empty()){
		vertex = *vertexQueue.begin(); vertexQueue.erase(vertex);
		for(std::pair<int,int> vert : graph.GetNextVertices(vertex.second)){
			if(paths[vert.first] == INT32_MAX){
				paths[vert.first] = paths[vertex.second] + vert.second;
				vertexQueue.insert(std::make_pair(vert.second + paths[vertex.second], vert.first));
			}else if(paths[vertex.second] + vert.second < paths[vert.first]) {
				paths[vert.first] = paths[vertex.second] + vert.second;
				vertexQueue.erase(vert);
				vertexQueue.insert(std::make_pair(vert.second + paths[vertex.second], vert.first));
			}
		};
	}

	return paths[end];
};

int main(){
	int N, M, start, end, len;

	std::cin >> N >> M;
	ListGraph graph(N);
	for(int i = 0; i < M; ++i){
		std::cin >> start >> end >> len;
		graph.AddEdge(start, end, len);
	}
	std::cin >> start >> end;
	std::cout << ShortestWayCount(start, end, graph) << std::endl;
}