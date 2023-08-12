// Member's name: Beh Jueen Hao Kelvin, Lim Yih Chern Xavier
// Student ID: S10244263E, S10242016G
// Team: 2
#include <iostream>
#include "Customer.h"
#include "Admin.h"

using namespace std;

void displayMainMenu();

void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

void waitForEnterKey() {
	cout << "Press Enter to continue...";
	cin.ignore(); // Ignore any leftover newline characters in the input buffer
	cin.get();    // Wait for the user to press Enter before continuing
}

int main()
{
	Customer customer;
	HashTable<string, Customer> customerTable = customer.getAllCustomers("Customers.csv"); // Get all customers
	Admin admin;
	HashTable<string, Admin> adminTable = admin.getAllAdmins("Admins.csv"); // Get all admins
	FoodItem fooditem;
	HashTable<int, FoodItem> foodItemsTable = fooditem.getAllFoodItems("FoodItems.csv"); // Get all food items
	Order order;
	Notification notification;
	Stack<Notification> notificationStack = notification.getAllNotifications("Notifications.csv"); // Get all notifications

	string selectedOptionStr;

	do {
		Queue<Order> orderQueue = order.getAllOrders("Orders.csv", foodItemsTable);
		displayMainMenu();
		cin >> selectedOptionStr;

		if (selectedOptionStr == "1") {
			customer.customerLoginMenu(customer, customerTable, orderQueue, notificationStack);
		}
		else if (selectedOptionStr == "2") {
			customer.customerRegisterMenu(customer, customerTable);
		}
		else if (selectedOptionStr == "3") {
			admin.adminLoginMenu(admin, adminTable, orderQueue, notificationStack);
		}
		else if (selectedOptionStr == "4") {
			cout << "\nThank you for using our app. Goodbye!" << endl;
		}
		else {
			cout << "\nInvalid option. Please try again." << endl;
		}
		waitForEnterKey();

	} while (selectedOptionStr != "4");
}

void displayMainMenu() {
	clearScreen();
	cout << "==================================" << endl;
	cout << "        WELCOME TO OUR APP        " << endl;
	cout << "==================================" << endl;
	cout << "1. Customer Login" << endl;
	cout << "2. Customer Register" << endl;
	cout << "3. Admin Login" << endl;
	cout << "4. Exit" << endl;
	cout << "==================================" << endl;
	cout << "Enter your choice: ";
}
