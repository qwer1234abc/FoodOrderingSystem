#pragma once
#include <iostream>
#include <string>
#include "FoodItem.h"
#include "Restaurant.h"
#include "Order.h"
#include "Admin.h"
#include "Notification.h"
#include "Array.h"
#include "GlobalFunctions.h"
using namespace std;

class Customer {
private:
	int customerID;
	string name;
	string loginID;
	string password;
	LinkedList<OrderItem> orderItemsList;

public:
	Customer();
	Customer(int id, const string& n, const string& l, const string& p);

	// Getters
	int getCustomerID() const;
	string getName() const;
	string getLoginID() const;
	string getPassword() const;
	LinkedList<OrderItem> getOrderItemsList() const;
	string getLoginIDByCustomerID(const string& filename, int customerID);

	// Member functions
	bool customerLogin(HashTable<string, Customer>& customersTable, const string& filename);
	void registerCustomer(HashTable<string, Customer>& customersTable, const string& filename);

	HashTable<string, Customer> getAllCustomers(const string& filename);
	void displayCustomerMenu();  // To show the customer menu after logging in
	HashTable<int, FoodItem> browseFoodItems(const string& foodItemsFile, const LinkedList<Restaurant>& restaurants, int restaurantID); // To browse all food items
	void addOrderItem(FoodItem& foodItem, int quantity);  // To add an item to the order
	int orderItemsMenu(const LinkedList<OrderItem>& orderItemsList, const LinkedList<Restaurant>& restaurants);
	void customerLoginMenu(Customer& customer, HashTable<string, Customer>& customersTable, Queue<Order>& orderQueue, Stack<Notification>& notificationStack);
	void customerRegisterMenu(Customer& customer, HashTable<string, Customer>& customersTable);
	void browseFoodItemsMenu(Customer& customer, Restaurant& restaurant, Queue<Order>& customerOrdersQueue);
	bool orderFoodItems(Customer& customer, Restaurant& restaurant, int foodItemChoice, HashTable<int, FoodItem>& foodItemsTable, Queue<Order>& customerOrdersQueue);
	void createOrder(const string& filename, int customerID, LinkedList<OrderItem>& orderItemsList, int restaurantID, long double totalPrice, Queue<Order>& customerOrdersQueue);  // To create a new order
	void cancelOrder(Queue<Order>& customerOrdersQueue);  // To cancel an existing order
	void displayOrders(Queue<Order>& customerOrdersQueue);
	void updateOrderStatusInCSV(const string& filename, int orderIDToCancel, const string& newStatus);
	void displayNotifications(Stack<Notification>& customerNotificationsStack);
};