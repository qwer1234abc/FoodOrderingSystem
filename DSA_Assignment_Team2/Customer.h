#pragma once
#include <iostream>
#include <string>
#include "HashTable.h"
#include "FoodItem.h"
#include "LinkedList.h"
#include "OrderItem.h"

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

	// Setters
	void setOrderItemsList(const LinkedList<OrderItem>& orderItemsList);

	// Member functions
	void registerCustomer(const string& filename);
	bool customerExists(const string& filename, const string& loginID, const string& password);
	bool uniqueLoginID(const string& filename, const string& loginID);
	bool customerLogin(const string& filename);


	void customerLoginMenu(Customer& customer);
	void customerRegisterMenu(Customer& customer);
	void displayCustomerMenu();  // To show the customer menu after logging in
	HashTable<int, FoodItem> browseFoodItems(const string& foodItemsFile, const LinkedList<Restaurant>& restaurants, int restaurantID); // To browse all food items
	void browseFoodItemsMenu(Customer& customer, Restaurant& restaurant);
	void addOrderItem(FoodItem& foodItem, int quantity);  // To add an item to the order
	void orderFoodItems(Customer& customer, Restaurant& restaurant, int foodItemChoice, HashTable<int, FoodItem>& foodItemsTable);
	int orderItemsMenu(const LinkedList<OrderItem>& orderItemsList, const LinkedList<Restaurant>& restaurants);
	void createOrder(const string& foodItemsFile, const string& ordersFile);  // To create a new order
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