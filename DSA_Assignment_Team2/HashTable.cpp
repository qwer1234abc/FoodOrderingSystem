#include "Customer.h"
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
int HashTable<KeyType, ItemType>::hash(int key)
{
	return key % MAX_SIZE; // Simple hash function using the FoodItem's ID
}

template<typename KeyType, typename ItemType>
int HashTable<KeyType, ItemType>::hash(const string& key)
{
	const int PRIME = 31; // A prime number to use in the hash calculation
	long long int hashValue = 0;

	for (size_t i = 0; i < key.length(); i++)
	{
		int charVal;
		if (isalpha(key[i]))
		{
			charVal = (isupper(key[i])) ? (int)key[i] - (int)'A' + 10 : (int)key[i] - (int)'a' + 36;
		}
		else if (isdigit(key[i]))
		{
			charVal = (int)key[i] - (int)'0';
		}
		else
		{
			charVal = -1;
		}

		if (charVal != -1)
		{
			hashValue = hashValue * PRIME + charVal;
		}
	}

	int index = hashValue % MAX_SIZE;
	if (index < 0)
	{
		index += MAX_SIZE;
	}

	return index;
}

// Other member function implementations remain the same, but now work with FoodItem objects
template<typename KeyType, typename ItemType>
bool HashTable<KeyType, ItemType>::add(KeyType newKey, ItemType newItem)
{
	long long int index = hash(newKey);
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
	long long int index = hash(key);

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
	long long int index = hash(key);

	if (items[index] == nullptr)
	{
		return ItemType();
	}
	else
	{
		Node<KeyType, ItemType>* current = items[index];
		while (current != nullptr)
		{
			if (current->key == key)
			{
				return current->item;
			}
			current = current->next;
		}
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

void HashTable<int, FoodItem>::print(const LinkedList<Restaurant>& restaurants)
{
	// Calculate the padding to center the header
	int totalWidth = 95; // Increased total width to accommodate the restaurant name
	string header = "Food Items Menu";

	string dashes(totalWidth, '=');

	int spacesOnEachSide = (totalWidth - header.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + header;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	Array tempFoodItemArray(size);

	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node<int, FoodItem>* current = items[i];
		while (current != nullptr)
		{
			tempFoodItemArray.insert(current->item);
			current = current->next;
		}
	}

	tempFoodItemArray.quickSort(0, tempFoodItemArray.getLength() - 1);

	for (int i = 0; i < tempFoodItemArray.getLength(); i++)
	{
		FoodItem current = tempFoodItemArray.retrieve(i);
		string restaurantName = current.getRestaurantNameByID(current.getRestaurantID(), restaurants);
		cout << setw(4) << left << i + 1 << " | "
			<< setw(30) << left << current.getName() << " | "
			<< setw(23) << left << restaurantName << " | " // Restaurant name
			<< setw(18) << left << current.getCategory() << " | "
			<< "$" << fixed << setprecision(2) << current.getPrice() << endl;
	}

	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << "Enter your food item number: ";
}

void HashTable<int, FoodItem>::print(const LinkedList<Restaurant>& restaurants, int restaurantID)
{
	// Calculate the padding to center the header
	int totalWidth = 74; // Increased total width to accommodate the restaurant name
	string dashes(totalWidth, '=');


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

	int spacesOnEachSide = (totalWidth - restaurantName.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + restaurantName;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	Array tempFoodItemArray(size);

	for (int i = 0; i < MAX_SIZE; i++)
	{
		Node<int, FoodItem>* current = items[i];
		while (current != nullptr)
		{
			tempFoodItemArray.insert(current->item);
			current = current->next;
		}
	}

	tempFoodItemArray.quickSort(0, tempFoodItemArray.getLength() - 1);

	for (int i = 0; i < tempFoodItemArray.getLength(); i++)
	{
		FoodItem current = tempFoodItemArray.retrieve(i);
		if (current.getRestaurantID() == restaurantID)
		{
			cout << setw(4) << left << i + 1 << " | "
				<< setw(30) << left << current.getName() << " | "
				<< setw(23) << left << current.getCategory() << " | "
				<< "$" << fixed << setprecision(2) << current.getPrice() << endl;
		}
	}

	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << "Enter your food item number: ";
}

template class HashTable<int, FoodItem>;
template class HashTable<string, Customer>;
template class HashTable<string, Admin>;
