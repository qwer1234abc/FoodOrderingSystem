#pragma once
#include <iostream>
#include <string>

using namespace std;

class FoodItem
{
private:
	int foodItemID;
	string name;
	string description;
	double price;
	int restaurantID;

public:
	FoodItem();
	FoodItem(int id, const string& n, const string& d, double p, int r);

	int getFoodItemID() const;
	string getName() const;
	string getDescription() const;
	double getPrice() const;
	int getRestaurantID() const;

};

