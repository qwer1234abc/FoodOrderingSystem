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
	cout << "\n====================================" << endl;
	cout << "1. Update Status of Orders" << endl;
	cout << "2. View Customer Information" << endl;
	cout << "3. Log out" << endl;
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
		Queue<Order> restaurantOrdersQueue = order.filterRestaurantIncomingOrders(orderQueue, admin.getRestaurantID());
		waitForEnterKey();
		clearScreen();
		string adminOptionStr;
		do {
			admin.displayIncomingOrder(restaurantOrdersQueue);
			cin >> adminOptionStr;

			if (adminOptionStr == "1")
			{
				updateOrderStatus(restaurantOrdersQueue);
			}
			else if (adminOptionStr == "2")
			{
				viewCustomerInformationForOrder(restaurantOrdersQueue, orderQueue, admin.getRestaurantID());
				waitForEnterKey();
				clearScreen();
			}
			else if (adminOptionStr == "3")
			{
				cout << "\nWe are logging you out now. Thank you!" << endl;
				return;
			}
			else
			{
				cout << "\nInvalid option. Please try again." << endl;
			}
		} while (adminOptionStr != "3");
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
	int totalWidth = 80;
	string header = "Incoming Orders";

	string dashes(totalWidth, '=');

	int spacesOnEachSide = (totalWidth - header.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + header;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	// Display headers
	cout << left << setw(10) << "Order ID" << setw(30) << "Food Item" << setw(10) << "Quantity"
		<< setw(15) << "Status" << setw(15) << "Total Price" << endl;
	cout << string(totalWidth, '-') << endl;

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
		cout << string(totalWidth, '-') << endl;
	}

	while (!tempQueue.isEmpty())
	{
		Order order;
		tempQueue.dequeue(order);
		restaurantOrdersQueue.enqueue(order);
	}

	displayAdminMenu();
}

void Admin::updateOrderStatus(Queue<Order>& restaurantOrdersQueue) {
	if (restaurantOrdersQueue.isEmpty()) {
		cout << "No orders to update." << endl;
		return;
	}

	int orderIDToUpdate;
	bool validOrderID = false;
	Order updatedOrder;

	while (!validOrderID) {
		cout << "Enter the Order ID you want to update (enter 0 to exit): ";
		cin >> orderIDToUpdate;

		if (cin.fail()) {
			cin.clear(); // Clear the error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
			cout << "Invalid input. Please enter a valid Order ID." << endl;
			continue;
		}

		if (orderIDToUpdate == 0) {
			cout << "Exiting update process." << endl;
			return;
		}

		Queue<Order> updatedQueue; // Temporary queue for updated orders

		while (!restaurantOrdersQueue.isEmpty()) {
			Order order;
			restaurantOrdersQueue.dequeue(order);

			if (order.getOrderID() == orderIDToUpdate) {
				validOrderID = true; // Found a valid order ID
				updatedOrder = order; // Store the order to be updated
				cout << "\n-------------------------" << endl;
				cout << "      Status Options     " << endl;
				cout << "-------------------------" << endl;
				cout << "1. Preparing" << endl;
				cout << "2. Prepared" << endl;
			}
			updatedQueue.enqueue(order); // Store orders that are not being updated
		}

		// Re-enqueue orders back to the main queue
		while (!updatedQueue.isEmpty()) {
			Order order;
			updatedQueue.dequeue(order);
			restaurantOrdersQueue.enqueue(order);
		}

		if (!validOrderID) {
			cout << "Invalid Order ID. Please try again." << endl;
		}
	}

	if (validOrderID) {
		int status;
		bool updated = false;
		while (true)
		{
			cout << "Enter the new status for the order (enter 0 to exit): ";
			cin >> status;


			if (cin.fail()) {
				cin.clear(); // Clear the error flags
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
				cout << "Invalid input. Please enter a valid input." << endl;
				continue;
			}

			if (status == 0) {
				cout << "Exiting update process." << endl;
				return;
			}
			else if (status == 1) {
				updatedOrder.setStatus("Preparing");
				updated = true;
				cout << "Order status updated to 'Preparing'." << endl;
				break;
			}
			else if (status == 2) {
				updatedOrder.setStatus("Prepared");
				updated = true;
				cout << "Order status updated to 'Prepared'." << endl;
				break;
			}
			else {
				cout << "Invalid status. Please enter 1 for Preparing, 2 for Prepared.\n" << endl;
			}
		}
		if (updated)
		{
			// Update the status of the updated order in the original queue
			Queue<Order> updatedCustomerOrdersQueue;

			while (!restaurantOrdersQueue.isEmpty()) {
				Order originalOrder;
				restaurantOrdersQueue.dequeue(originalOrder);

				if (originalOrder.getOrderID() == updatedOrder.getOrderID()) {
					originalOrder = updatedOrder;  // Update status of the updated order
				}

				updatedCustomerOrdersQueue.enqueue(originalOrder);
			}

			// Update the original queue with the modified orders
			while (!updatedCustomerOrdersQueue.isEmpty()) {
				Order updatedOrder;
				updatedCustomerOrdersQueue.dequeue(updatedOrder);
				restaurantOrdersQueue.enqueue(updatedOrder);
			}

			updateOrderStatusInCSV("Orders.csv", updatedOrder.getOrderID(), updatedOrder.getStatus());
		}
	}
}

