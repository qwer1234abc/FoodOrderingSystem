#include "FoodItem.h"
#include <iostream>
#include <string>

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

