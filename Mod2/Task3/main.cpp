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
				Node(const Node& node): isLeaf(node.isLeaf), keys(node.keys){
					children = std::vector<Node*>(node.children.size(), NULL);
					for(int i = 0; i < node.children.size(); ++i)
						if(node.children[i])
							children[i] = new Node(*node.children[i]);
				}
				Node& operator=(const Node& node){
					isLeaf = node.isLeaf;
					keys = node.keys;
					children = std::vector<Node*>(node.children.size(), NULL);
					for(int i = 0; i < node.children.size(); ++i)
						if(node.children[i])
							children[i] = new Node(*node.children[i]);
					return *this;
				}
				~Node(){
					for(Node* child: children){
						delete child;
					}
				}
				void print(std::ostream& out){
					for(T key: keys){
						out << key << " ";
					}
				}
		};

		Node* root;
		size_t t;
		Comparator cmp;
		bool isNodeFull(Node* node){
			return node->keys.size() == 2*t - 1;
		}
		void splitChild(Node* node, size_t index){
			node->keys.resize(node->keys.size() + 1);
			node->children.push_back(NULL);

			Node* splitted = node->children[index];
			Node* newNode = new Node(splitted->isLeaf);

			for(int i = 0; i < t - 1; ++i)
				newNode->keys.push_back(splitted->keys[i + t]);
			
			if(!splitted->isLeaf){
				for(int i = 0; i < t; ++i)
					newNode->children.push_back(splitted->children[i + t]);
				splitted->children.resize(t);
			}

			if (node->keys.size() != 0)
				for(int i = node->keys.size() - 1; i > index; --i)
					node->keys[i] = node->keys[i - 1];
			else node->keys = std::vector<T>(1);

			node->keys[index] = splitted->keys[t - 1];

			for(int i = node->children.size() - 1; i > index + 1; --i)
				node->children[i] = node->children[i - 1];
			node->children[index + 1] = newNode;

			splitted->keys.resize(t - 1);
			
		};
		void insertNonFull(Node* node, const T& key){
			int pos = node->keys.size() - 1;

			if( node->isLeaf ){
				node->keys.resize(node->keys.size() + 1);
				while(pos >= 0 && cmp(key, node->keys[pos]) ){
					node->keys[pos + 1] = node->keys[pos];
					--pos;
				}
				if (pos < 0) node->keys[0] = key;
				else node->keys[ pos + ( cmp(key, node->keys[pos]) ? 0 : 1 ) ] = key;
			}else{
				while(pos >= 0 && cmp(key, node->keys[pos]) ){
					--pos;
				}
				if (pos < 0) pos = 0;

				if(isNodeFull(node->children[pos + ( cmp(key, node->keys[pos]) ? 0 : 1 )])){
					splitChild(node, ( pos = pos + ( cmp(key, node->keys[pos]) ? 0 : 1 ) ));
				}

				insertNonFull(node->children[pos + ( cmp(key, node->keys[pos]) ? 0 : 1 )], key);
			}
		};
	public:
		BTree(size_t _t, Comparator _cmp = Comparator()): root(NULL), t(_t), cmp(_cmp){}
		BTree(const BTree& tree){
			t = tree.t;
			cmp = tree.cmp;
			if(root)
				root = new Node(*tree.root);
		}
		BTree& operator=(const BTree& tree){
			t = tree.t;
			cmp = tree.cmp;
			if(root)
				root = new Node(*tree.root);
			return *this;
		}
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
				out << std::endl;
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
	
	BTree<int, IntComparator> tree2(tree);
}