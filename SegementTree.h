#include<iostream>
#include<assert.h>

using namespace std;

template<typename E>
class SegementTree {

public:
	E* data;
	E* tree;
	E(*merge)(E,E);
	int size = 0;
	int capacity = 0;

	int getSize() {
		return size;
	}

	E get(int index) {
		assert(index >= 0 || index < size);
		return data[index];
	}

	int leftChild(int index) {
		return (2 * index + 1);
	}

	int rightChild(int index) {
		return 2 * index + 2;
	}

	SegementTree(E arr[], int n, E(*merge1)(E , E )) {
		merge = merge1;
		data = new E[n];
		tree = new E[4 * n];
		for (int i = 0; i < n; i++) {
			data[i] = arr[i];
		}
		buildSegementTree(0, 0, n - 1);
		size = n;
		capacity = 4 * n;
	}

	void buildSegementTree(int treeIndex, int l, int r) {
		if (l == r) {
			tree[treeIndex] = data[l];
			return;
		}
		int leftTreeIndex = leftChild(treeIndex);
		int rightTreeIndex = rightChild(treeIndex);
		int mid = l + (r - l) / 2;

		buildSegementTree(leftTreeIndex, l, mid);
		buildSegementTree(rightTreeIndex, mid + 1, r);
		tree[treeIndex] = merge(tree[leftTreeIndex], tree[rightTreeIndex]);
	}


	E query(int queryL, int queryR) {
		assert(queryL >= 0 && queryL <= size && queryR >= 0 && queryR <= size);
		return _query(0, 0, size - 1, queryL, queryR);
	}

	E _query(int treeIndex, int l, int r, int queryL, int queryR) {
		if (l == queryL && r == queryR) {
			return tree[treeIndex];
		}
		int mid = l + (r - l) / 2;
		int leftTreeIndex = leftChild(treeIndex);
		int rightTreeIndex = rightChild(treeIndex);
		if (queryL >= mid + 1) {
			return _query(rightTreeIndex, mid + 1, r, queryL, queryR);
		}
		else if (queryR <= mid) {
			return _query(leftTreeIndex, l, mid, queryL, queryR);
		}
		E leftResult = _query(leftTreeIndex, l, mid, queryL, mid);
		E rightResult = _query(rightTreeIndex, mid + 1, r, mid + 1, queryR);
		return merge(leftResult, rightResult);

	}

	void set(int index, E e) {
		data[index] = e;
		_set(0, 0, size - 1, index, e);
	}
	void _set(int treeIndex, int l, int r, int index, E e) {
		if (l == r) {
			tree[treeIndex] = e;
		}
		int mid = l + (r - l) / 2;
		int leftTreeIndex = leftChild(treeIndex);
		int rightTreeIndex = rightChild(treeIndex);
		if (index >= mid + 1) {
			_set(rightTreeIndex, mid + 1, r, index, e);
		}
		else {
			_set(leftTreeIndex, l, mid, index, e);
		}
		tree[treeIndex] = merge(tree[leftTreeIndex], tree[rightTreeIndex]);
	}
};