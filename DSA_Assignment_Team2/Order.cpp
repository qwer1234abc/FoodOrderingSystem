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
	orderItemsList = o;
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
	return orderItemsList;
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
/*
Queue<Order> Order::GetAllOrders(const string& filename)
{
	Queue<Order> orders;
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		cout << "File not found!" << endl;
		return orders;
	}
	else
	{
		string line;
		while (getline(inFile, line))
		{
			istringstream iss(line);
			string field;

			getline(iss, field, ','); // Order ID
			int orderID = stoi(field);

			getline(iss, field, ','); // Customer ID
			int customerID = stoi(field);

			getline(iss, field, ','); // Food Items List
			LinkedList<OrderItem> orderItemsList;
			stringstream foodItemsStream(field);
			string itemString;
			while (getline(foodItemsStream, itemString, '|')) { // Iterate over items
				size_t sepPos = itemString.find(':');
				string foodItemID = itemString.substr(0, sepPos);
				int quantity = stoi(itemString.substr(sepPos + 1));

				FoodItem foodItem = getFoodItemByName(foodItemID);

				OrderItem orderItem(foodItem, quantity); 
				orderItemsList.insert(orderItem);
			}

			getline(iss, field, ','); // Restaurant ID
			int restaurantID = stoi(field);

			getline(iss, field, ','); // Total Price
			double totalPrice = stod(field);

			getline(iss, field, ','); // Order Status
			string status = field;

			Order order(orderID, customerID, orderItemsList, restaurantID, totalPrice, status);

			orders.enqueue(order);
		}
	}
	return orders;
}

Queue<Order> Order::filterCustomerOrders(const Queue<Order>& allOrders, int targetCustomerID) {
	Queue<Order> filteredQueue;

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) {
		if (currentOrder.getCustomerID() == targetCustomerID) {
			filteredQueue.enqueue(currentOrder);
		}
	}

	return filteredQueue;
}

Queue<Order> Order::filterRestaurantOrders(const Queue<Order>& allOrders, int targetRestaurantID) {
	Queue<Order> filteredQueue;

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) {
		if (currentOrder.getRestaurantID() == targetRestaurantID) {
			filteredQueue.enqueue(currentOrder);
		}
	}

	return filteredQueue;
}

*/

string Order::orderItemsListToString(const LinkedList<OrderItem>&orderItems) {
	string result;
	for (int i = 0; i < orderItems.getLength(); ++i) {
		OrderItem item = orderItems.retrieve(i);
		result += to_string(item.getFoodItem().getFoodItemID()) + ":" + to_string(item.getQuantity());
		if (i < orderItems.getLength() - 1) {
			result += "|"; // Separator for different items
		}
	}
	return result;
}
