#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <ostream>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

class Period{
	private:
		int start;
		int end;
	public:
		Period(): start(0), end(0){}
		Period(const Period& per): start(per.start), end(per.end){}
		Period(int _start, int _end): start(_start), end(_end){}
		~Period(){};
		Period& operator=(const Period& per){
			start = per.start;
			end = per.end;
			return *this;
		}
		int getStart() const { return start; };
		int getEnd() const { return end; };
		bool doesContain(int time) const { return ( ! ( ( start > time ) || ( end < time ) ) );}
		friend std::ostream& operator<<(std::ostream& out, const Period& per){
			out << per.start << " " << per.end;
			return out;
		}
};

//find first element contains the time in sorted Period array
int findFirstContained(Period arr[], int len, int time){
	if ( arr[0].doesContain(time) ) return 0;

	int top = len - 1;
	int bottom = 0;
	int elem = ( top + bottom ) / 2;

	while ( ! ( arr[elem].doesContain(time) && ( ! arr[elem - 1].doesContain(time) ) ) ){
		if( arr[elem].getEnd() < time ) bottom = elem; 
		else top = elem;
		elem = ( top + bottom + 1 ) / 2;
	}
	return elem;
}

//runs over array and increase watch counters to clients who watched it
void show(Period arr[], int countArr[], int len, int time){
	for( int i = findFirstContained(arr, len, time); i < len && ( ! ( arr[i].getStart() > time ) ); ++i ){
		if ( arr[i].doesContain(time) ) ++(countArr[i]);
	}
}

template<typename T>
class iComparator{
	public:
		virtual bool operator()(const T &first, const T &second){
			return false;
		};
};

class minIntComparator: public iComparator<int>{
	public:
		minIntComparator(){};
		bool operator()(const int &first, const int &second){
			return first < second;
		};
};

class PeriodComparator: public iComparator<Period>{
	public:
		PeriodComparator(){};
		bool operator()(const Period &first, const Period &second){
			if ( first.getEnd() < second.getEnd() ) return true;
			if ( first.getEnd() > second.getEnd() ) return false;
			return first.getStart() > second.getStart();
		};
};

bool compareInts(const int &first, const int &second){
			return first < second;
};

bool comparePeriods(const Period &first, const Period &second){
			if ( first.getEnd() < second.getEnd() ) return true;
			if ( first.getEnd() > second.getEnd() ) return false;
			return first.getStart() > second.getStart();
};

template <typename T>
void merge(T merged[], T firstToMerge[], int firstLen, T secondToMerge[], int secondLen, bool (*cmp)(const T &first, const T &second)){

	T* firstArr = new T[firstLen];
	T* secondArr = new T[secondLen];
	memcpy(firstArr, firstToMerge, sizeof(T)*firstLen);
	memcpy(secondArr, secondToMerge, sizeof(T)*secondLen);

	int i, j;
	i = j = 0;
	while (i < firstLen && j < secondLen){
		if ( cmp( firstArr[i], secondArr[j] ) ) {
			merged[i + j] = firstArr[i];
			++i;
		}else{
			merged[i + j] = secondArr[j];
			++j;
		}
	}
	T* last;
	int left;
	if (i < firstLen) {
		last = &firstArr[i];
		left = firstLen - i;
	}else{
		last = &secondArr[j];
		left = secondLen - j;
	}

	for (int k = 0; k < left; ++k, ++last) merged[i + j + k] = *last;

	delete [] firstArr;
	delete [] secondArr;
}

template <typename T>
void mergeSort(T array[], int len,  bool (*cmp)(const T &first, const T &second)){
	for (int twoDeg = 1; twoDeg <= len; twoDeg *= 2){
		//merging pairs of arrays that have lenght twoDeg and next to each other
		for(int i = 0; i < len - twoDeg; i += 2 * twoDeg){
			merge<T>(array + i, array + i, twoDeg, array + i + twoDeg, MIN(twoDeg, len - (i + twoDeg)), cmp);
		}
	}
	
}

int main(){
	const int neededTime = 2;
	int len, startTime, endTime;
	Period* arr;

	std::cin >> len;
	arr = new Period[len];

	for (int i = 0; i < len; ++i){
		std::cin >> startTime >> endTime;
		arr[i] = Period(startTime, endTime);
	}

	mergeSort(arr, len, comparePeriods);
	
	int* showCount = (int*) calloc( len, sizeof(int) );
	int totalShowCount = 0;
	for (int i = 0; i < len; ++i){
		int time = arr[i].getEnd();
		while ( showCount[i] < 2 ){
			show(arr, showCount, len, time);
			++totalShowCount;
			--time;
			
		}
	}
	
	std::cout << totalShowCount << std::endl;
	delete [] arr;
}