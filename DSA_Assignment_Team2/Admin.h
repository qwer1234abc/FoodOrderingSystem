#pragma once
#include <iostream>
#include <string>
#include "Order.h"
#include "Customer.h"
#include "Notification.h"
using namespace std;

class Admin
{
private:
	int adminID;
	string name;
	string loginID;
	string password;
	int restaurantID;
public:
	Admin();
	Admin(int id, const string& n, const string& l, const string& p, int r);

	int getAdminID() const;
	string getName() const;
	string getLoginID() const;
	string getPassword() const;
	int getRestaurantID() const;
	
	HashTable<string, Admin> getAllAdmins(const string& filename);
	bool adminLogin(HashTable<string, Admin>& adminTable, const string& filename);
	void displayAdminMenu();
	void adminLoginMenu(Admin& admin, HashTable<string, Admin>& adminTable, Queue<Order>& orderQueue, Stack<Notification>& notificationStack);
	void displayIncomingOrder(Queue<Order>& restaurantOrdersQueue);
	void updateOrderStatus(Queue<Order>& restaurantOrdersQueue, Stack<Notification>& notificationStack, Queue<Order>& allOrdersQueue);
	void updateOrderStatusInCSV(const string& filename, int orderIDToUpdate, const string& newStatus);
	void viewCustomerInformationForOrder(Queue<Order>& restaurantOrdersQueue, Queue<Order>& allOrders, int restaurantID);
	void insertNotificationInCSV(const string& filename, Notification& newNotification);
	void viewFoodItemsRevenue(Queue<Order>& restaurantOrdersQueue);

	void clearScreen() {
		cout << "\033[2J\033[1;1H";
	}

	void waitForEnterKey() {
		cout << "Press Enter to continue...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
	}
};

