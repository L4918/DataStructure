#include<iostream>
#include"动态数组.h"
#include<assert.h>
#include"LoopQueue.h"

using namespace std;

template<typename K,typename V>
class AVLTree {
	struct Node {
		K key;
		V value;
		Node* left;
		Node* right;
		int height;

		Node(K key, V value) {
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
			this->height = 1;
		}
		Node(K key) {
			this->key = key;
			this->value = NULL;
			this->left = nullptr;
			this->right = nullptr;
			this->height = 1;
		}
	};

public:

	Node* root;
	int size;

	AVLTree() {
		root = nullptr;
		size = 0;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	bool isBST() {
		Array<K> keys = Array<K>();
		inOrder(root, keys);
		for (int i = 1; i < keys.getSize(); i++) {
			if (keys.get(i-1) > keys.get(i)) {
				return false;
			}
		}
		return true;
	}
	void inOrder(Node* node, Array<K> keys) {
		if (node == nullptr) {
			return;
		}
		inOrder(node->left, keys);
		cout << node->key << endl;
		keys.addLast(node->key);
		inOrder(node->right, keys);
	}


	bool isBalanced() {
		return _isBalanced(root);
	}

	bool _isBalanced(Node* node) {
		if (node == nullptr) {
			return true;
		}

		int balancefactor = getBalanceFactor(node);
		if (abs(balancefactor) > 1) {
			return false;
		}
		return _isBalanced(node->left) && _isBalanced(node->right);
	}


	int getHeight(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return node->height;
	}

	int getBalanceFactor(Node* node) {
		return getHeight(node->left) - getHeight(node->right);
	}

	Node* rightRotate(Node* y) {
		Node* x = y->left;
		Node* T3 = x->right;
		x->right = y;
		y->left = T3;
		x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
		y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
		return x;
	}

	Node* leftRotate(Node* y) {
		Node* x = y->right;
		Node* T2 = x->left;
		x->left = y;
		y->right = T2;
		x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
		y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
		return x;
	}


	void add(K key, V value) {
		root = _add(root, key, value);
	}

	Node* _add(Node* node, K key, V value) {
		if (node == nullptr) {
			size++;
			return new Node(key, value);
		}

		if (key > node->key) {
			node->right = _add(node->right, key, value);
		}
		else if (key < node->key) {
			node->left = _add(node->left, key, value);
		}
		else {
			node->value = value;
		}

		node->height = 1 + max(getHeight(node->left), getHeight(node->right));

		int balancefactor = getBalanceFactor(node);

		//LL
		if (balancefactor > 1 && getBalanceFactor(node->left) >= 0) {
			return rightRotate(node);
		}
		//RR
		else if (balancefactor < -1 && getBalanceFactor(node->right) <= 0) {
			return leftRotate(node);
		}
		//LR
		else if (balancefactor > 1 && getBalanceFactor(node->left) < 0) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		//RL
		else if (balancefactor < -1 && getBalanceFactor(node->right) > 0) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
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
		return node == nullptr ? NULL : node->value;
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

		Node* retNode = nullptr;
		if (key > node->key) {
			node->right = _remove(node->right, key);
			retNode = node;
		}
		else if (key < node->key) {
			node->left = _remove(node->left, key);
			retNode = node;
		}

		else {
			if (node->left == nullptr) {
				Node* rightnode = node->right;
				node->right = nullptr;
				size--;
				retNode = rightnode;
			}

			else if (node->right == nullptr) {
				Node* leftnode = node->left;
				node->left = nullptr;
				size--;
				retNode = leftnode;
			}
			else {
				Node* successor = _minimum(node->right);
				successor->right = _remove(node->right,successor->key);
				successor->left = node->left;
				node->left = nullptr;
				node->right = nullptr;
				retNode = successor;
			}
		}

		if (retNode == nullptr) {
			return nullptr;
		}

		retNode->height = 1 + max(getHeight(retNode->left), getHeight(retNode->right));

		int balancefactor = getBalanceFactor(retNode);

		//LL
		if (balancefactor > 1 && getBalanceFactor(retNode->left) >= 0) {
			return rightRotate(retNode);
		}
		//RR
		else if (balancefactor < -1 && getBalanceFactor(retNode->right) <= 0) {
			return leftRotate(retNode);
		}
		//LR
		else if (balancefactor > 1 && getBalanceFactor(retNode->left) < 0) {
			retNode->left = leftRotate(retNode->left);
			return rightRotate(retNode);
		}
		//RL
		else if (balancefactor < -1 && getBalanceFactor(retNode->right) > 0) {
			retNode->right = rightRotate(retNode->right);
			return leftRotate(retNode);
		}
		return retNode;
	}


	K* keyset() {
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