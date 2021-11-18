#include<iostream>
#include"Maxheap.h"

using namespace std;


template<typename E>
class PriorityQueue {
public:
	Maxheap<E> maxHeap;

	PriorityQueue() {
		maxHeap = Maxheap<E>();
	}

	int getSize() {
		return maxHeap.getSize();
	}

	bool isEmpty() {
		return maxHeap.isEmpty();
	}

	E getFront() {
		return maxHeap.findMax();
	}

	void enqueue(E e) {
		maxHeap.add(e);
	}

	E dequeue() {
		return maxHeap.extractMax();
	}
};