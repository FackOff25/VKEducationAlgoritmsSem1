#include <stdlib.h>
#include <iostream>

class IntComparator{
	public:
		IntComparator(){};
		bool operator()(const int &first, const int &second){
			return first < second;
		};
};

template <class T, class Comparator>
class AVLTree{
	private:
		class CNode{
			protected:
				T key;
				size_t height;
				size_t count;
			public:
				CNode* parent;
				CNode* left;
				CNode* right;
				CNode(const T& _key){
					key = _key;
					height = 1;
					count = 1;
					parent = left = right = NULL;
				};
				CNode(const CNode& node){
					key = node.key;
					height = node.height;
					count = node.count;

					parent = NULL;

					left = new CNode(*node.left);
					left.parent = this;
					right = new CNode(*node.right);
					right.parent = this;
				};
				CNode& operator=(const CNode& node){
					key = node.key;
					height = node.height;
					count = node.count;

					parent = NULL;

					left = new CNode(*node.left);
					left.parent = this;
					right = new CNode(*node.right);
					right.parent = this;
					return *this;
				};
				~CNode(){
					if (left) delete left;
					if (right) delete right;
				};
				T get_key() { return key; };
				size_t getHeight() { return height; };
				size_t getCount() { return count; };
				void fixHeight(){ 
					height = std::max(left ? left->height : 0, right ? right->height : 0) + 1; 
					count = (left ? left->count : 0) + (right ? right->count : 0) + 1;
				};
				void print(std::ostream& out){
					out << key;
				}
		};
		CNode* root;
		Comparator cmp;
		int getHeight(CNode* node){ return (node ? node->getHeight() : 0); };
		int getCount(CNode* node){ return (node ? node->getCount() : 0); };
		int getDif(CNode* node){ 
			return getHeight(node->left) 
				- getHeight(node->right);};
		CNode* littleRightRotate(CNode* node){
			CNode* oldLeft = node->left;

			node->left = oldLeft->right;
			if(oldLeft->right) oldLeft->right->parent = node;
			oldLeft->right = node;
			oldLeft->parent = node->parent;
			node->parent = oldLeft;

			node->fixHeight();
			oldLeft->fixHeight();

			return oldLeft;
		};
		CNode* littleLeftRotate(CNode* node){
			CNode* oldRight = node->right;

			node->right = oldRight->left;
			if(oldRight->left) oldRight->left->parent = node;
			oldRight->left = node;
			oldRight->parent = node->parent;
			node->parent = oldRight;

			node->fixHeight();
			oldRight->fixHeight();

			return oldRight;
		};
		CNode* bigRightRotate(CNode* node){
			node->left = littleLeftRotate(node->left);
			return littleRightRotate(node);
		};
		CNode* bigLeftRotate(CNode* node){
			node->right = littleRightRotate(node->right);
			return littleLeftRotate(node);
		};
		CNode* balance(CNode* node){
			node->fixHeight();
			switch (getDif(node)){
				case 2:
					node = (getDif(node->left) < 0) ? bigRightRotate(node) : littleRightRotate(node);
					break;
				case -2:
					node = (getDif(node->right) < 0) ? littleLeftRotate(node) : bigLeftRotate(node);
					break;
				default:
					break;
			}
			return node;
		};
		CNode* insertInternal(CNode* node, const T& newNodeKey){
			if( !node ) 
				return new CNode( newNodeKey );
			
			if( cmp( newNodeKey, node->get_key() )){
				node->left = insertInternal(node->left, newNodeKey);
				if(node->left) node->left->parent = node;
			}else{
				node->right = insertInternal(node->right, newNodeKey);
				if(node->right) node->right->parent = node;
			}

			return balance(node);
		};
		CNode* deleteInternal(CNode* node, const T& newNodeKey){
			if( !node ) 
				return NULL;
			
			if( cmp( newNodeKey, node->get_key() )){
				node->left = deleteInternal(node->left, newNodeKey);
				if(node->left) node->left->parent = node;
			}else
				if ( cmp( node->get_key(), newNodeKey ) ){
					node->right = deleteInternal(node->right, newNodeKey);
					if(node->right) node->right->parent = node;
				}else{
					CNode* left = node->left;
					CNode* right = node->right;

					node->left = NULL;
					node->right = NULL;
					delete node;

					if(!right && !left) return NULL;
					if(!left) return right;
					if(!right) return left;

					CNode* changed;
					if(getHeight(left) < getHeight(right)){
						changed = findAndRemoveMin(right);
						changed->left = left;
						if(changed->left) changed->left->parent = changed;	
					}else{
						changed = findAndRemoveMax(left);
						changed->right = right;
						if(changed->right) changed->right->parent = changed;	
					}
					
					
					return balance(changed);
				}

			return balance(node);
		};
		CNode* findMin(CNode* node){
			while(node->left) node = node->left;
			return node;
		};
		CNode* removeMin(CNode* node){
			if(!node->left) return node->right;
			node->left = removeMin(node->left);
			return balance(node);
		};
		CNode* findAndRemoveMin(CNode* node){
			CNode* min = findMin(node);
			min->right = removeMin(node);
			return min;
		}
		CNode* findMax(CNode* node){
			while(node->right) node = node->right;
			return node;
		};
		CNode* removeMax(CNode* node){
			if(!node->right) return node->left;
			node->right = removeMax(node->right);
			return balance(node);
		};
		CNode* findAndRemoveMax(CNode* node){
			CNode* max = findMax(node);
			max->left = removeMax(node);
			return max;
		}
		CNode* getNStatisticsInternal(CNode* node, const size_t& stat){
			if(getCount(node->left) == stat) return node;

			if(getCount(node->left) > stat) return getNStatisticsInternal(node->left, stat);
			else return getNStatisticsInternal(node->right, stat - getCount(node->left) - 1);
		};
	public:
        AVLTree(Comparator _cmp = Comparator()): root(NULL), cmp(_cmp){};
		AVLTree(const AVLTree& tree){
			cmp = tree.cmp;
			root = new CNode(*tree.root);
		};
		AVLTree& operator=(const AVLTree& tree){
			cmp = tree.cmp;
			root = new CNode(*tree.root);
		};
		~AVLTree(){
			if( root == NULL ) return;
			delete root;
		};
		void insertKey(const T& newNodeKey){
			root = insertInternal(root, newNodeKey);
		};        
		void deleteKey(const T& newNodeKey){
			root = deleteInternal(root, newNodeKey);
			if(root) root->parent = NULL;
		};
		T getNStatistics(const size_t& stat){
			if(!root) return T();
			if(stat > root->getCount()) return T();
					
			return getNStatisticsInternal(root, stat)->get_key();
		};            
};

int main(){
	IntComparator cmp;
	AVLTree<int, IntComparator> tree(cmp);
	int number, toInsert, statistic;

	std::cin >> number;
	for( int i = 0; i < number; ++i ) {
		std::cin >> toInsert;
		std::cin >> statistic;

		if(toInsert < 0){
			toInsert *= -1;
			tree.deleteKey(toInsert);
		}else tree.insertKey(toInsert);
		
	std::cout << tree.getNStatistics(statistic) << std::endl;
	}
	return 0;
}