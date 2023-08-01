#pragma once
#include <iostream>
#include <string>

using namespace std;

template <class T>
class LinkedList
{
private:
	struct Node
	{
		T item;
		Node* next;
	};

	Node* head;
	int size;

public:
	LinkedList();
	~LinkedList();

	bool isEmpty() const;
	int getLength() const;
	bool retrieve(int index, T& item) const;
	T retrieve(int index) const;
	bool insert(T item);
	bool remove(int index);
};
