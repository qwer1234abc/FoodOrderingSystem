#include "FoodItem.h"
#include <fstream>
#include <sstream> 

using namespace std;

FoodItem::FoodItem() {}

FoodItem::FoodItem(int id, const string& n, const string& d, double p, int r)
{
	foodItemID = id;
	name = n;
	category = d;
	price = p;
	restaurantID = r;
}

int FoodItem::getFoodItemID() const
{
	return foodItemID;
}

string FoodItem::getName() const
{
	return name;
}

string FoodItem::getCategory() const
{
	return category;
}

double FoodItem::getPrice() const
{
	return price;
}

int FoodItem::getRestaurantID() const
{
	return restaurantID;	
}

string FoodItem::getRestaurantNameByID(int restaurantID, const LinkedList<Restaurant>& restaurants) {
	Restaurant restaurant;
	for (int i = 0; i < restaurants.getLength(); i++) {
		if (restaurants.retrieve(i, restaurant)) {
			if (restaurant.getRestaurantID() == restaurantID) {
				return restaurant.getName();
			}
		}
	}
	return "N.A";
}

HashTable<int, FoodItem> FoodItem::getAllFoodItems(const string& filename)
{
	// Read food items from the CSV file and store them in the hashtable
	HashTable<int, FoodItem> foodItemsTable; // create a foodItemsTable hash table
	ifstream foodOptionsfile(filename);  // input file named "FoodOptionsFile" created and initiated with "foodItemsFile" file
	if (!foodOptionsfile.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return foodItemsTable; // Return an empty table as there are no food items read
	}

	// Skip the header line
	string header;
	getline(foodOptionsfile, header);

	string line;
	int key = 1;
	while (getline(foodOptionsfile, line)) // read the lines in the file
	{
		istringstream iss(line); // extract comma-separated values from each line
		string foodItemIDStr, name, category, restaurantIDStr, priceStr;

		// Read each field from the CSV line, separated by commas
		getline(iss, foodItemIDStr, ',');
		getline(iss, name, ',');
		getline(iss, category, ',');
		getline(iss, restaurantIDStr, ',');
		getline(iss, priceStr, ',');

		// Convert the read data to appropriate data types
		int foodItemID = stoi(foodItemIDStr);
		double price = stod(priceStr);
		int restaurantIDFromFile = stoi(restaurantIDStr);

		// Check if the restaurant ID is provided and skip items from other restaurants
		if (restaurantID != -1 && restaurantID != restaurantIDFromFile)
		{
			continue;
		}

		// Create a FoodItem object
		FoodItem foodItem(foodItemID, name, category, price, restaurantIDFromFile);

		// Add the FoodItem object to the hashtable, with the id as the key and the food item as the value
		foodItemsTable.add(key, foodItem);
		key++;
	}

	foodOptionsfile.close();
}
