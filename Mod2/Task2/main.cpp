#include <stdlib.h>
#include <queue>
#include <stack>
#include <iostream>

class IntComparator{
	public:
		IntComparator(){};
		bool operator()(const int &first, const int &second){
			return first > second;
		};
};

template <class T>
class CNode{
	protected:
        T key;
    public:
		CNode* left;
		CNode* right;
        CNode(const T& _key){
			key = _key;
			left = right = NULL;
		};
		CNode(const CNode& node){
			key = node.key;
			left = right = NULL;
		};
		CNode& operator=(const CNode& node){
			key = node.key;
			left = right = NULL;
			return *this;
		};
        T get_key() { return key; };
		void print(std::ostream& out){
			out << key;
		}
};

template <class T, class Comparator>
class BinTree{
	private:
        CNode<T>* root;
		Comparator cmp;
    public:
        BinTree(Comparator _cmp = Comparator()): root(NULL), cmp(_cmp){};
		BinTree(const BinTree& tree){
			cmp = tree.cmp;
			std::queue<CNode<T>*> queue;
			CNode<T>* node;
			queue.push( tree.root );
			while( !queue.empty() ) {
				node = queue.front();
				queue.pop();
				if( node->left != NULL)	queue.push( node->left );
				if( node->right != NULL) queue.push( node->right );
				insert(node->get_key());
			}
		};
		BinTree& operator=(const BinTree& tree){
			cmp = tree.cmp;
			std::queue<CNode<T>*> queue;
			CNode<T>* node;
			queue.push( tree.root );
			while( !queue.empty() ) {
				node = queue.front();
				queue.pop();
				if( node->left != NULL)	queue.push( node->left );
				if( node->right != NULL) queue.push( node->right );
				insert(node->get_key());
			}
			return *this;
		};
		~BinTree(){
			if( root == NULL ) return;
			std::queue<CNode<T>*> queue;
			CNode<T>* node;
			queue.push( root );
			while( !queue.empty() ) {
				node = queue.front();
				queue.pop();
				if( node->left != NULL)	queue.push( node->left );
				if( node->right != NULL) queue.push( node->right );
				delete node;
			}
		};
        void insert(const T& newNodeKey){
			if( root == NULL ) {
				root = new CNode<T>( newNodeKey );
				return;
			}

        	CNode<T>* ptr;
       		CNode<T>* ptr1;

       		ptr = ptr1 = root;
        	while( ptr != NULL ){
                ptr1 = ptr;
                if( cmp( newNodeKey, ptr->get_key() ) )	ptr = ptr->left;
                else ptr = ptr->right;
        	}

        	if ( cmp( newNodeKey, ptr1->get_key() ) )	ptr1->left = new CNode<T>( newNodeKey );
			else ptr1->right = new CNode<T>( newNodeKey );
		};                               
		CNode<T>* findMin() const {
			CNode<T>* node = root;
			if( node == NULL ) return node;
			while( node->left != NULL )	node = node->left;
			return node;
		};
		CNode<T>* findMax() const {
			CNode<T>* node = root;
			if( node == NULL ) return node;
			while( node->right != NULL ) node = node->right;
			return node;
		};
		void preOrder(std::ostream& out){
			if( !root ) return;

			CNode<T>* node = root;
			std::stack<CNode<T>*> nodes;

			nodes.push(node);
			while(!nodes.empty()){
				node = nodes.top();
				nodes.pop();
				
				node->print(out);
				out << " ";

				if( node->left ) nodes.push(node->left);
				if( node->right ) nodes.push(node->right);
			}
			out << "\n";
		}
};


int main(){
	IntComparator cmp;
	BinTree<int, IntComparator> tree(cmp);
	int number, toInsert;

	std::cin >> number;
	for( int i = 0; i < number; ++i ) {
		std::cin >> toInsert;
		tree.insert(toInsert);
	}

	tree.preOrder(std::cout);
}