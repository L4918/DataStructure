#include<iostream>
#include "LoopQueue.h"
#include<assert.h>
using namespace std;

template<typename T>
class BST {
	struct Node
	{

		Node(T val){
			this->value = val;
			this->left = nullptr;
			this->right = nullptr;
		}

		T value;
		Node* left = nullptr;
		Node* right = nullptr;

		

		
	};



public:
	

	Node* root;
	int size;

	BST() {
		root = nullptr;
		size = 0;
	}

	int getSize() {
		return size;
	}
	bool isEmpty() {
		return size == 0;
	}

	void add(T value) {
		root = _add(root, value);
	}

	Node* _add(Node* node, T value) {
		if (node == nullptr) {
			size++;
			return new Node(value);
		}

		if (node->value > value) {
			node->left = _add(node->left, value);
		}
		else if (node->value < value) {
			node->right = _add(node->right, value);
		}
		return node;
	}

	bool contains(T value) {
		return _contains(root, value);
	}

	bool _contains(Node* node, T value) {
		if (node == nullptr) {
			return false;
		}

		if (node->value == value) {
			return true;
		}

		else if (node->value > value) {
			return _contains(node->left, value);
		}
		else {
			return _contains(node->right, value);
		}
	}

	T minimum() {
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

	T maximum() {
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

	T removeMin() {
		T ret = minimum();
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


	T removeMax() {
		T ret = maximum();
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

	void remove(T value) {
		root = _remove(root, value);
	}

	Node* _remove(Node* node, T value) {
		if (node == nullptr) {
			return nullptr;
		}
		if (value > node->value) {
			node->right = _remove(node->right, value);
			return node;
		}
		else if (value < node->value) {
			node->left = _remove(node->left, value);
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






	void preOrder() {
		_preOrder(root);
	}
	void _preOrder(Node* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->value << endl;
		_preOrder(node->left);
		_preOrder(node->right);
	}


	void inOrder() {
		_inOrder(root);
	}
	void _inOrder(Node* node) {
		if (node == nullptr) {
			return;
		}
		_inOrder(node->left);
		cout << node->value << endl;
		_inOrder(node->right);
	}

	void postOrder() {
		_postOrder(root);
	}
	void _postOrder(Node* node) {
		if (node == nullptr) {
			return;
		}
		_postOrder(node->left);
		_postOrder(node->right);
		cout << node->value << endl;
	}


	void levelOrder() {
		LoopQueue<Node*> q;
		q.enqueue(root);
		while (!q.isEmpty()) {
			Node* cur = q.dequeue();
			cout << cur->value << endl;
			if (cur->left != nullptr) {
				q.enqueue(cur->left);
			}
			if (cur->right != nullptr) {
				q.enqueue(cur->right);
			}
		}

	}

};