#include "Restaurant.h"
#include <iostream>
#include <string>

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


