#pragma once
#include <iostream>
#include <string>
#include "OrderItem.h"
#include "LinkedList.h"
#include "Queue.h"

using namespace std;

class Order
{
private:
	int orderID;
	int customerID;
	LinkedList<OrderItem> orderItemList;
	int restaurantID;
	double totalPrice;
	string status;

public:
	Order();
	Order(int id, int c, LinkedList<OrderItem>& o, int r, double p, const string& s);

	int getOrderID() const;
	int getCustomerID() const;
	LinkedList<OrderItem> getOrderItemList() const;
	int getRestaurantID() const;
	double getTotalPrice() const;
	string getStatus() const;
	Queue<Order> GetIncomingOrders(const string& orderFileName);
	bool UpdateStatus(int orderID);
};

