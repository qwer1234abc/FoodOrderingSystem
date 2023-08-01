#include "Restaurant.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

Restaurant::Restaurant() {}

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

LinkedList<Restaurant> Restaurant::getAllRestaurants(const string& filename)
{
	LinkedList<Restaurant> restaurantList;
	ifstream file(filename); // create  input file stream object called "file" and opens the file
	if (!file.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return restaurantList;
	}

	string header;
	getline(file, header); // read the first line of the file and store it in the variable "header"

	string line;
	while (getline(file, line))
	{
		istringstream iss(line); // extract comma-separated values from each line
		string restaurantIDFromFile, nameFromFile;
		getline(iss, restaurantIDFromFile, ',');
		getline(iss, nameFromFile, ',');

		Restaurant restaurant(stoi(restaurantIDFromFile), nameFromFile);
		restaurantList.insert(restaurant);
	}

	file.close();

	return restaurantList;
}

