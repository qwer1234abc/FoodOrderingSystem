#pragma once
#include <iostream>
#include <string>
#include "OrderItem.h"
#include "LinkedList.h"

using namespace std;

class Order
{
private:
	int orderID;
	int customerID;
	LinkedList orderItemList;
	int restaurantID;
	double totalPrice;
	string status;

public:
	Order();
	Order(int id, int c, int f, int r, double p, const string& s);

	int getOrderID() const;
	int getCustomerID() const;
	int getFoodItemID() const;
	int getRestaurantID() const;
	double getTotalPrice() const;
	string getStatus() const;
};

