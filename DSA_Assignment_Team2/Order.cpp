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

void Order::setStatus(const string& status)
{
	this->status = status;
}

Queue<Order> Order::getAllOrders(const string& filename, HashTable<int, FoodItem>& foodItemsTable)
{
	Queue<Order> orders;
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		cout << "File not found!" << endl;
		return orders;
	}
	string header;
	getline(inFile, header);

	string line;
	while (getline(inFile, line))
	{
		istringstream iss(line);
		string orderIDStr, customerIDStr, orderItemsListStr, restaurantIDStr, totalPriceStr, statusStr;

		getline(iss, orderIDStr, ','); // Order ID
		getline(iss, customerIDStr, ','); // Customer ID
		getline(iss, orderItemsListStr, ','); // Order Items List

		LinkedList<OrderItem> orderItemsList;
		stringstream foodItemsStream(orderItemsListStr);
		string itemString;
		while (getline(foodItemsStream, itemString, '|')) { // Iterate over items
			size_t sepPos = itemString.find(':');
			string foodItemID = itemString.substr(0, sepPos);
			int quantity = stoi(itemString.substr(sepPos + 1));

			FoodItem foodItem = foodItemsTable.get(stoi(foodItemID));

			OrderItem orderItem(foodItem, quantity);
			orderItemsList.insert(orderItem);
		}

		getline(iss, restaurantIDStr, ','); // Restaurant ID
		getline(iss, totalPriceStr, ','); // Total Price
		getline(iss, statusStr, ','); // Status

		int orderID = stoi(orderIDStr);
		int customerID = stoi(customerIDStr);
		int restaurantID = stoi(restaurantIDStr);
		double totalPrice = stod(totalPriceStr);
		string status = statusStr;
		LinkedList<OrderItem> orderItemsListCopy = orderItemsList;
		Order order(orderID, customerID, orderItemsListCopy, restaurantID, totalPrice, status);

		orders.enqueue(order);
	}
	return orders;
}

Queue<Order> Order::filterCustomerOrders(Queue<Order>& allOrders, int targetCustomerID) {
	Queue<Order> filteredQueue;

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) {
		if (currentOrder.getCustomerID() == targetCustomerID) {
			filteredQueue.enqueue(currentOrder);
		}
	}

	return filteredQueue;
}

Queue<Order> Order::filterUnPreparedCustomerOrders(Queue<Order>& customerOrders) {
	Queue<Order> filteredQueue;
	Queue<Order> tempQueue; // Temporary queue to store orders

	Order currentOrder;
	while (customerOrders.dequeue(currentOrder)) {
		if (currentOrder.getStatus() == "Not Prepared") {
			filteredQueue.enqueue(currentOrder);
		}
		tempQueue.enqueue(currentOrder); // Store the order in the temporary queue
	}

	// Re-queue the orders back to the original queue
	while (!tempQueue.isEmpty()) {
		Order order;
		tempQueue.dequeue(order);
		customerOrders.enqueue(order);
	}

	return filteredQueue;
}


Queue<Order> Order::filterRestaurantOrders(Queue<Order>& allOrders, int targetRestaurantID) {
	Queue<Order> filteredQueue;

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) {
		if (currentOrder.getRestaurantID() == targetRestaurantID) {
			filteredQueue.enqueue(currentOrder);
		}
	}

	return filteredQueue;
}

string Order::orderItemsListToString(const LinkedList<OrderItem>& orderItems) {
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
