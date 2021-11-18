#include<iostream>
#include"AVLTree.h"
#include<assert.h>

using namespace std;

template<typename K,typename V>
class HashTable {
	int capacity[26] = { 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
		12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741 };
	static const int upperTol = 10;
	static const int lowerTol = 2;
	int capacityIndex = 0;
public:
	AVLTree<K, V>* hashtable;
	int M;
	int size;
	HashTable() {
		this->M = capacity[capacityIndex];
		hashtable = new AVLTree<K, V>[M];
		for (int i = 0; i < M; i++) {
			hashtable[i] = AVLTree<K, V>();
		}
		size = 0;
	}
	
	int hash(K key) { 
		std::hash<K> ha;
		return (ha(key) & 0x7fffffff) % M;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void add(K key, V value) {

		if (hashtable[hash(key)].contains(key)) {
			hashtable[hash(key)].add(key, value);
		}
		else {
			hashtable[hash(key)].add(key, value);
			size++;
			if (size >= upperTol * M && capacityIndex + 1 < 26) {
				capacityIndex++;
				resize(capacity[capacityIndex]);
			}
		}
	}

	V remove(K key) {
		AVLTree<K, V> map = hashtable[hash(key)];
		V ret = NULL;
		
		if (hashtable[hash(key)].contains(key)) {
			ret = hashtable[hash(key)].remove(key);
			size--;

			if (size < lowerTol * M && capacityIndex - 1 >= 0) {
				capacityIndex--;
				resize(capacity[capacityIndex]);
			}
		}
		return ret;
	}


	void resize(int newM) {
		AVLTree<K, V>* newtable = new AVLTree<K, V>[newM];
		for (int i = 0; i < newM; i++) {
			newtable[i] = AVLTree<K, V>();
		}

		int oldM = M;
		this->M = newM;

		for (int i = 0; i < oldM; i++) {
			K* keys = hashtable[i].keyset();
			for (int j = 0; j < hashtable[i].getSize(); j++) {
				newtable[hash(keys[j])].add(keys[j], hashtable[i].get(keys[j]));
			}
		}
		this->hashtable = newtable;
	}

	bool contains(K key) {
		return hashtable[hash(key)].contains(key);
	}

	V get(K key) {
		return hashtable[hash(key)].get(key);
	}

};