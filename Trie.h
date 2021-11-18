#include<iostream>
#include"BSTMap.h"

using namespace std;



class Trie {
	struct Node2 {
		bool isWord;
		BSTMap<char, Node2*> next;

		Node2(bool isWord) {
			this->isWord = isWord;
			this->next = BSTMap<char, Node2*>();
		}

		Node2() {
			this->isWord = false;
		}
	};

public:

	Node2* root;
	int size;

	Trie() {
		root = new Node2();
		size = 0;
	}

	int getSize() {
		return size;
	}

	void add(string word) {
		Node2* cur = root;
		for (int i = 0; i < word.size(); i++) {
			char c = word[i];
			if (cur->next.get(c) == nullptr) {
				Node2* newNode = new Node2();
				cur->next.add(c, newNode);
			}
			cur = cur->next.get(c);
		}
		if (!cur->isWord) {
			cur->isWord = true;
			size++;
		}
	}

	bool contains(string word) {
		Node2* cur = root;
		for (int i = 0; i < word.size(); i++) {
			char c = word[i];
			if (cur->next.get(c) == nullptr) {
				return false;
			}
			cur = cur->next.get(c);
		}
		return cur->isWord;
	}

	bool isPrefix(string prefix) {
		Node2* cur = root;
		for (int i = 0; i < prefix.size(); i++) {
			char c = prefix[i];
			if (cur->next.get(c) == nullptr) {
				return false;
			}
			cur = cur->next.get(c);
		}
		return true;
	}
};