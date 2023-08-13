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

// Returns a queue with all the orders
Queue<Order> Order::getAllOrders(const string& filename, HashTable<int, FoodItem>& foodItemsTable) {
	Queue<Order> orders;
	ifstream inFile(filename); // Create an input file stream object named file and opens the file
	if (!inFile.is_open())
	{
		cout << "File not found!" << endl;
		return orders;
	}
	string header;
	getline(inFile, header); // Read header (to skip)

	string line;
	while (getline(inFile, line)) // Loop through all the lines in the file 
	{
		istringstream iss(line); // Extract comma-separated values from each line
		string orderIDStr, customerIDStr, orderItemsListStr, restaurantIDStr, totalPriceStr, statusStr;

		getline(iss, orderIDStr, ','); // Order ID
		getline(iss, customerIDStr, ','); // Customer ID
		getline(iss, orderItemsListStr, ','); // Order Items List

		LinkedList<OrderItem> orderItemsList; // Create linked list called orderItemsList
		stringstream foodItemsStream(orderItemsListStr); // Creates a string stream to process orderItemsListStr, which contains food item details
		string itemString; // Store each food item detail
		while (getline(foodItemsStream, itemString, '|')) { // // Read from "foodItemsStream" until it encounters the delimiter "|", itemString is where the extracted content will be stored
			size_t sepPos = itemString.find(':'); // Find the position of the ":" to separate the food item ID from the quantity
			string foodItemID = itemString.substr(0, sepPos); // Extract the food item ID from itemString
			int quantity = stoi(itemString.substr(sepPos + 1)); // Extract quantity from itemString and convert it to integer

			FoodItem foodItem = foodItemsTable.get(stoi(foodItemID)); // Retrieve the FoodItem object from the hash table based on the extracted food item ID

			OrderItem orderItem(foodItem, quantity); // Create an orderItem using the retrieved FoodItem object and its extracted quantity
			orderItemsList.insert(orderItem); // Insert the OrderItem object inot the linked list created above
		}

		getline(iss, restaurantIDStr, ','); // Restaurant ID
		getline(iss, totalPriceStr, ','); // Total Price
		getline(iss, statusStr, ','); // Status

		int orderID = stoi(orderIDStr);
		int customerID = stoi(customerIDStr);
		int restaurantID = stoi(restaurantIDStr);
		double totalPrice = stod(totalPriceStr);
		string status = statusStr;
		// Since the list is linked by pointers, any changes made to this list will be reflected in all objects that reference it (maintain the integrity of the data)
		LinkedList<OrderItem> orderItemsListCopy = orderItemsList; // Create a copy of the OrderItemsList to preserve the original list
		Order order(orderID, customerID, orderItemsListCopy, restaurantID, totalPrice, status); // Create a new Order object

		orders.enqueue(order); // Add the newly created Order object into the queue
	}
	return orders;
}

// Returns a queue with customer orders based on the customer's ID
Queue<Order> Order::filterCustomerOrders(Queue<Order>& allOrders, int targetCustomerID) {
	Queue<Order> filteredQueue;
	Queue<Order> tempQueue; // Temporary queue to store orders

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) {
		if (currentOrder.getCustomerID() == targetCustomerID) {
			filteredQueue.enqueue(currentOrder);
		}
	}

	// Re-queue the orders back to the original queue
	while (!tempQueue.isEmpty()) {
		Order order;
		tempQueue.dequeue(order);
		allOrders.enqueue(order);
	}

	return filteredQueue;
}

// Return a queue that gets unpreapred orders for a customer
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

// Return a queue of orders for an admin that has status set to "Not Prepared" and "Preparing"
Queue<Order> Order::filterRestaurantIncomingOrders(Queue<Order>& allOrders, int targetRestaurantID) {
	Queue<Order> filteredQueue; // Queue that will be returned
	Queue<Order> tempQueue; // Temporary queue to store orders

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) { // Loop through all the ordes in the queue
		if (currentOrder.getRestaurantID() == targetRestaurantID && (currentOrder.getStatus() == "Not Prepared" || currentOrder.getStatus() == "Preparing")) { // Check if status is "Not Prepared" or "Preparing" and if the restaurant ID matches with that of the admin
			filteredQueue.enqueue(currentOrder);  // Add to filteredQueue if status is "Not Preapred" or "Preparing" and the restaurant ID matches with that of the admin
		}
		tempQueue.enqueue(currentOrder); // Store the order in the temporary queue
	}

	// Re-queue the orders back to the original queue
	while (!tempQueue.isEmpty()) { // Loop through temporary queue
		Order order;
		tempQueue.dequeue(order); // Remove the orders from temporary queue
		allOrders.enqueue(order); // Add the orders back into the original queue
	}

	return filteredQueue;
}

// Return a filtered queue of orders for an admin which status is NOT "Cancelled"
Queue<Order> Order::filterRestaurantRevenueOrders(Queue<Order>& allOrders, int targetRestaurantID)
{
	Queue<Order> filteredQueue; // Queue that will be returned
	Queue<Order> tempQueue; // Temporary queue to store orders

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) {
		if (currentOrder.getStatus() != "Cancelled" && currentOrder.getRestaurantID() == targetRestaurantID) { // Check if status is NOT "Cancelled" and if the restaurant ID matches with that of the admin
			filteredQueue.enqueue(currentOrder); // Add to filteredQueue if status is NOT "Cancelled" and the restaurant ID matches with that of the admin
		}
		tempQueue.enqueue(currentOrder); // Store the order in the temporary queue
	}

	// Re-queue the orders back to the original queue
	while (!tempQueue.isEmpty()) { // Loop through temporary queue
		Order order;
		tempQueue.dequeue(order); // Remove the orders from temporary queue
		allOrders.enqueue(order); // Add the orders back into the original queue
	}

	return filteredQueue;
}

// Returns a queue baed on the customer ID
Queue<Order> Order::filterRestaurantSpecificCustomerOrders(Queue<Order>& allOrders, int targetRestaurantID, int targetCustomerID) {
	Queue<Order> filteredQueue; // Queue that will be returned
	Queue<Order> tempQueue; // Temporary queue to store orders

	Order currentOrder;
	while (allOrders.dequeue(currentOrder)) { // Loop through all the orders in the queue
		if (currentOrder.getRestaurantID() == targetRestaurantID && currentOrder.getCustomerID() == targetCustomerID) { // Check if restaurant ID is the same as the one the admin has and that the customerID is the same as the one the customer has
			filteredQueue.enqueue(currentOrder); // Add the orders into the queue if the conditions above are met
		}
		tempQueue.enqueue(currentOrder); // Store the order in the temporary queue
	}

	// Re-queue the orders back to the original queue
	while (!tempQueue.isEmpty()) { // Loop through the temporary queue
		Order order;
		tempQueue.dequeue(order); // Remove the orders from temporary queue
		allOrders.enqueue(order); // Add the orders back into the original queue
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
