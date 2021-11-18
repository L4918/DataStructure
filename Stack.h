#include<iostream>
#include"动态数组.h"
using namespace std;


template <typename E>
class ArrayStack {

public:
	Array <E> array;
	ArrayStack(int capacity) {
		array = Array<E>(capacity);
	}
	ArrayStack() {
		array = Array<E>();
	}

	int getSize() {
		return array.getSize();
	}
	bool isEmpty() {
		return array.isEmpty();
	}

	int getCapacity() {
		return array.getCapacity();
	}

	void push(E e) {
		array.addLast(e);
	}

	E pop() {
		return array.removeLast();
	}

	E peek() {
		return array.getLast();
	}

	friend ostream& operator<<(ostream& os, ArrayStack& a) {
		os << "包含元素:" << endl;
		for (int i = 0; i < a.getSize(); i++)
			os << a.array.get(i) << " ";
		return os;
	}
};



