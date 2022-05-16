#include <stdlib.h>
#include <queue>
#include <iostream>

template <class T> class CNode{
	protected:
        T key;
    public:
		CNode* left;
		CNode* right;
        CNode(const T& _key){
			key = _key;
			left = right = NULL;
		};
        T get_key() { return key; };
};

template <class T>
class BinTree{
	private:
        CNode<T>* root;
    public:
        BinTree(){
			root = NULL;
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
				root = new CNode( newNodeKey );
				return;
			}

        	CNode<T>* ptr;
       		CNode<T>* ptr1;

       		ptr = ptr1 = root;
        	while( ptr != NULL ){
                ptr1 = ptr;
                if(newNodeKey < ptr->get_key() )	ptr = ptr->left;
                else ptr = ptr->right;
        	}

        	if ( newNodeKey < ptr1->get_key() )	ptr1->left = new CNode( newNodeKey );
			else ptr1->right = new CNode( newNodeKey );
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
        CNode<T>* getRoot() const { return root; };
		bool isAllEqual() {
			if( root == NULL ) { return false; }
			T rootKey = root->get_key();
			std::queue<CNode<T>*> queue;
			CNode<T>* node;
			
			queue.push( root );
			while( !queue.empty() ) {
				node = queue.front();
				queue.pop();
				if( rootKey != node->get_key()) return false;
				if( node->left != NULL)	queue.push( node->left );
				if( node->right != NULL) queue.push( node->right );
			}
			return true;
		};
};

template<typename T>
bool isAllEqual(const BinTree<T>& tree){
	CNode<T>* node = tree.getRoot();
	if( node == NULL ) { return false; }
			int rootKey = node->get_key();
			std::queue<CNode<T>*> queue;
			
			
			queue.push( node );
			while( !queue.empty() ) {
				node = queue.front();
				queue.pop();
				if( rootKey != node->get_key()) return false;
				if( node->left != NULL)	queue.push( node->left );
				if( node->right != NULL) queue.push( node->right );
			}
			return true;
}

int main(){
	BinTree<int> tree;
	int toInsert;

	char peeked;
	for( int i = 0; std::cin.peek() != '\n' && std::cin.peek() != EOF; ++i ) {
		std::cin >> toInsert;
		tree.insert(toInsert);
	}

	std::cout << isAllEqual<int>(tree) << std::endl;
}