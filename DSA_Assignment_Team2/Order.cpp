#include "Order.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream> 

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

Queue Order::GetIncomingOrders(const string& orderFileName) {
	Queue queue;

	ifstream file(orderFileName);
	if (file.is_open()) {
		string header;
		getline(file, header);

		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			string orderIDStr, customerIDStr, foodItemIDStr, restaurantIDStr, orderStatusStr, totalPriceStr;

			getline(iss, orderIDStr, ',');
			getline(iss, customerIDStr, ',');
			getline(iss, foodItemIDStr, ',');
			getline(iss, restaurantIDStr, ',');
			getline(iss, orderStatusStr, ',');
			getline(iss, totalPriceStr, ',');

			if (orderStatusStr != "Prepared") {
				orderID = stoi(orderIDStr);
				customerID = stoi(customerIDStr);
				// how to use the linkedlist?
				restaurantID = stoi(restaurantIDStr);
				status = orderStatusStr;
				totalPrice = stod(totalPriceStr);
			}

		}
	}
	return queue;
}




	