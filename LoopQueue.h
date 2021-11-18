#include<iostream>
#include<queue>
using namespace std;


template <typename E>
class LoopQueue {

	E* data = new E[10];


	int size;
	int front,tail;
	int capacity;

	void queueresize(int newcapacity) {
		E* newdata = new E[newcapacity];
		for (int i = 0; i < size; i++) {
			newdata[i] = data[(i + front) % capacity];
		}
		data = newdata;
		front = 0;
		tail = size;
		capacity = newcapacity;
	}

public:
	LoopQueue(int cap) {
		capacity = cap;
		data = new E[capacity];
		tail = 0;
		size = 0;
	}
	LoopQueue() {
		capacity = 10;
		data = new E[10];
		tail = 0;
		size = 0;
	}
	int getCapacity() {
		return capacity;
	}
	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	void enqueue(E e) {
		if (size == capacity) {
			queueresize(capacity * 2);
		}
		data[tail] = e;
		tail = (tail + 1) % capacity;
		size++;
	}

	E dequeue() {
		if (isEmpty()) {
			cout << "队列为空" << endl;
			E kong = data[front];
			return kong;
		}
		else
		{
			E ret = data[front];
			data[front] = NULL;
			front = (front + 1) % capacity;
			size--;
			if (size == capacity / 4 && capacity / 2 != 0) {
				queueresize(capacity / 2);
			}
			return ret;
		}
	}


	E getFront() {
		if (isEmpty()) {
			cout << "队列为空" << endl;
		}
		else
		{
			return data[front];
		}
	}


	friend ostream& operator<<(ostream& os, LoopQueue& a) {
		os << "包含元素:" << endl;
		cout << "首：";
			for (int i = 0; i < a.size; i++)
				os << a.data[(a.front + i) % a.capacity] << " ";

		os << "：尾" << endl;
		return os;
	}

};