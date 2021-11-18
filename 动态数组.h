#include<iostream>
using namespace std;




template <typename E>
class  Array {
private:
	E* data = new E[10];
	int size;
	int capacity;

public:
	Array(int cap) {
		capacity = cap;
		data = new E[capacity];
		size = 0;
	}
	Array() {
		capacity = 5;
		data = new E[capacity];
		size = 0;
	}
	Array(E arr[],int n) {
		data = new E[n];
		for (int i = 0; i < n; i++) {
			data[i] = arr[i];
		}
		size = n;
	}

	int getSize() {
		return size;
	}

	int getCapacity() {
		return capacity;
	}

	bool isEmpty() {
		return size == 0;
	}

	void resize(int newcapacity) {
		E* newData = new E[newcapacity];
		for (int i = 0; i < size; i++) {
			newData[i] = data[i];
		}
		data = newData;
	}



	void add(int index, E e) {
		if (size == capacity) {
			resize(capacity * 2);
			capacity = capacity * 2;
		}
		if (index<0 || index>size)
		{
			cout << "输入非法范围" << endl;
			return;
		}
		for (int i = size - 1; i >= index; i--) {
			data[i + 1] = data[i];
		}
		data[index] = e;
		size++;
	}

	void addFirst(E e) {
		add(0, e);
	}
	void addLast(E e) {
		add(size, e);
	}

	E get(int index) {
		if (index >= size || index < 0)
		{
			cout << "索引范围不太对" << endl;
			return NULL;
		}
		return data[index];
	}

	E getFirst() {
		return array.get(0);
	}

	E getLast() {
		return array.get(size - 1);
	}
	 

	void set(int index, E e) {
		if (index >= size || index < 0)
		{
			cout << "索引范围不太对" << endl;
		}
		data[index] = e;
	}

	bool contains(E e) {
		for (int i = 0; i < size; i++) {
			if (data[i] == e) {
				return true;
			}
		}
		return false;
	}

	int find(E e) {
		for (int i = 0; i < size; i++) {
			if (data[i] == e) {
				return i;
			}
		}
		return -1;
	}

	E remove(int index) {
		if (index >= size || index < 0)
		{
			cout << "索引范围不太对" << endl;
			return -1;
		}
		int re = data[index];
		for (int i = index + 1; i < size; i++) {
			data[i - 1] = data[i];
		}
		size--;
		return re;
	}

	E removeFirst() {
		return remove(0);
	}

	E removeLast() {
		return remove(size - 1);
	}
	void removeElement(E e) {
		int index = find(e);
		if (index != -1) {
			remove(index);
		}
	}

	void swap(int i,int j) {
		
		if (i<0 || i>size || j<0 || j>size) {
			cout << "索引范围不对" << endl;
			return;
		}
		E temp = data[j];
		data[j] = data[i];
		data[i] = temp;
	}


	friend ostream& operator<<(ostream& os, const Array& a) {
		os << "capacity:" << a.capacity << endl;
		os << "size:" << a.size << endl;
		os << "包含元素:" << endl;
		for (int i = 0; i < a.size; i++)
			os << a.data[i] << " ";
		return os;
	}
};

