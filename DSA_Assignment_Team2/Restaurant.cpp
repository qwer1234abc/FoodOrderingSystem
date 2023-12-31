#include "Restaurant.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Restaurant::Restaurant()
{
	restaurantID = -1;
	name = "";
}

Restaurant::Restaurant(int id, const string& n)
{
	restaurantID = id;
	name = n;
}

int Restaurant::getRestaurantID() const
{
	return restaurantID;
}

string Restaurant::getName() const
{
	return name;
}

void Restaurant::setRestaurantID(int id)
{
	restaurantID = id;
}

void Restaurant::setName(const string& n)
{
	name = n;
}

LinkedList<Restaurant> Restaurant::getAllRestaurants(const string& filename)
{
	LinkedList<Restaurant> restaurantList; // create a list of restaurant type
	ifstream file(filename); // create  input file stream object called "file" and opens the file
	if (!file.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return restaurantList;
	}

	string header;
	getline(file, header); // read the first line of the file and store it in the variable "header"

	string line;
	while (getline(file, line)) // read each ine in the file
	{
		istringstream iss(line); // extract comma-separated values from each line
		string restaurantIDFromFile, nameFromFile; 
		getline(iss, restaurantIDFromFile, ',');
		getline(iss, nameFromFile, ',');

		// create a new restaurant object
		Restaurant restaurant(stoi(restaurantIDFromFile), nameFromFile);
		restaurantList.insert(restaurant); // add restaurant to restaurant list
	}

	file.close();

	return restaurantList;
}

string Restaurant::getNameByID(int id, LinkedList<Restaurant>& restaurantList)
{
	for (int i = 0; i < restaurantList.getLength(); i++)
	{
		if (restaurantList.retrieve(i).getRestaurantID() == id)
		{
			return restaurantList.retrieve(i).getName();
		}
	}

	return "";
}