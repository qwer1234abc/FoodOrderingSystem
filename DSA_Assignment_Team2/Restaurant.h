#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

class Restaurant
{
private:
	int restaurantID;
	string name;

public:
	Restaurant();
	Restaurant(int id, const string& n);

	int getRestaurantID() const;
	string getName() const;
	LinkedList<Restaurant> getAllRestaurants(const string& filename);
};

