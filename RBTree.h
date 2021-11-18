#include<iostream>
#include<assert.h>

using namespace std;

template<typename K, typename V>
class RBTree {
	static const bool RED = true;
	static const bool BLACK = false;

	struct Node {
		K key;
		V value;
		Node* left;
		Node* right;
		bool color;

		Node(K key,V value) {
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
			color = RED;
		}
	};

public:
	Node* root;
	int size;

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return size == 0;
	}

	RBTree() {
		root = nullptr;
		size = 0;
	}

	bool isRed(Node* node) {
		if (node == nullptr) {
			return BLACK;
		}
		return node->color;
	}


	Node* leftRotate(Node* node) {
		Node* x = node->right;

		node->right = x->left;
		x->left = node;

		x->color = node->color;
		node->color = RED;

		return x;
	}

	Node* rightRotate(Node* node) {
		Node* x = node->left;

		node->left = x->right;
		x->right = node;

		x->color = node->color;
		node->color = RED;

		return x;
	}

	void flipColors(Node* node) {
		node->color = RED;
		node->left->color = BLACK;
		node->right->color = BLACK;
	}



	void add(K key, V value) {
		root = _add(root, key, value);
		root->color = BLACK;
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

		if (isRed(node->right) && !isRed(node->left)) {
			node = leftRotate(node);
		}
		if (isRed(node->left) && isRed(node->left->left)) {
			node = rightRotate(node);
		}
		if (isRed(node->left) && isRed(node->right)) {
			flipColors(node);
		}

		return node;
	}

	void inOrder() {
		_inOrder(root);
	}
	void _inOrder(Node* node) {
		if (node == nullptr) {
			return;
		}
		_inOrder(node->left);
		cout << node->key << ":" << node->value << endl;
		_inOrder(node->right);
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
};