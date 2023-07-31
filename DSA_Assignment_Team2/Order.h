#pragma once
#include <iostream>
#include <string>

using namespace std;

class Order
{
private:
	int orderID;
	int customerID;
	int foodItemID;
	int quantity;
	double totalPrice;
	string status;

public:
	Order();
	Order(int id, int c, int f, int q, double p, const string& s);

	int getOrderID() const;
	int getCustomerID() const;
	int getFoodItemID() const;
	int getQuantity() const;
	double getTotalPrice() const;
	string getStatus() const;
};

