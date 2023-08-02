#include "HashTable.h"
#include <iostream>
#include <iomanip>

template<typename KeyType, typename ItemType>
HashTable<KeyType, ItemType>::HashTable()
{
	size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = nullptr;
	}
}

template<typename KeyType, typename ItemType>
HashTable<KeyType, ItemType>::~HashTable()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node<KeyType, ItemType>* current = items[i];
		while (current != nullptr)
		{
			Node<KeyType, ItemType>* temp = current;
			current = current->next;
			delete temp;
		}
	}
}

template<typename KeyType, typename ItemType>
int HashTable<KeyType, ItemType>::hash(KeyType key)
{
	return key % MAX_SIZE; // Simple hash function using the FoodItem's ID
}

// Other member function implementations remain the same, but now work with FoodItem objects
template<typename KeyType, typename ItemType>
bool HashTable<KeyType, ItemType>::add(KeyType newKey, ItemType newItem)
{
	int index = hash(newKey);
	Node<KeyType, ItemType>* newNode = new Node<KeyType, ItemType>;
	newNode->key = newKey;
	newNode->item = newItem;
	newNode->next = nullptr;

	if (items[index] == nullptr)
	{
		items[index] = newNode;
	}
	else
	{
		Node<KeyType, ItemType>* current = items[index];
		while (current->next != nullptr)
		{
			if (current->key == newKey)
			{
				current->item = newItem;
				delete newNode;
				return false;
			}
			current = current->next;
		}
		if (current->key == newKey)
		{
			current->item = newItem;
			delete newNode;
			return false;
		}
		current->next = newNode;
	}

	size++;
	return true;
}

template<typename KeyType, typename ItemType>
void HashTable<KeyType, ItemType>::remove(KeyType key)
{
	int index = hash(key);

	if (items[index] == nullptr)
	{
		return;
	}

	Node<KeyType, ItemType>* current = items[index];
	Node<KeyType, ItemType>* previous = nullptr;

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

template<typename KeyType, typename ItemType>
ItemType HashTable<KeyType, ItemType>::get(KeyType key)
{
	int index = hash(key);

	if (items[index] == nullptr)
	{
		return ItemType();
	}

	Node<KeyType, ItemType>* current = items[index];
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

template<typename KeyType, typename ItemType>
bool HashTable<KeyType, ItemType>::isEmpty()
{
	return size == 0;
}

template<typename KeyType, typename ItemType>
int HashTable<KeyType, ItemType>::getLength()
{
	return size;
}

template<typename KeyType, typename ItemType>
void HashTable<KeyType, ItemType>::print(const LinkedList<Restaurant>& restaurants)
{
	// Calculate the padding to center the header
	int totalWidth = 86; // Increased total width to accommodate the restaurant name
	string header = "Food Items Menu";
	int padding = (totalWidth - header.length()) / 2;

	// Print header
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << setw(padding + header.length()) << header << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node<KeyType, ItemType>* current = items[i];
		while (current != nullptr)
		{
			// Get the restaurant name for the current food item
			string restaurantName = current->item.getRestaurantNameByID(current->item.getRestaurantID(), restaurants);

			// Print the FoodItem details along with the restaurant name
			cout << setw(4) << left << current->key << " | "
				<< setw(23) << left << current->item.getName() << " | "
				<< setw(23) << left << restaurantName << " | " // Restaurant name
				<< setw(18) << left << current->item.getCategory() << " | "
				<< "$" << fixed << setprecision(2) << current->item.getPrice() << endl;
			current = current->next;
		}
	}

	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << "Enter your food item number: ";
}
template <typename KeyType, typename ItemType>
void HashTable<KeyType, ItemType>::print(const LinkedList<Restaurant>& restaurants, int restaurantID)
{
	// Calculate the padding to center the header
	int totalWidth = 86; // Increased total width to accommodate the restaurant name
	string header = "Food Items Menu";
	int padding = (totalWidth - header.length()) / 2;

	// Get the restaurant name for the provided restaurant ID
	string restaurantName = "";
	for (int i = 0; i < restaurants.getLength(); i++)
	{
		if (restaurants.retrieve(i).getRestaurantID() == restaurantID)
		{
			restaurantName = restaurants.retrieve(i).getName();
			break;
		}
	}

	// Print the restaurant name in the header
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << setw(padding + header.length()) << header << endl;
	cout << "Restaurant: " << restaurantName << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node<KeyType, ItemType>* current = items[i];
		while (current != nullptr)
		{
			// Print the FoodItem details if it belongs to the specified restaurant
			if (current->item.getRestaurantID() == restaurantID)
			{
				cout << setw(4) << left << current->key << " | "
					<< setw(23) << left << current->item.getName() << " | "
					<< setw(18) << left << current->item.getCategory() << " | "
					<< "$" << fixed << setprecision(2) << current->item.getPrice() << endl;
			}
			current = current->next;
		}
	}

	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << "Enter your food item number: ";
}
template class HashTable<int, FoodItem>;
