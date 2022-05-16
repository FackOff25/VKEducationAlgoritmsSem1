#include <stdlib.h>
#include <cstring>
#include <iostream>

class Queue{
	private:
		int* array;
		int len;
		int* head;					//beginning of cycle buf
		int* tail;					//end of cycle buf

	public:
	Queue(){
		len = 4;
		array = new int[len];
		head = tail = array;
	}

	Queue(const Queue& que){
		len = que.len;
		array = new int[len];
		head = array + ( que.head - que.array );
		tail = array + ( que.tail- que.array );
		memcpy(array, que.array, len);
	}

	~Queue(){
		delete [] array;
	}

	Queue& operator=(const Queue& que){
		len = que.len;
		array = new int[len];
		head = array + ( que.head - que.array );
		tail = array + ( que.tail- que.array );
		memcpy(array, que.array, len);
		return *this;
	}

	//При возможности операции проводит её, при невозможности игнорирует. Возвращает возможность
	bool popFront(int num){
		if (head == tail) {
			if (num == -1) return true;
			else return false;
		}

		if (num != *head) return false;
		head == array + len - 1 ? head = array : ++head;

		return true;
	}

	bool pushBack(int num){
		if ( tail == array + len ){
			if ( head == array ) expandArray();
			else tail = array;
		}
		
		if ( tail == head - 1 ) expandArray();
		*tail = num;
		tail++;

		return true;
	}

	void expandArray(){
		int newLen = len * 2;
		int* newArr = new int[newLen];
		int* newHead;

		if( tail - head > 0 ){
			newHead = newArr + ( head - array );
			//int* newTail = newArr + ( tail - array );
			memcpy(newHead, head, ( tail - head ) * sizeof(int));

			head = newHead;
			tail = newArr + ( tail - array );			
		}else{
			newHead = newArr + newLen - ( ( array + len ) - head ) ;
			//int* newTail = newArr + ( tail - array );
			memcpy(newHead, head, ( ( array + len ) - head )  * sizeof(int));
			memcpy(newArr, array, ( tail - array )  * sizeof(int) );

			head = newHead;
			tail = newArr + ( tail - array );	
		}

		len = newLen;
		delete [] array;
		array = newArr;
	}
};

int main(){
	int commands;
	int a, b;
	Queue queue;
	std::cin >> commands;

	bool flag = true;

	for(int i = 0; i < commands; ++i){
		std::cin >> a >> b;
		switch (a)
		{
		case 2:
			flag = flag && queue.popFront(b);
			break;
		case 3:
			flag = flag && queue.pushBack(b);
			break;
		default:
			flag = false;
			break;
		}
	}
	flag ? std::cout << "YES" << std::endl : std::cout << "NO" << std::endl;
}