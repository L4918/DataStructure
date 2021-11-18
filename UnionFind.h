#include<iostream>
#include<assert.h>

using namespace std;

class UnionFind {
	int* parent;
	int* rank;
	int size;

	UnionFind(int size) {
		this->size = size;
		this->parent = new int[size];
		this->rank = new int[size];

		for (int i = 0; i < size; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}
	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	//查找元素p对应的集合编号
	int find(int p) {
		assert(p >= 0 && p < size);
		while (parent[p] != p) {
			parent[p] = parent[parent[p]];
			p = parent[p];
		}
		return p;
	}

	void unionElements(int p,int q) {
		int proot = find(p);
		int qroot = find(q);

		if (proot = qroot) {
			return;
		}
		if (rank[proot] < rank[qroot]) {
			parent[proot] = qroot;
		}
		else if (rank[proot] > rank[qroot]) {
			parent[qroot] = proot;
		}
		else {
			parent[qroot] = proot;
			rank[proot] += 1;
		}
	}
};