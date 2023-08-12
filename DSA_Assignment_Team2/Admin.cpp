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

// Read each line from admin file, and store it into hash table
// Returns an admin hash table containing all the admin details
HashTable<string, Admin> Admin::getAllAdmins(const string& filename)
{
	HashTable <string, Admin> adminsTable; // Create a hash table called adminsTable
	ifstream file(filename); // Create input file stream object named file and opens the file

	if (!file.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return adminsTable;
	}

	string header;
	getline(file, header); // Read the first line of the file and store it in the variable "header"

	string line;
	while (getline(file, line))
	{
		istringstream iss(line); // Extract comma-separated values from each line
		string adminIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile, restaurantIDFromFile;
		getline(iss, adminIDFromFile, ',');
		getline(iss, nameFromFile, ',');
		getline(iss, loginIDFromFile, ',');
		getline(iss, passwordFromFile, ',');
		getline(iss, restaurantIDFromFile, ',');

		string lowercaseLoginIDFromFile = loginIDFromFile;

		for (char& c : lowercaseLoginIDFromFile) { // Convert all the login id characters in the file to lowercase
			c = tolower(c);
		}

		Admin admin(stoi(adminIDFromFile), nameFromFile, lowercaseLoginIDFromFile, passwordFromFile, stoi(restaurantIDFromFile)); // Create a new admin object
		adminsTable.add(lowercaseLoginIDFromFile, admin); // Add the admin object to the adminsTable
	}

	file.close();

	return adminsTable;
}

