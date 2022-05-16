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
		int shortestBranch() {
			return getDepth(root);
		};
		int getDepth(CNode<T>* node){
			if ( node == NULL ) return 0;
			int leftD = getDepth(node->left);
			int rightD = getDepth(node->right);
			if ( leftD == 0 && rightD != 0 ) return rightD+1;
			if ( leftD != 0 && rightD == 0 ) return leftD+1;
			return (leftD < rightD ? leftD+1 : rightD+1);
		}
};

template<typename T>
int shortestBranch(CNode<T>* node) {
		if ( node == NULL ) return 0;
		int leftD =shortestBranch(node->left);
		int rightD = shortestBranch(node->right);
		if ( leftD == 0 && rightD != 0 ) return rightD+1;
		if ( leftD != 0 && rightD == 0 ) return leftD+1;
		return (leftD < rightD ? leftD+1 : rightD+1);
		return shortestBranch(root);
};


int main(){
	BinTree<int> tree;
	int toInsert;

	char peeked;
	for( int i = 0; std::cin.peek() != '\n' && std::cin.peek() != EOF; ++i ) {
		std::cin >> toInsert;
		tree.insert(toInsert);
	}

	std::cout << shortestBranch<int>(tree.getRoot()) << std::endl;
}