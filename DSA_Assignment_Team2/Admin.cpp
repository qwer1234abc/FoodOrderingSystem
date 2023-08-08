#include "Admin.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream> 

using namespace std;

Admin::Admin() {}

Admin::Admin(int id, const string& n, const string& l, const string& p, int r) {
	adminID = id;
	name = n;
	loginID = l;
	password = p;
	restaurantID = r;
}

int Admin::getAdminID() const {
	return adminID;
}

string Admin::getName() const {
	return name;
}

string Admin::getLoginID() const {
	return loginID;
}

string Admin::getPassword() const {
	return password;
}

int Admin::getRestaurantID() const {
	return restaurantID;
}

HashTable<string, Admin> Admin::getAllAdmins(const string& filename)
{
	HashTable <string, Admin> adminsTable;
	ifstream file(filename); // create input file stream object named file and opens the file

	if (!file.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return adminsTable;
	}

	string header;
	getline(file, header); // read the first line of the file and store it in the variable "header"

	string line;
	while (getline(file, line))
	{
		istringstream iss(line); // extract comma-separated values from each line
		string adminIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile, restaurantIDFromFile;
		getline(iss, adminIDFromFile, ',');
		getline(iss, nameFromFile, ',');
		getline(iss, loginIDFromFile, ',');
		getline(iss, passwordFromFile, ',');
		getline(iss, restaurantIDFromFile, ',');

		string lowercaseLoginIDFromFile = loginIDFromFile;

		for (char& c : lowercaseLoginIDFromFile) { // convert all the characters in the file to lowercase
			c = tolower(c);
		}

		Admin admin(stoi(adminIDFromFile), nameFromFile, lowercaseLoginIDFromFile, passwordFromFile, stoi(restaurantIDFromFile));
		adminsTable.add(lowercaseLoginIDFromFile, admin);
	}

	file.close();

	return adminsTable;
}

bool Admin::adminLogin(HashTable<string, Admin>& adminTable, const string& filename) {
	string loginID, password;
	cout << "Enter your login credentials:\n";
	cout << "Login ID: ";
	cin >> ws;
	getline(cin, loginID);
	if (loginID.length() > 20) {
		cout << "Error: Login ID must not exceed 20 characters.\n";
		return false; // Return false because login is not successful
	}
	cout << "Password: ";
	cin >> ws;
	getline(cin, password);

	string lowercaseLoginID = loginID;

	for (char& c : lowercaseLoginID) { // convert all the characters in the file to lowercase
		c = tolower(c);
	}

	Admin admin = adminTable.get(lowercaseLoginID);

	if (admin.getAdminID() != 0 && admin.getLoginID() == lowercaseLoginID && admin.getPassword() == password) {
		adminID = admin.getAdminID();
		name = admin.getName();
		restaurantID = admin.getRestaurantID();
		cout << "Login successful!\n" << endl;
		return true;
	}
	else if (admin.getAdminID() == 0) {
		cout << "Admin with this Login ID does not exist. Please try again.\n";
	}
	else {
		cout << "Incorrect Login ID or password. Please try again.\n";
	}
	return false;
}

void Admin::displayAdminMenu() {
	cout << "Welcome " << name << ", " << "here is the admin menu:" << endl;
	cout << "====================================" << endl;
	cout << "             Admin Menu            " << endl;
	cout << "====================================" << endl;
	cout << "1. View Incoming Orders" << endl;
	cout << "2. Update Status of Orders" << endl;
	cout << "3. View Customer Information" << endl;
	cout << "4. Log out" << endl;
	cout << "====================================" << endl;
	cout << "Enter your choice: ";
}

void Admin::adminLoginMenu(Admin& admin, HashTable<string, Admin>& adminTable, Queue<Order>& orderQueue)
{
	cout << "\n-------------------------" << endl;
	cout << "       Admin Login        " << endl;
	cout << "-------------------------" << endl;
	if (admin.adminLogin(adminTable, "Admins.csv")) {
		// Filter the order queue to only display the restaurant's orders
		Order order;
		Queue<Order> restaurantOrdersQueue = order.filterRestaurantOrders(orderQueue, admin.getRestaurantID());
		waitForEnterKey();
		clearScreen();
		string adminOptionStr;
		do {
			admin.displayIncomingOrder(restaurantOrdersQueue);

			cin >> adminOptionStr;
		} while (adminOptionStr != "4");
	}
}

void Admin::displayIncomingOrder(Queue<Order>& restaurantOrdersQueue)
{
	if (restaurantOrdersQueue.isEmpty()) {
		cout << "There are no incoming orders." << endl;
		waitForEnterKey();
		clearScreen();
		return;
	}

	Queue<Order> tempQueue; // Temporary queue to store the orders

	cout << "\nIncoming Orders:" << endl;
	cout << string(80, '=') << endl; // Using string constructor to generate dashes

	// Display headers
	cout << left << setw(10) << "Order ID" << setw(30) << "Food Item" << setw(10) << "Quantity"
		<< setw(15) << "Status" << setw(15) << "Total Price" << endl;
	cout << string(80, '-') << endl;

	while (!restaurantOrdersQueue.isEmpty())
	{
		Order order;
		restaurantOrdersQueue.getFront(order);
		restaurantOrdersQueue.dequeue();

		LinkedList<OrderItem> orderItemsList = order.getOrderItemList();
		int itemCount = orderItemsList.getLength();

		for (int i = 0; i < itemCount; i++)
		{
			OrderItem orderItem;
			orderItemsList.retrieve(i, orderItem);
			FoodItem foodItem = orderItem.getFoodItem();

			if (i == 0) {
				cout << left << setw(10) << order.getOrderID()
					<< setw(30) << foodItem.getName()
					<< setw(10) << orderItem.getQuantity()
					<< setw(15) << order.getStatus()
					<< fixed << setprecision(2) << setw(15) << order.getTotalPrice() << endl;
			}
			else {
				cout << left << setw(10) << ""
					<< setw(30) << foodItem.getName()
					<< setw(10) << orderItem.getQuantity()
					<< setw(15) << ""
					<< setw(15) << "" << endl;
			}

		}
		tempQueue.enqueue(order);
		cout << string(80, '-') << endl;
	}

	while (!tempQueue.isEmpty())
	{
		Order order;
		tempQueue.dequeue(order);
		restaurantOrdersQueue.enqueue(order);
	}
	waitForEnterKey();
	clearScreen();
}
