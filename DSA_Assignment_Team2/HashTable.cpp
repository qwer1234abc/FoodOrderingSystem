#include "HashTable.h"

#include <iomanip>

HashTable::HashTable()
{
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = nullptr;
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node* current = items[i];
		while (current != nullptr)
		{
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

int HashTable::hash(KeyType key)
{
	return key % MAX_SIZE; // Simple hash function using the FoodItem's ID
}

// Other member function implementations remain the same, but now work with FoodItem objects
bool HashTable::add(KeyType newKey, ItemType newItem)	
{
	int index = hash(newKey);
	Node* newNode = new Node;
	newNode->key = newKey;
	newNode->item = newItem;
	newNode->next = nullptr;

	if (items[index] == nullptr)
	{
		items[index] = newNode;
	}
	else
	{
		Node* current = items[index];
		while (current->next != nullptr)
		{
			if (current->key == newKey)
			{
				delete newNode;
				return false;
			}
			current = current->next;
		}
		if (current->key == newKey)
		{
			delete newNode;
			return false;
		}
		current->next = newNode;
	}

	size++;
	return true;
}

void HashTable::remove(KeyType key)
{
	int index = hash(key);

	if (items[index] == nullptr)
	{
		return;
	}

	Node* current = items[index];
	Node* previous = nullptr;

	while (current != nullptr)
	{
		if (current->key == key)
		{
			if (previous == nullptr)
			{
				items[index] = current->next;
			}
			else
			{
				previous->next = current->next;
			}
			delete current;
			size--;
			return;
		}
		previous = current;
		current = current->next;
	}
}

ItemType HashTable::get(KeyType key)
{
	int index = hash(key);

	if (items[index] == nullptr)
	{
		return ItemType();
	}

	Node* current = items[index];
	while (current != nullptr)
	{
		if (current->key == key)
		{
			return current->item;
		}
		current = current->next;
	}

	return ItemType();
}

bool HashTable::isEmpty()
{
	return size == 0;
}

int HashTable::getLength()
{
	return size;
}

void HashTable::print()
{
	// Calculate the padding to center the header
	int totalWidth = 60;
	string header = "Food Items Menu";
	int padding = (totalWidth - header.length()) / 2;

	// Print header
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << setw(padding + header.length()) << header << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node* current = items[i];
		while (current != nullptr)
		{
			// Printing the FoodItem details
			cout << setw(4) << left << current->key << " | "
				<< setw(23) << left << current->item.getName() << " | "
				<< setw(18) << left << current->item.getCategory() << " | "
				<< "$" << fixed << setprecision(2) << current->item.getPrice() << endl;
			current = current->next;
		}
	}

	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
}