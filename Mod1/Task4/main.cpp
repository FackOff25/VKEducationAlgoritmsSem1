#include <stdlib.h>
#include <iostream>

class Process{
	private:
		int P;
		int T;
		int t;
	public:
		Process(): P(0), T(0){};
		Process(int _P, int _T): P(_P), T(_T) {t = 0;};
		void work(){
			t += P;
		};
		int getPrority() const {return P;};
		int getTime() const {return T;};
		int getWorktime() const {return t;};
		bool isFinished() const {return  t >= T;};
		Process operator=(const Process &pr){
			P = pr.P;
			T = pr.T;
			t = pr.t;
			return *this;
		};
};

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

class ProcessComparator: public iComparator<Process>{
	public:
		ProcessComparator(){};
		bool operator()(const Process &first, const Process &second){
			return (first.getPrority() * (first.getWorktime() + 1) < second.getPrority() * ( second.getWorktime() + 1 ));
		};
};

template<typename T>
class Heap{
	private:

		int len;
		int arrayLen;
		T* heap; 
		iComparator<T> cmp;

	public:

		void siftDown(int idx){
			int maxChild, left, right;
			while (2 * idx + 1 < len - 1) {
				maxChild = left = 2 * idx + 1;
				right = 2 * idx + 2;

				if( right < len - 1 )
					if ( cmp( heap[right], heap[left]) ) maxChild = right
					;

				if ( cmp( heap[maxChild], heap[idx]) ) {
					swap(idx, maxChild);
					idx = maxChild;
				}else return;
			}
		}

		void siftUp(int idx){
			while (cmp(heap[idx], heap[(idx - 1)/2])) {
				swap(idx, (idx - 1)/2);
				idx = (idx - 1)/2;
			}
		}

		void deleteItem(int idx){
			--len;
			if ( len > 0 ){
				heap[idx] = heap[len];
				if (! len > arrayLen / 2) shrinkArray();
				siftDown(idx);
			}
		}

		void swap(const int idx1, const int idx2){
			T temp = heap[idx1];
			heap[idx1] = heap[idx2];
			heap[idx2] = temp;
		}

		void expandArray(){
			
			arrayLen = arrayLen * 2 + 1;
			heap = (T*) realloc(heap, sizeof(T) * arrayLen);
		}

		void shrinkArray(){
			arrayLen = arrayLen / 2;
			heap = (T*) realloc(heap, sizeof(T) * arrayLen);
		}

		bool isEmpty() {return len == 0;};

	public:

		Heap(){
			arrayLen = 1;
			len = 0;
			heap = new T[1];
		}

		Heap(const iComparator<T>& _cmp): cmp(_cmp){
			arrayLen = 1;
			len = 0;
			heap = new T[1];
		}

		Heap(const Heap<T>& _heap): len(_heap.len), arrayLen(_heap.arrayLen), cmp(_heap.cmp){
			heap = new T[arrayLen];
			memcpy(heap, _heap.heap, len);
		}

		~Heap(){
			delete [] heap;
		}

		Heap<T>& operator=(const Heap<T>& _heap){
			len = _heap.len;
			arrayLen = _heap.arrayLen;
			cmp = _heap.cmp;
			heap = new T[arrayLen];
			memcpy(heap, _heap.heap, len);
			return *this;
		}

		const T& getTop(){ return heap[0];};

		T extractTop() {
			T toReturn = heap[0];
			deleteItem(0);
			return toReturn;
		};

		void add(const T& item){
			if (! ( len < arrayLen ) ) expandArray();
			heap[len] = item;
			siftUp(len);
			++len;
		};
};

int main(){
	int processNumber;
	int P, T;
	ProcessComparator cmp;
	Heap<Process> heap(cmp);

	std::cin >> processNumber;
	for(int i = 0; i < processNumber; ++i){
		std::cin >> P >> T;
		heap.add(Process(P,T));
	}
	
	Process pr;
	int i;

	for(i = 0; !heap.isEmpty(); ++i){
		pr = heap.extractTop();
		pr.work();
		if (!pr.isFinished()) heap.add(pr);
	}
	std::cout << i << std::endl;
	return 0;
}