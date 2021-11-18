#include<iostream>
#include"HashTable.h"



using namespace std;


int add(int a, int b) {
	return (a + b);
}

int main() {


	HashTable<int,int> a = HashTable<int, int>();

	
	for (int i = 0; i < 1000; i++) {
		a.add(i, i);
	}

	cout << a.M << endl;
	
	
}