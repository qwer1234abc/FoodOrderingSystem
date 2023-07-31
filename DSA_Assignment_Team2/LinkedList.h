#pragma once
#include <iostream>
#include <string>
#include "OrderItem.h"

using namespace std;

class LinkedList
{
private:
	struct Node
	{
		OrderItem item;
		Node* next;
	};

	Node* head;
	int size;

public:
	LinkedList();
	~LinkedList();

	bool isEmpty() const;
	int getLength() const;
	bool retrieve(int index, OrderItem& orderItem) const;
	bool insert(OrderItem orderItem);
	bool remove(int index);
};

