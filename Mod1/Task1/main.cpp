#include <iostream>
using namespace std;

int getByte(int n, int k){
	return ((n & (1 << k)) >> k);
}

int main(){
	int n, k;
	cin >> n >> k;
	cout << getByte(n, k) << endl;
	return 0;
}