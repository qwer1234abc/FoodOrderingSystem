#pragma once
#include <iostream>
#include <string>
#include "FoodItem.h"
#include "Restaurant.h"
#include "Order.h"

using namespace std;

class Customer {
private:
	int customerID;
	string name;
	string loginID;
	string password;
	int loyaltyPoints;
	LinkedList<OrderItem> orderItemsList;

public:
	Customer();
	Customer(int id, const string& n, const string& l, const string& p, int lp);

	// Getters
	int getCustomerID() const;
	string getName() const;
	string getLoginID() const;
	string getPassword() const;
	int getLoyaltyPoints() const;
	LinkedList<OrderItem> getOrderItemsList() const;

	// Member functions
	bool customerLogin(HashTable<string, Customer>& customersTable, const string& filename);
	void registerCustomer(HashTable<string, Customer>& customersTable, const string& filename);

	HashTable<string, Customer> getAllCustomers(const string& filename);
	void displayCustomerMenu();  // To show the customer menu after logging in
	HashTable<int, FoodItem> browseFoodItems(const string& foodItemsFile, const LinkedList<Restaurant>& restaurants, int restaurantID); // To browse all food items
	void addOrderItem(FoodItem& foodItem, int quantity);  // To add an item to the order
	int orderItemsMenu(const LinkedList<OrderItem>& orderItemsList, const LinkedList<Restaurant>& restaurants);
	void customerLoginMenu(Customer& customer, HashTable<string, Customer>& customersTable);
	void customerRegisterMenu(Customer& customer, HashTable<string, Customer>& customersTable);
	void browseFoodItemsMenu(Customer& customer, Restaurant& restaurant);
	bool orderFoodItems(Customer& customer, Restaurant& restaurant, int foodItemChoice, HashTable<int, FoodItem>& foodItemsTable);
	void createOrder(const string& ordersFile, int customerID, LinkedList<OrderItem>& orderItemsList, int restaurantID, long double totalPrice);  // To create a new order
	void cancelOrder(const string& ordersFile);  // To cancel an existing order
	void redeemPoints();

	void clearScreen() {
		cout << "\033[2J\033[1;1H";
	}

	void waitForEnterKey() {
		cout << "Press Enter to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
	}
};