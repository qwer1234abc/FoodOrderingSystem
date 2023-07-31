#include "OrderItem.h"
#include <iostream>

using namespace std;

OrderItem::OrderItem() {}

OrderItem::OrderItem(FoodItem f, int q)
{
	fooditem = f;
	quantity = q;
}

FoodItem OrderItem::getFoodItem() const
{
	return fooditem;
}

int OrderItem::getQuantity() const
{
	return quantity;
}

