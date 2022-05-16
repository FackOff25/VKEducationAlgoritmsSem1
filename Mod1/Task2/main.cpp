#include <iostream>
using namespace std;

int findClosest(int arr[], int len, int num){
	int idx;
	int lowEdge = 0;
	int topEdge = len - 1;

	for( idx = 1; (idx < len/2) && (arr[idx] < num); idx = idx * 2) lowEdge = idx;

	if(idx > len - 1) idx = len - 1;

	arr[idx] < num ? lowEdge = idx :  topEdge = idx;

	while (topEdge - lowEdge > 1){
		arr[(topEdge + lowEdge)/2] > num ? topEdge = (topEdge + lowEdge)/2 : lowEdge = (topEdge + lowEdge)/2;
	}
	
	return ( arr[topEdge] - num < num - arr[lowEdge] ? topEdge : lowEdge );
}

void fillIntArray(int arr[], int len){
	for(int i = 0; i < len; ++i){
		cin >> arr[i];
	}
}

int main(){
	int n;
	int *A;

	cin >> n;
	A = new int[n];
	fillIntArray(A, n);

	int m;
	int *B;

	cin >> m;
	B = new int[m];
	fillIntArray(B, m);

	for (int i = 0; i < m; ++i) cout << findClosest(A, n, B[i]) << " ";

	cout << endl;

	return 0;
}