void Admin::updateOrderStatusInCSV(const string& filename, int orderIDToUpdate, const string& newStatus)
{
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cerr << "Failed to open the file." << endl;
		return;
	}

	stringstream buffer;
	buffer << inFile.rdbuf(); // Read entire file into the buffer
	inFile.close();

	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cerr << "Failed to open the file." << endl;
		return;
	}

	string line;
	buffer.seekg(0); // Rewind the buffer to the beginning
	getline(buffer, line); // Skip the header line
	outFile << line << endl; // Write the header line to the output file

	while (getline(buffer, line)) {
		stringstream lineStream(line);
		string token;
		getline(lineStream, token, ',');
		int orderID = stoi(token);

		if (orderID == orderIDToUpdate) {
			// Replace the order status in this line
			string newLine = line.substr(0, line.rfind(',') + 1) + newStatus;
			outFile << newLine << endl;
		}
		else {
			outFile << line << endl;
		}
	}

	outFile.close();
}

void Admin::viewCustomerInformationForOrder(Queue<Order>& restaurantOrdersQueue, Queue<Order>& allOrders, int restaurantID)
{
	if (restaurantOrdersQueue.isEmpty()) {
		cout << "No orders to view customer information." << endl;
		return;
	}

	int customerOrderID;
	bool validOrderID = false;
	Order customerOrder;

	while (!validOrderID) {
		cout << "Enter the Order ID you want to view customer information for (enter 0 to exit): ";
		cin >> customerOrderID;

		if (cin.fail()) {
			cin.clear(); // Clear the error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
			cout << "Invalid input. Please enter a valid Order ID." << endl;
			continue;
		}

		if (customerOrderID == 0) {
			cout << "Exiting update process." << endl;
			return;
		}

		Queue<Order> updatedQueue; // Temporary queue for updated orders

		while (!restaurantOrdersQueue.isEmpty()) {
			Order order;
			restaurantOrdersQueue.dequeue(order);

			if (order.getOrderID() == customerOrderID) {
				validOrderID = true; // Found a valid order ID
				customerOrder = order;
			}

			updatedQueue.enqueue(order);
		}

		// Re-enqueue orders back to the main queue
		while (!updatedQueue.isEmpty()) {
			Order order;
			updatedQueue.dequeue(order);
			restaurantOrdersQueue.enqueue(order);
		}

		if (!validOrderID) {
			cout << "Invalid Order ID. Please try again." << endl;
		}
	}

	if (validOrderID) {
		Customer customer;
		string customerLoginID = customer.getLoginIDByCustomerID("Customers.csv", customerOrder.getCustomerID());
		HashTable<string, Customer> customerTable = customer.getAllCustomers("Customers.csv");
		customer = customerTable.get(customerLoginID);

		Order order;
		Queue<Order> specificCustomerOrderQueue = order.filterRestaurantSpecificCustomerOrders(allOrders, restaurantID, customer.getCustomerID());

		if (specificCustomerOrderQueue.isEmpty()) {
			cout << customer.getName() + " has no past orders in this restaurant." << endl;
			waitForEnterKey();
			clearScreen();
			return;
		}

		Queue<Order> tempQueue; // Temporary queue to store the orders
		int totalWidth = 80;
		string header = "Past Orders For " + customer.getName();

		string dashes(totalWidth, '=');

		int spacesOnEachSide = (totalWidth - header.length()) / 2;
		string centeredHeader = string(spacesOnEachSide, ' ') + header;
		string displayName = "Customer Name: " + customer.getName();
		string displayLoyaltyPoints = "Loyalty Points: " + customer.getLoyaltyPoints();
		cout << dashes << endl;
		cout << left << setw(40) << displayName << displayLoyaltyPoints << endl;
		cout << dashes << endl;
		cout << centeredHeader << endl;
		cout << dashes << endl;

		// Display headers
		cout << left << setw(10) << "Order ID" << setw(30) << "Food Item" << setw(10) << "Quantity"
			<< setw(15) << "Status" << setw(15) << "Total Price" << endl;
		cout << string(totalWidth, '-') << endl;

		while (!specificCustomerOrderQueue.isEmpty())
		{
			specificCustomerOrderQueue.getFront(order);
			specificCustomerOrderQueue.dequeue();

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
			cout << string(totalWidth, '-') << endl;

		}
		allOrders;
		while (!tempQueue.isEmpty())
		{
			Order order;
			tempQueue.dequeue(order);
			specificCustomerOrderQueue.enqueue(order);
		}
	}
}