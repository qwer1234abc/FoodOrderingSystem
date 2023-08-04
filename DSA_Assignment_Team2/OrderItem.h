#pragma once
#include <iostream>
#include <string>
#include "FoodItem.h"

using namespace std;

class OrderItem
{
private:
	FoodItem fooditem;
	int quantity;

public:
	OrderItem();
	OrderItem(FoodItem f, int q);

	FoodItem getFoodItem() const;
	int getQuantity() const;
	string getNameAndQuantity() const;
};

