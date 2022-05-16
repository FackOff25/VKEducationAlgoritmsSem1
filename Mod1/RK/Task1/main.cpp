#include <stdlib.h>
#include <iostream>

int search(int arr[], int len, int k){
	int top = len - 1;
	int bottom = 0;
	int idx = ( top + bottom ) / 2;

	if( k > arr[top] ) return len;
	if( k < arr[bottom] ) return 0;

	while( top - bottom > 1 ){
		if ( arr[idx] < k ){
			bottom = idx;
		}else{
			if(arr[idx] == k) return idx;
			top = idx; 
		}
		 idx = ( top + bottom ) / 2;
	}
	return top;
}

int main(){
	
	int len;
	int *arr;
	int k;

	std::cin >> len;
	arr = new int[len];
	for (int i = 0; i < len; ++i) std::cin >> arr[i];
	std::cin >> k;

	/*
	int len = 4;
	int arr[] = {1, 3, 5, 6};
	int k = 7;
	*/
	std::cout << search(arr, len, k) << std::endl;
	delete [] arr;
	return 0;
}