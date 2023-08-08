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
	LinkedList<OrderItem> orderItemsList;
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

	void setStatus(const string& status);
	string getStatus() const;
	string orderItemsListToString(const LinkedList<OrderItem>& orderItems);
	Queue<Order> getAllOrders(const string& filename, HashTable<int, FoodItem>& foodItemsTable);
	Queue<Order> filterCustomerOrders(Queue<Order>& orders, int customerID);
	Queue<Order> filterUnPreparedCustomerOrders(Queue<Order>& customerOrders);
	Queue<Order> filterRestaurantIncomingOrders(Queue<Order>& orders, int restaurantID);
	Queue<Order> filterRestaurantSpecificCustomerOrders(Queue<Order>& allOrders, int targetRestaurantID, int targetCustomerID);
};

