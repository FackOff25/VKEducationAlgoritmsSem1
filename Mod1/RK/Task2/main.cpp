#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class CharStack{
	private:
		
	public:
	string str;
		CharStack(){
			str = "";
		}
		void add(char ch){
			str += ch;
		};
		char extractLast(){
			char c = str[str.size() - 1];
			str.resize(str.size() - 1);
			return c;
		};
		char getLast(){
			if (str.size() == 0 ) return '\0';
			return str[str.size() - 1];
		};
		bool isEmpty(){ return str.size() == 0; }
};

int main(){
	/*
	string first = "ABC";
	string second = "CAB";
	int len = first.size();
	*/
	if ( len != second.size() ) cout << "NO" << endl;

	CharStack stack;
	int i;
	int j = 0;

	for(i = 0; i < len; ++i){
		stack.add(first[i]);
		while( stack.getLast() == second[j] && j < len ){
			++j;
			stack.extractLast();
		}
	}
	if ( i != j) cout << "NO" << endl;
	else cout << "YES" << endl;
  return 0;
}