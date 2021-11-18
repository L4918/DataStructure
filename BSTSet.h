#include<iostream>
#include"BST.h"
using namespace std;


template<typename E>
class BSTSet {
	BST<E> bst;

public:
	BSTSet() {
		bst = BST<E>();
	}

	int getSize() {
		return bst.getSize();
	}

	bool isEmpty() {
		return bst.isEmpty();
	}

	void add(E e) {
		bst.add(e);
	}

	bool contains(E e) {
		return bst.contains(e);
	}

	void remove(E e) {
		bst.remove(e);
	}

	void getBST() {
		bst.inOrder();
	}
};