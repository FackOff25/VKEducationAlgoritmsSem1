#include <stdlib.h>
#include <iostream>

class IntComparator{
	public:
		IntComparator(){};
		bool operator()(const int &first, const int &second){
			return first > second;
		};
};

template<typename T, typename Comparator>
int partition(T arr[], int len, Comparator cmp){
	if ( len == 1 ) return 0;

	int i, j;
	i = j = 0;


	while( j < len - 1){
		if(! ( arr[j] > arr[len - 1] )) {
			std::swap(arr[j], arr[i]);
			++i;
		}
		++j;
	}

	std::swap(arr[len - 1], arr[i]);
	return i;											//returns index of base element
}

template<typename T, typename Comparator>
int findThreeNedian(T arr[], int len, Comparator cmp){
	T first, mid, last;
	first = arr[0];
	mid = arr[len / 2];
	last = arr[len - 1];

	if ( cmp(first, mid) ){
		if (cmp(first, last)){
			if (cmp(mid, last)) return len / 2;
			else return len - 1;
		}else{
			return 0;
		}
	}else{
		if (cmp(mid, last)){
			if ( cmp(first, last) ) return 0;
			else return len - 1;
		}else{
			return len / 2;
		}
	}
}

template<typename T, typename Comparator = std::less<T>>
T findKStat(T arr[], int len, int k, Comparator cmp = Comparator()){

	int stat = 0;
	while ( true ){
		std::swap(arr[len - 1], arr[findThreeNedian(arr, len, cmp)]);
		stat = partition(arr, len, cmp);

		if ( stat + 1 > k ){
			len = stat;
		}else{
			if ( stat + 1 < k){
				len -= stat + 1;
				arr += stat + 1;
				k -= stat + 1;
			}else return arr[stat];
		}
	}
}

int main(){
	
	int len;
	std::cin >> len;

	int *arr = new int[len];
	for (int i = 0; i < len; ++i) std::cin >> arr[i];
	
	/*
	int len = 10;
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	*/

	int tenPerc = 0.1 * len + 1;
	int median = len / 2 + 1;
	int ninePerc = 0.9 * len + 1;
	

	std::cout << findKStat(arr, len, tenPerc, IntComparator()) << std::endl;
	std::cout << findKStat(arr, len, median, IntComparator()) << std::endl;
	std::cout << findKStat(arr, len, ninePerc, IntComparator()) << std::endl;

	delete [] arr;
	return 0;
}