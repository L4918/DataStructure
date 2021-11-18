#include<iostream>
#include"BST.h"

using namespace std;

template<typename K, typename V>
class BSTMap {
	struct Node {

		Node(K k,V v) {
			this->key = k;
			this->value = v;
			this->left = nullptr;
			this->right = nullptr;
		}

		K key;
		V value;
		Node* left;
		Node* right;
	};

private:
	Node* root;
	int size;

public:
	BSTMap() {
		root = nullptr;
		size = 0;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	void add(K key,V value) {
		root = _add(root, key, value);
	}
	Node* _add(Node* node, K key, V value) {
		if (node == nullptr) {
			size++;
			return new Node(key, value);
		}

		if (node->key == key) {
			node->value = value;
		}
		else if (node->key > key) {
			node->left = _add(node->left, key, value);
		}
		else {
			node->right = _add(node->right, key, value);
		}
		return node;
	}

	Node* getNode(Node* node, K key) {
		if (node == nullptr) {
			return nullptr;
		}
		if (node->key == key) {
			return node;
		}
		else if (node->key > key) {
			return getNode(node->left, key);
		}
		else {
			return getNode(node->right, key);
		}
		
	}

	bool contains(K key) {
		return getNode(root, key) != nullptr;
	}

	V get(K key) {
		Node* node = getNode(root, key);
		return node == nullptr ? nullptr : node->value;
	}

	void set(K key, V value) {
		Node* node = getNode(root, key);
		if (node == nullptr) {
			cout << "本树没有这个key" << endl;
			return;
		}
		node->value = value;
	}

	V minimum() {
		if (size == 0) {
			cout << "本树为空" << endl;
			assert(false);
		}
		return _minimum(root)->value;
	}

	Node* _minimum(Node* node) {
		if (node->left == nullptr) {
			return node;
		}
		return _minimum(node->left);
	}

	V maximum() {
		if (size == 0) {
			cout << "本树为空" << endl;
			assert(false);
		}
		return _maximum(root)->value;
	}


	Node* _maximum(Node* node) {
		if (node->right == nullptr) {
			return node;
		}
		return _maximum(node->right);
	}

	V removeMin() {
		V ret = minimum();
		root = _removeMin(root);
		return ret;
	}
	Node* _removeMin(Node* node) {
		if (node->left == nullptr) {
			Node* rightnode = node->right;
			node->right = nullptr;
			size--;
			return rightnode;
		}
		node->left = _removeMin(node->left);
		return node;
	}


	V removeMax() {
		V ret = maximum();
		root = _removeMax(root);
		return ret;
	}


	Node* _removeMax(Node* node) {
		if (node->right == nullptr) {
			Node* leftnode = node->left;
			node->left = nullptr;
			size--;
			return leftnode;
		}
		node->right = _removeMax(node->right);
		return node;
	}

	V remove(K key) {
		Node* node = getNode(root, key);
		if (node != nullptr) {
			root = _remove(root, key);
			return node->value;
		}
	}

	Node* _remove(Node* node, K key) {
		if (node == nullptr) {
			return nullptr;
		}
		if (key > node->key) {
			node->right = _remove(node->right, key);
			return node;
		}
		else if (key < node->key) {
			node->left = _remove(node->left, key);
			return node;
		}

		else {
			if (node->left == nullptr) {
				Node* rightnode = node->right;
				node->right = nullptr;
				size--;
				return rightnode;
			}

			if (node->right == nullptr) {
				Node* leftnode = node->left;
				node->left = nullptr;
				size--;
				return leftnode;
			}

			Node* successor = _minimum(node->right);
			successor->right = _removeMin(node->right);
			successor->left = node->left;
			node->left = nullptr;
			node->right = nullptr;
			return successor;
		}
	}

	void inOrder() {
		_inOrder(root);
	}
	void _inOrder(Node* node) {
		if (node == nullptr) {
			return;
		}
		_inOrder(node->left);
		cout << node->key <<":"<<node->value<< endl;
		_inOrder(node->right);
	}
	//基于中序遍历实现key值获取
	K*  keyset() {
		LoopQueue<Node*> q;
		q.enqueue(root);
		int j = 0;
		K* temp = new K[size];
		while (!q.isEmpty()) {
			Node* cur = q.dequeue();
			temp[j] = cur->key;
			if (cur->left != nullptr) {
				q.enqueue(cur->left);
			}
			if (cur->right != nullptr) {
				q.enqueue(cur->right);
			}
			j++;
		}
		return temp;
	}


};