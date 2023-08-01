#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Restaurant.h"

using namespace std;

class FoodItem
{
private:
	int foodItemID;
	string name;
	string category;
	double price;
	int restaurantID;

public:
	FoodItem();
	FoodItem(int id, const string& n, const string& d, double p, int r);

	int getFoodItemID() const;
	string getName() const;
	string getCategory() const;
	double getPrice() const;
	int getRestaurantID() const;
	string getRestaurantNameByID(int id, const LinkedList<Restaurant>& restaurants);
};

