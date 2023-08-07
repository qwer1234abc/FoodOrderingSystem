#include "Order.h"
#include <fstream>
#include <iomanip>
#include <sstream>

// constructor
template<typename ItemType>
Queue<ItemType>::Queue()
{
	frontNode = nullptr;
	backNode = nullptr;
}

// destructor
template<typename ItemType>
Queue<ItemType>::~Queue()
{
	// Remove all nodes from the queue
	while (!isEmpty())
	{
		dequeue();
	}
}

// enqueue (add) item at the back of queue
template<typename ItemType>
void Queue<ItemType>::enqueue(const ItemType& item)
{
	Node* newNode = new Node; // Create a new node
	newNode->item = item; // Set the data of the node
	newNode->next = nullptr; // Set the next pointer of the node to null

	if (isEmpty())
	{
		// If the queue is empty, set both frontNode and backNode to the new node
		frontNode = newNode;
		backNode = newNode;
	}
	else
	{
		// Otherwise, add the new node to the back of the queue
		backNode->next = newNode;
		backNode = newNode;
	}

	return;
}

// dequeue (remove) item from front of queue
template<typename ItemType>
bool Queue<ItemType>::dequeue()
{
	if (isEmpty())
	{
		// If the queue is empty, return false
		return false;
	}
	else
	{
		Node* temp = frontNode; // Save the front node in a temporary variable
		frontNode = frontNode->next; // Move the frontNode pointer to the next node
		delete temp; // Delete the temporary variable to free up memory

		if (frontNode == nullptr)
		{
			// If there are no more nodes, set backNode to null as well
			backNode = nullptr;
		}

		return true;
	}
}

// dequeue (remove) and retrieve item from front of queue
template<typename ItemType>
bool Queue<ItemType>::dequeue(ItemType& item)
{
	if (isEmpty())
	{
		// If the queue is empty, return false
		return false;
	}
	else
	{
		// Remove the front node and retrieve its data
		Node* temp = frontNode; // Save the front node in a temporary variable
		item = frontNode->item; // Retrieve the item from the front node
		frontNode = frontNode->next; // Move the frontNode pointer to the next node
		delete temp; // Delete the temporary variable to free up memory

		if (frontNode == nullptr)
		{
			// If there are no more nodes, set backNode to null as well
			backNode = nullptr;
		}

		return true;
	}
}

// retrieve (get) item from front of queue
template<typename ItemType>
void Queue<ItemType>::getFront(ItemType& item)
{
	if (isEmpty())
	{
		// If the queue is empty, do nothing
	}
	else
	{
		// Retrieve the item from the front node
		item = frontNode->item;
	}
}

// check if the queue is empty
template<typename ItemType>
bool Queue<ItemType>::isEmpty()
{
	return (frontNode == nullptr && backNode == nullptr);
}

// display items in queue from front to back
template<typename ItemType>
void Queue<ItemType>::displayItems()
{
	if (isEmpty())
	{
		cout << "Queue is empty." << endl;
		return;
	}
	Node* current = frontNode; // Start at the front node

	cout << "Items in queue: ";
	while (current != nullptr)
	{
		// Print the item of each node in the queue
		cout << current->item.getOrderID() << " ";
		current = current->next;  // Move to the next node
	}

	cout << endl;
}

template<typename ItemType>
bool Queue<ItemType>::getLastElement(Queue<ItemType>& q, ItemType& item)
{
	item = backNode->item;

	return true;
}

template<typename ItemType>
int Queue<ItemType>::getNoOfElements()
{
	int count = 0;
	Node* current = frontNode;
	while (current != nullptr) {
		count++;
		current = current->next;
	}

	return count;
}

template<typename ItemType>
void Queue<ItemType>::filterQueueForCustomer(int customerID)
{

	Order currentOrder;
	while (dequeue(currentOrder)) {
		if (currentOrder.getCustomerID() == customerID) {
			enqueue(currentOrder);
		}
	}
}

template class Queue<Order>;