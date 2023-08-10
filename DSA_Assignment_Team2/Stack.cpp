#include "Stack.h"
#include "Notification.h"

template<typename ItemType>
Stack<ItemType>::Stack()
{
	top = nullptr;
}

template<typename ItemType>
Stack<ItemType>::~Stack()
{
	while (!isEmpty())
	{
		pop();
	}
}

template<typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return top == nullptr;
}

template<typename ItemType>
bool Stack<ItemType>::push(const ItemType& item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = nullptr;

	if (isEmpty())
	{
		top = newNode;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}

	return true;
}

template<typename ItemType>
ItemType Stack<ItemType>::pop()
{
	if (isEmpty())
	{
		return ItemType();
	}
	else
	{
		Node* temp = top;
		top = top->next;
		ItemType item = temp->item;
		delete temp;
		return item;
	}
}

template<typename ItemType>
ItemType Stack<ItemType>::peek() const
{
	if (isEmpty())
	{
		return ItemType();
	}
	else
	{
		return top->item;
	}
}

template class Stack<Notification>;