// Returns a boolean value - true if successful login and false if unsuccessful login
bool Admin::adminLogin(HashTable<string, Admin>& adminTable, const string& filename) {
	string loginID, password;
	cout << "Enter your login credentials:\n";
	cout << "Login ID: ";
	cin >> ws; // Discard whitespace
	getline(cin, loginID); // Store input into loginID
	if (loginID.length() > 20) {
		cout << "Error: Login ID must not exceed 20 characters.\n";
		return false; // Return false because login is not successful
	}
	cout << "Password: ";
	cin >> ws; // Discard whitespace
	getline(cin, password); // Store input into password

	string lowercaseLoginID = loginID;

	for (char& c : lowercaseLoginID) { // Convert all the characters in the file to lowercase
		c = tolower(c);
	}

	Admin admin = adminTable.get(lowercaseLoginID); // Get admin object from the hash table based on the login ID input

	if (admin.getAdminID() != 0 && admin.getLoginID() == lowercaseLoginID && admin.getPassword() == password) { // If Admin object exists, check if the password matches
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

// Displays admin menu
void Admin::displayAdminMenu() {
	cout << "\n====================================" << endl;
	cout << "1. Update Status of Orders" << endl;
	cout << "2. View Customer Information" << endl;
	cout << "3. View Food Items Revenue" << endl;
	cout << "4. Log out" << endl;
	cout << "====================================" << endl;
	cout << "Enter your choice: ";
}

// Displays the admin home page
void Admin::adminLoginMenu(Admin& admin, HashTable<string, Admin>& adminTable, Queue<Order>& orderQueue, Stack<Notification>& notificationStack)
{
	cout << "\n-------------------------" << endl;
	cout << "       Admin Login        " << endl;
	cout << "-------------------------" << endl;
	if (admin.adminLogin(adminTable, "Admins.csv")) {
		// Filter the order queue to only display the restaurant's orders
		Order order;
		Queue<Order> restaurantOrdersQueue = order.filterRestaurantIncomingOrders(orderQueue, admin.getRestaurantID()); // Get restaurant orders queue
		Queue<Order> restaurantRevenueOrdersQueue = order.filterRestaurantRevenueOrders(orderQueue, admin.getRestaurantID()); // Get restaurant revenue orders queue
		waitForEnterKey();
		clearScreen();
		string adminOptionStr;
		do {
			admin.displayIncomingOrder(restaurantOrdersQueue); // Display the incoming orders
			displayAdminMenu(); // Displays admin menu
			cin >> adminOptionStr;

			if (adminOptionStr == "1")
			{
				updateOrderStatus(restaurantOrdersQueue, notificationStack, orderQueue); // Update order status, give customer notification, and write to files
				waitForEnterKey();
				clearScreen();
			}
			else if (adminOptionStr == "2")
			{
				viewCustomerInformationForOrder(restaurantOrdersQueue, orderQueue, admin.getRestaurantID()); // View customer informtio for a specific order
				waitForEnterKey();
				clearScreen();
			}
			else if (adminOptionStr == "3")
			{
				viewFoodItemsRevenue(restaurantRevenueOrdersQueue);
				waitForEnterKey();
				clearScreen();
			}
			else if (adminOptionStr == "4")
			{
				cout << "\nWe are logging you out now. Thank you!" << endl;
				return;
			}
			else
			{
				cout << "\nInvalid option. Please try again." << endl;
			}
		} while (adminOptionStr != "4");
	}
}

// Display all incoming orders for the admin
void Admin::displayIncomingOrder(Queue<Order>& restaurantOrdersQueue)
{
	if (restaurantOrdersQueue.isEmpty()) {
		cout << "There are no incoming orders." << endl;
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

		LinkedList<OrderItem> orderItemsList = order.getOrderItemList(); // Use a linked list to store the order items list
		int itemCount = orderItemsList.getLength(); // Get the number of ordered items in each order

		for (int i = 0; i < itemCount; i++)
		{
			OrderItem orderItem; // Create a OrderItem object
			orderItemsList.retrieve(i, orderItem); // Retrieve the orderItem object an store it into the "orderItem" variable
			FoodItem foodItem = orderItem.getFoodItem(); // Get the food item from the OrderItem object

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
		tempQueue.enqueue(order); // Add the orders into a temporary queue
		cout << string(totalWidth, '-') << endl;
	}

	while (!tempQueue.isEmpty())
	{
		Order order; 
		tempQueue.dequeue(order); // Remove the orders from a temporary queue
		restaurantOrdersQueue.enqueue(order); // Add the orders back into the original queue
	}
}

// Update status of order
void Admin::updateOrderStatus(Queue<Order>& restaurantOrdersQueue, Stack<Notification>& notificationStack, Queue<Order>& allOrdersQueue) {
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

		if (orderIDToUpdate == 0) { // Exit
			cout << "Exiting update process." << endl;
			return;
		}

		Queue<Order> updatedQueue; // Temporary queue for updated orders
		 
		while (!restaurantOrdersQueue.isEmpty()) { // Loop through all the orders in the queue
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
			updatedQueue.dequeue(order); // Dequeue the orders from the updated queue
			restaurantOrdersQueue.enqueue(order); // Enqueue the orders back into the original queue
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
				if (updatedOrder.getStatus() == "Preparing") // Check if current status is "Preparing"
				{
					cout << "Order status is already in 'Preparing State'." << endl;
				}
				else
				{
					updatedOrder.setStatus("Preparing");
					updated = true;
					cout << "Order status updated to 'Preparing'." << endl;
					break;
				}
			}
			else if (status == 2) {
				if (updatedOrder.getStatus() == "Preparing") { // Check if status is "Preparing"
					updatedOrder.setStatus("Prepared");
					updated = true;
					cout << "Order status updated to 'Prepared'." << endl;
					break;
				}
				else {
					cout << "Order status cannot be updated to 'Prepared' directly without being in 'Preparing' state." << endl;
				}
			}
			else {
				cout << "Invalid status. Please enter 1 for Preparing, 2 for Prepared or 3 to exit.\n" << endl;
			}
		}
		
		if (updated) {
			// Put the updated order in the notification stack
			Customer customer;
			string message = "Order with order ID of " + to_string(updatedOrder.getOrderID()) + " has been updated to " + updatedOrder.getStatus();
			Notification newNotification = Notification(updatedOrder.getCustomerID(), updatedOrder.getRestaurantID(), message); // Create new Notification object

			notificationStack.push(newNotification);

			insertNotificationInCSV("Notifications.csv", newNotification); // Insert new notification into file

			// Update the status of the updated order in the original queue
			Queue<Order> updatedCustomerOrdersQueue;

			while (!restaurantOrdersQueue.isEmpty()) { // Loop through the orders in the queue
				Order originalOrder;
				restaurantOrdersQueue.dequeue(originalOrder);

				if (originalOrder.getOrderID() == updatedOrder.getOrderID()) {
					originalOrder = updatedOrder;  // Update status of the updated order
				}

				if (originalOrder.getStatus() != "Prepared") {
					updatedCustomerOrdersQueue.enqueue(originalOrder); // Only add into queue if the status is not "Prepared"
				}
			}

			Queue<Order> updatedAllOrdersQueue;
			while (!allOrdersQueue.isEmpty()) // Loop through the orders in the queue
			{
				Order originalOrder;
				allOrdersQueue.dequeue(originalOrder);

				if (originalOrder.getOrderID() == updatedOrder.getOrderID()) {
					originalOrder = updatedOrder;  // Update status of the updated order
				}
				updatedAllOrdersQueue.enqueue(originalOrder); // Only add into queue if the status is not "Prepared"
			}

			while (!updatedAllOrdersQueue.isEmpty())
			{
				Order updatedOrder;
				updatedAllOrdersQueue.dequeue(updatedOrder);
				allOrdersQueue.enqueue(updatedOrder);
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

// Write notification to file
void Admin::insertNotificationInCSV(const string& filename, Notification& newNotification)
{
	ofstream inFile(filename, ios::app); // Creates an output file stream named "infile" and opens the file in append mode
	if (!inFile.is_open()) {
		cerr << "Failed to open the file." << endl;
		return;
	}

	inFile << newNotification.getCustomerID() << "," << newNotification.getRestaurantID() << "," << newNotification.getMessage() << "\n"; // Writes the notification message into the file
	inFile.close();

	cout << "Order update notification sent to customer." << endl;
}

// Update order status in CSV file
void Admin::updateOrderStatusInCSV(const string& filename, int orderIDToUpdate, const string& newStatus)
{
	ifstream inFile(filename); // Create an input file stream object named "inFile" to read data from files
	if (!inFile.is_open()) {
		cerr << "Failed to open the file." << endl;
		return;
	}

	stringstream buffer; // Creates a stringstream named "buffer"
	buffer << inFile.rdbuf(); // Read entire file into the buffer - copy contents of file in buffer
	inFile.close();

	ofstream outFile(filename); // Creates an output file stream object named "outFile"
	if (!outFile.is_open()) {
		cerr << "Failed to open the file." << endl;
		return;
	}

	string line; // Variable to hold each line in CSV file
	buffer.seekg(0); // Rewind the buffer to the beginning
	getline(buffer, line); // Skip the header line
	outFile << line << endl; // Write the header line to the output file

	while (getline(buffer, line)) { // Process each line in the buffer
		stringstream lineStream(line); // Creates a stringstream called "lineStream" to process each line
		string token; // stores the order ID
		getline(lineStream, token, ','); // read from first value up to the "," (order ID) and store it in token
		int orderID = stoi(token);

		if (orderID == orderIDToUpdate) { // Check if the order ID is the order ID to be updated
			// Replace the order status in this line
			string newLine = line.substr(0, line.rfind(',') + 1) + newStatus; // Read everything from start all the way to the last comma (inclusive), then add the updated status
			outFile << newLine << endl; // replaces the original line with the new line that includes the new status
		}
		else {
			outFile << line << endl;
		}
	}

	outFile.close();
}

// View customer informatio for selected order
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

		if (customerOrderID == 0) { // Exit
			cout << "Exiting view customer information process." << endl;
			return;
		}

		Queue<Order> tQueue; // Temporary queue for orders

		while (!restaurantOrdersQueue.isEmpty()) { // Loop through orders in the queue
			Order order;
			restaurantOrdersQueue.dequeue(order);

			if (order.getOrderID() == customerOrderID) {
				validOrderID = true; // Found a valid order ID
				customerOrder = order;
			}

			tQueue.enqueue(order); // Add order into temporary queue
		}

		// Re-enqueue orders back to the main queue
		while (!tQueue.isEmpty()) {
			Order order;
			tQueue.dequeue(order); // Remove order from temporary queue
			restaurantOrdersQueue.enqueue(order); // Add order back into main queue
		}

		if (!validOrderID) {
			cout << "Invalid Order ID. Please try again." << endl;
		}
	}

	if (validOrderID) {
		Customer customer;
		string customerLoginID = customer.getLoginIDByCustomerID("Customers.csv", customerOrder.getCustomerID()); // Retrieve the login ID of the customer
		HashTable<string, Customer> customerTable = customer.getAllCustomers("Customers.csv"); // Retrieve all customers stored in the hash table
		customer = customerTable.get(customerLoginID); // get the customer object based on the login ID

		Order order;
		Queue<Order> specificCustomerOrderQueue = order.filterRestaurantSpecificCustomerOrders(allOrders, restaurantID, customer.getCustomerID()); // get a queue containing the specified customer's orders

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
		cout << dashes << endl;
		cout << left << setw(40) << displayName << endl;
		cout << dashes << endl;
		cout << centeredHeader << endl;
		cout << dashes << endl;

		// Display headers
		cout << left << setw(10) << "Order ID" << setw(30) << "Food Item" << setw(10) << "Quantity"
			<< setw(15) << "Status" << setw(15) << "Total Price" << endl;
		cout << string(totalWidth, '-') << endl;

		while (!specificCustomerOrderQueue.isEmpty()) // Loop through cusotmer's orders in the queue
		{
			specificCustomerOrderQueue.getFront(order);
			specificCustomerOrderQueue.dequeue();

			LinkedList<OrderItem> orderItemsList = order.getOrderItemList(); // Use a linked list to store the order item list
			int itemCount = orderItemsList.getLength(); // Count how many food items the customer has

			for (int i = 0; i < itemCount; i++)
			{
				OrderItem orderItem;
				orderItemsList.retrieve(i, orderItem); // Retrieve the order item
				FoodItem foodItem = orderItem.getFoodItem(); // Retrieve the food item from the order item

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
			tempQueue.enqueue(order); // Add orders into temporary queue
			cout << string(totalWidth, '-') << endl;

		}
		allOrders;
		while (!tempQueue.isEmpty()) // Loop through all the orders in the temporary queue
		{
			Order order;
			tempQueue.dequeue(order); // Remove the orders in the temporary queue
			specificCustomerOrderQueue.enqueue(order); // Add back the orders into the original queue
		}
	}
}

// Shows admin the revenue gained from the food items
void Admin::viewFoodItemsRevenue(Queue<Order>& restaurantRevenueOrdersQueue)
{
	if (restaurantRevenueOrdersQueue.isEmpty())
	{
		cout << "No revenues generated." << endl;
		return;
	}

	LinkedList<string> foodItemNamesList; // Linked list to store food item names
	LinkedList<int> foodItemQuantitiesList; // Linked list to store food item quantities
	LinkedList<double> foodItemTotalRevenueList; // Linked list to store food item total revenue
	int numFoodItems = 0; // Keep track of the number of different food items encountered
	Queue<Order> tempQueue; // Temporary queue to help with re-enqueuing items after processing

	while (!restaurantRevenueOrdersQueue.isEmpty()) // Loop through the orders in the queue
	{
		Order order;
		restaurantRevenueOrdersQueue.dequeue(order);

		LinkedList<OrderItem> orderItemsList = order.getOrderItemList(); // Get ordered items list for each order in the queue
		int itemCount = orderItemsList.getLength(); // Get number of food items ordered

		for (int i = 0; i < itemCount; i++)
		{
			OrderItem orderItem;
			orderItemsList.retrieve(i, orderItem); // Retrieve the ordered item
			FoodItem foodItem = orderItem.getFoodItem(); // Retrieve the food item from the ordered item

			string itemName = foodItem.getName(); // Retrive the name of the food item
			double totalRevenue = foodItem.getPrice() * orderItem.getQuantity(); // Calculate the total revenue by multiplying the price of the food item with the quantity of the ordered item

			int existingIndex = -1;
			for (int j = 0; j < numFoodItems; j++) // Check whether the current food item has been encountered before
			{
				string existingItemName;
				foodItemNamesList.retrieve(j, existingItemName);
				if (existingItemName == itemName)
				{
					existingIndex = j;
					break;
				}
			}

			if (existingIndex == -1) // If not encountered before
			{
				foodItemNamesList.insert(itemName);
				foodItemQuantitiesList.insert(orderItem.getQuantity());
				foodItemTotalRevenueList.insert(totalRevenue);
				numFoodItems++;
			}
			else // If encountered before
			{
				int existingQuantity; // Hold the existing quantites
				double existingRevenue; // Hold the existing revenues
				foodItemQuantitiesList.retrieve(existingIndex, existingQuantity); // Retrieve the existing quantity
				foodItemTotalRevenueList.retrieve(existingIndex, existingRevenue); // Retrieve the existing revenue

				foodItemQuantitiesList.remove(existingIndex); // Remove the exsting quantity
				foodItemTotalRevenueList.remove(existingIndex); // Remove the existing revenue

				foodItemQuantitiesList.insert(existingIndex, existingQuantity + orderItem.getQuantity()); // Add existing quantity with quantity of current order item
				foodItemTotalRevenueList.insert(existingIndex, existingRevenue + totalRevenue); // Add existing revenue with revenue of current order item
			}
		}
		tempQueue.enqueue(order); // Add the orders into temporary queue
	}

	const int totalWidth = 80;
	string header = "Food Items Revenue";
	string dashes(totalWidth, '=');

	int spacesOnEachSide = (totalWidth - header.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + header;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	cout << left << setw(35) << "Food Item" << setw(20) << "Quantity Sold"
		<< setw(15) << "Total Profit" << endl;
	cout << string(totalWidth, '-') << endl;

	long double totalOverallRevenue = 0.0;

	for (int i = 0; i < numFoodItems; i++) // Loop through all the food items
	{
		string itemName;
		int quantity;
		double revenue;
		foodItemNamesList.retrieve(i, itemName); // Retrieve the name
		foodItemQuantitiesList.retrieve(i, quantity); // Retrieve the  quantity
		foodItemTotalRevenueList.retrieve(i, revenue); // Retrieve the revenue

		cout << left << setw(35) << itemName
			<< setw(20) << quantity
			<< fixed << setprecision(2) << "$" << setw(15) << revenue << endl;

		totalOverallRevenue += revenue; // Add revenue to find total
	}

	cout << string(totalWidth, '-') << endl;

	cout << left << setw(55) << "Total Revenue"
		<< fixed << setprecision(2) << "$" << setw(15) << totalOverallRevenue << endl;

	cout << string(totalWidth, '-') << endl;

	while (!tempQueue.isEmpty())
	{
		Order order; 
		tempQueue.dequeue(order); // Remove all orders from queue
		restaurantRevenueOrdersQueue.enqueue(order); // Add the orders back into the list
	}
}
