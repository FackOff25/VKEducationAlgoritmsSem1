#include <iostream>
#include <vector>
#include <queue>

class IntComparator{
	public:
		IntComparator(){};
		bool operator()(const int &first, const int &second){
			return first > second;
		};
};

template< typename T, class Comparator>
class BTree{
	private:

		class Node{
			public:
				bool isLeaf;
				std::vector<T> keys;
				std::vector<Node*> children;
				Node(bool _isLeaf): isLeaf(_isLeaf){}
				~Node(){
					for(Node* child: children){
						delete child;
					}
				}
				void print(std::ostream& out){
					for(T key: keys){
						out << key << " ";
					}
					out << "\n";
				}
		};

		Node* root;
		size_t t;
		Comparator cmp;
		bool isNodeFull(Node* node){
			return node->keys() == 2*t - 1;
		}
		void splitChild(Node* node, size_t index);
		void insertFull();
		void insertNonFull(Node* node, const T& key){
			int pos = node->keys.size() - 1;
			if( node->isLeaf ){
				node->keys.resize(node->keys.size() + 1);
				while(pos >= 0 && cmp(key, node->children[ pos + 1 ]) ){
					node->keys[pos + 1] = node.keys[pos];
					--pos;
				}
				node->keys[ pos + 1 ] = key;
			}else{
				while(pos >= 0 && node->children[ pos + 1 ] ){
					--pos;
				}
				if(isNodeFull(node->children[ pos + 1 ])){
					splitChild(node, pos + 1);
					if( cmp(key, node->children[ pos + 1 ])){
						++pos;
					}
				}

				insertNonFull(node->children[ pos + 1 ], key);
			}
		};
	public:
		BTree(size_t _t, Comparator _cmp = Comparator()): root(NULL), t(_t), cmp(_cmp){}
		~BTree(){
			if( root )
				delete root;
		};
		void insert(const T& key){
			if( !root )
				root = new Node(true);

			if(isNodeFull(root)){
				Node* newRoot = new Node(false);
				newRoot->children.push_back(root);
				root = newRoot;
				splitChild(root, 0);
			}
			insertNonFull(root, key);
		};
		void printByLayers(std::ostream& out){
			std::vector<Node*> layer, nextLayer;

			layer.push_back(root);
			while(!layer.empty()){
				for(Node* node: layer) {
					node->print(out);
					nextLayer.push_back(node->children);
				}
				layer = nextLayer;
				nextLayer = std::vector<Node*>();
			}
		};

};

int main(){
	int num;
	std::cin >> num;

	BTree<int, IntComparator> tree(num);

	while( std::cin >> num ) tree.insert(num);
	tree.printByLayers(std::cout);
}