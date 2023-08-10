#pragma once
#include <string>
#include <iostream>

using namespace std;

template<typename ItemType>

class Stack
{
private:
	struct Node
	{
		ItemType item;
		Node* next;
	};

	Node* top;

public:
	Stack();
	~Stack();
	bool isEmpty() const;
	bool push(const ItemType& item);
	ItemType pop();
	ItemType peek() const;
};

