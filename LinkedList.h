#include<iostream>
using namespace std;

template <typename E>
class LinkedList {
public:
    class Node {
    public:
        E e;
        Node* next;
        Node(E e,Node* next){
            this->e = e;
            this->next = next;
        }

        Node(E e) {
            this->e = e;
            this->next = nullptr;
        }

        Node() {
            this->e = NULL;
            this->next = nullptr;
        }
    };
    Node* dummyhead ;
    int size;


    LinkedList() {
        dummyhead = new Node(NULL, nullptr);
        size = 0;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    void addFirst(E e) {

        //Node* node = new Node(e);
        //node->next = head;
        //head = node;
        //size++;
        add(0, e);
    }

    void add(int index, E e) {

        if (index<0||index>size)
        {
            cout << "·¶Î§´íÎó" << endl;
            return ;
        }

        Node* prev = dummyhead;

        for (int i = 0; i < index; i++) {
            prev = prev->next;
        }
        Node* node =new Node(e);
        node->next = prev->next;
        prev->next = node;
        size++;
    }

    void addLast(E e) {
        add(size, e);
    }

    E get(int index) {
        if (index<0 || index>size)
        {
            cout << "·¶Î§´íÎó" << endl;
            return -1;
        }
        Node* cur = dummyhead->next;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        return cur->e;
    }

    E getFirst() {
        return get(0);
    }

    E getLast() {
        return get(size - 1);
    }


    void set(int index, E e) {
        if (index<0 || index>size)
        {
            cout << "·¶Î§´íÎó" << endl;
            return;
        }

        Node* cur = new Node();
        cur = dummyhead->next;
        for (int i = 0; i <index; i++) {
            cur = cur->next;
        }
        cur->e = e;
        return;
    }

    bool contains(E e) {
        Node* cur = new Node();
        cur = dummyhead->next;
        for (int i = 0; i < size; i++) {
            if (cur->e == e) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    int find(E e) {
        Node* cur = new Node();
        cur = dummyhead->next;
        for (int i = 0; i < size; i++) {
            if (cur->e == e) {
                return i;
            }
            cur = cur->next;
        }
        cout << "Ã»ÓÐÕâ¸öÊý" << endl;
        return -1;
    }


    E remove(int index) {
        if (index<0 || index>size)
        {
            cout << "·¶Î§´íÎó" << endl;
            return -1;
        }

        Node* prev = dummyhead;
        for (int i = 0; i < index; i++) {
            prev = prev->next;
        }
        Node* retnode = new Node();
        retnode = prev->next;
        prev->next = retnode->next;
        retnode->next = nullptr;
        size--;
        return retnode->e;
    }

    E removeFirst() {
        return remove(0);
    }
    E removeLast() {
        return remove(size - 1);
    }

    Node* reverse() {
        Node* pre = new Node();
        Node* cur = new Node();
        Node* next = new Node();

        cur = dummyhead->next;
        
        for (int i = 0; i < size; i++) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }



    friend ostream& operator<<(ostream& os, LinkedList& a) {
        os << "°üº¬ÔªËØ:" << endl;
        cout << "Ê×£º";
        Node* cur = new Node();
        cur = a.dummyhead->next;
        cout << cur->e << endl;
        int i = 0;
        while (i<a.size)
        {
            cout << i << ":µÄÖµÎª  " << cur->e << endl;
            cur = cur->next;
            i++;
        }
        os << "£ºÎ²" << endl;
        return os;
    }



};