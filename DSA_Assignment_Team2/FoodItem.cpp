#include "FoodItem.h"
#include <iostream>
#include <string>
#include "Restaurant.h"
#include "LinkedList.h"

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