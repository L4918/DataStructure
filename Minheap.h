#include<iostream>
#include"动态数组.h"
#include<assert.h>

using namespace std;

template<typename E>
class Minheap {

public:
	Array<E> data;

	Minheap(int capacity) {
		data = Array<E>(capacity);
	}
	Minheap() {
		data = Array<E>();
	}

	Minheap(E arr[], int n) {
		data = Array<E>(arr, n);
		for (int i = parent(n - 1); i >= 0; i--) {
			siftDown(i);
		}
	}

	int getSize() {
		return data.getSize();
	}

	bool isEmpty() {
		return data.isEmpty();
	}

	int parent(int index) {
		if (index <= 0) {
			cout << "索引值不对劲" << endl;
			return -1;
		}
		return (index - 1) / 2;
	}

	int leftchild(int index) {
		if (index < 0) {
			cout << "索引值不对劲" << endl;
			return -1;
		}
		return index * 2 + 1;
	}

	int rightchild(int index) {
		if (index < 0) {
			cout << "索引值不对劲" << endl;
			return -1;
		}
		return index * 2 + 2;
	}

	void add(E e) {
		data.addLast(e);
		siftUp(data.getSize() - 1);
	}

	void siftUp(int k) {
		while (k > 0 && data.get(k) < data.get(parent(k)))
		{
			data.swap(k, parent(k));
			k = parent(k);
		}
	}

	E findMin() {
		if (data.getSize() == 0) {
			cout << "队列为空" << endl;
		}
		return data.get(0);
	}

	E extractMin() {
		E ret = findMin();
		data.swap(0, data.getSize() - 1);
		data.removeLast();
		siftDown(0);
		return ret;
	}

	void siftDown(int k) {
		while (leftchild(k) < data.getSize()) {
			int j = leftchild(k);
			if (j + 1 < data.getSize() && data.get(j) > data.get(j + 1)) {
				j++;
			}

			if (data.get(k) <= data.get(j)) {
				break;
			}
			data.swap(k, j);
			k = j;
		}
	}
	//取出当前最大元素并替换为e
	E replace(E e) {
		E ret = findMin();
		data.set(0, e);
		siftDown(0);
		return ret;
	}

};