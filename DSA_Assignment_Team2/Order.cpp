#include "Order.h"
#include <iostream>
#include <string>

using namespace std;

Order::Order() {}

Order::Order(int id, int c, LinkedList<OrderItem>& o, int r, double p, const string& s)
{
	orderID = id;
	customerID = c;
	orderItemList = o;
	restaurantID = r;
	totalPrice = p;
	status = s;
}

int Order::getOrderID() const
{
	return orderID;
}

int Order::getCustomerID() const
{
	return customerID;
}

LinkedList<OrderItem> Order::getOrderItemList() const
{
	return orderItemList;
}

int Order::getRestaurantID() const
{
	return restaurantID;
}

double Order::getTotalPrice() const
{
	return totalPrice;
}

string Order::getStatus() const
{
	return status;
}





	