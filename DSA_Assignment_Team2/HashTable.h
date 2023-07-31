#include "FoodItem.h" // Assuming the FoodItem class is defined in FoodItem.h
#include <iostream>

const int MAX_SIZE = 101;
typedef FoodItem ItemType; // Using FoodItem as the item type
typedef int KeyType;       // Using FoodItem's ID as the key

struct Node
{
	KeyType key;    // search key
	ItemType item;  // data item (FoodItem object)
	Node* next;     // pointer pointing to the next item
};

class HashTable
{
private:
	Node* items[MAX_SIZE];
	int size; // number of items in the HashTable

public:
	// constructor
	HashTable();

	// destructor
	~HashTable();

	int hash(KeyType key);

	// add a new item with the specified key to the HashTable
	bool add(KeyType newKey, ItemType newItem);

	// remove an item with the specified key in the HashTable
	void remove(KeyType key);

	// get an item with the specified key in the HashTable (retrieve)
	ItemType get(KeyType key);

	// check if the HashTable is empty
	bool isEmpty();

	// check the size of the HashTable
	int getLength();

	// display the items in the HashTable
	void print();
};