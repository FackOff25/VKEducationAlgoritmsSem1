#include <iostream>
#include <vector>
#include <queue>

class IntComparator{
	public:
		IntComparator(){};
		bool operator()(const int &first, const int &second){
			return first < second;
		};
};

template<typename T, class Comparator>
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
			return node->keys.size() == 2*t - 1;
		}
		void splitChild(Node* node, size_t index){
			Node* splitted = node->children[index];
			Node* newNode = new Node(splitted->isLeaf);

			for(int i = 0; i < t - 1; ++i)
				newNode->keys.push_back(splitted->keys[i + t]);
			
			if(!splitted->isLeaf){
				for(int i = 0; i < splitted->children.size() - 1; ++i)
					newNode->children.push_back(splitted->children[i + t + 1]);
			}

			if (node->keys.size() != 0)
				for(int i = node->keys.size() - 1; i > index; --i)
					node->keys[i] = node->keys[i - 1];
			else node->keys = std::vector<T>(1);

			node->keys[index] = splitted->keys[t - 1];

			for(int i = node->children.size() - 1; i > index + 1; --i)
				node->children[i] = node->children[i - 1];
			node->children[index] = newNode;

			splitted->keys.resize(t - 1);
		};
		//void insertFull();
		void insertNonFull(Node* node, const T& key){
			int pos = node->keys.size() - 1;

			if( node->isLeaf ){
				node->keys.resize(node->keys.size() + 1);
				while(pos >= 0 && cmp(key, node->keys[ pos + 1 ]) ){
					node->keys[pos + 1] = node->keys[pos];
					--pos;
				}
				node->keys[ pos + 1 ] = key;
			}else{
				while(pos >= 0 && cmp(key, node->keys[ pos + 1 ]) ){
					--pos;
				}
				if(isNodeFull(node->children[ pos + 1 ])){
					splitChild(node, pos + 1);
					if( cmp(key, node->keys[ pos + 1 ])){
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
					for(Node* child: node->children)
						nextLayer.push_back(child);
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

	while( std::cin >> num ) 
		tree.insert(num);
	tree.printByLayers(std::cout);
}