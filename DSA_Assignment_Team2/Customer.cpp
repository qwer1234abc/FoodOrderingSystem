#include "Customer.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream> 

using namespace std;


Customer::Customer() : orderItemsList() {}

Customer::Customer(int id, const string& n, const string& l, const string& p) {
	customerID = id;
	name = n;
	loginID = l;
	password = p;
}

int Customer::getCustomerID() const {
	return customerID;
}

string Customer::getName() const {
	return name;
}

string Customer::getLoginID() const {
	return loginID;
}

string Customer::getPassword() const {
	return password;
}

LinkedList<OrderItem> Customer::getOrderItemsList() const {
	return orderItemsList;
}

string Customer::getLoginIDByCustomerID(const string& filename, int customerID) {
	ifstream file(filename); // create input file stream object named file and opens the file

	if (!file.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return "";
	}

	string header;
	getline(file, header); // read the first line of the file and store it in the variable "header"

	string line;
	while (getline(file, line))
	{
		istringstream iss(line); // extract comma-separated values from each line
		string customerIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile;
		getline(iss, customerIDFromFile, ',');
		getline(iss, nameFromFile, ',');
		getline(iss, loginIDFromFile, ',');
		getline(iss, passwordFromFile, ',');

		if (stoi(customerIDFromFile) == customerID) {
			return loginIDFromFile;
		}
	}

	file.close();

	return "";
}

HashTable<string, Customer> Customer::getAllCustomers(const string& filename)
{
	HashTable <string, Customer> customersTable;
	ifstream file(filename); // create input file stream object named file and opens the file

	if (!file.is_open())
	{
		cout << "Error: Unable to open the file " << filename << endl;
		return customersTable;
	}

	string header;
	getline(file, header); // read the first line of the file and store it in the variable "header"

	string line;
	while (getline(file, line))
	{
		istringstream iss(line); // extract comma-separated values from each line
		string customerIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile;
		getline(iss, customerIDFromFile, ',');
		getline(iss, nameFromFile, ',');
		getline(iss, loginIDFromFile, ',');
		getline(iss, passwordFromFile, ',');

		string lowercaseLoginIDFromFile = loginIDFromFile;

		for (char& c : lowercaseLoginIDFromFile) { // convert all the characters in the file to lowercase
			c = tolower(c);
		}

		Customer customer(stoi(customerIDFromFile), nameFromFile, lowercaseLoginIDFromFile, passwordFromFile);
		customersTable.add(lowercaseLoginIDFromFile, customer);
	}

	file.close();

	return customersTable;
}

void Customer::registerCustomer(HashTable<string, Customer>& customersTable, const string& filename) {
	string name, loginID, password;

	cout << "Enter customer details:\n";
	cout << "Name: ";
	cin >> ws;
	getline(cin, name);
	cout << "Login ID: ";
	cin >> ws;
	getline(cin, loginID);
	if (loginID.length() > 20) {
		cout << "Error: Login ID must not exceed 20 characters.\n";
		return;
	}
	cout << "Password: ";
	cin >> ws;
	getline(cin, password);

	for (char c : loginID) {
		if (!isalnum(c)) {
			cout << "Error: Login ID must contain only alphanumeric characters.\n";
			return;
		}
	}

	string lowercaseLoginID = loginID;

	for (char& c : lowercaseLoginID) { // convert all the characters in the input to lowercase
		c = tolower(c);
	}

	if (customersTable.get(lowercaseLoginID).getLoginID() != "") {
		cout << "Error: Customer with this Login ID already exists.\n";
		return;
	}

	int customerID = 0; // Default ID if no accounts are present

	// Get the last customer ID from the file
	ifstream file(filename); // create input file stream object named file and opens the file
	if (file.is_open()) {
		string line;
		while (getline(file, line)) { // reads the file and getline reads each line into "line" variable
			istringstream iss(line); // extract comma-separated values from each line
			string customerIDFromFile;
			if (getline(iss, customerIDFromFile, ',')) { // read first value up to ',' and store in "customerIDFromFile" variable
				try {
					int tempID = stoi(customerIDFromFile); // convert extracted value from string to int
					if (tempID > customerID) {
						customerID = tempID; // Update customerID with the last ID
					}
				}
				catch (const invalid_argument& e) {
				}
			}
		}
		file.close();
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}

	// Increment the customer ID for the new customer
	customerID++;

	// Create a new Customer object
	Customer newCustomer(customerID, name, lowercaseLoginID, password);

	// Save the customer details to the CSV file
	ofstream fileToWrite(filename, ios::app); // creates output file stream object and opens file in APPEND mode
	if (fileToWrite.is_open()) {
		fileToWrite << newCustomer.getCustomerID() << "," << newCustomer.getName() << ","
			<< newCustomer.getLoginID() << "," << newCustomer.getPassword() << "\n";
		fileToWrite.close();
		cout << "Registration successful!\n";
		customersTable.add(lowercaseLoginID, newCustomer);
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}
}

bool Customer::customerLogin(HashTable<string, Customer>& customersTable, const string& filename) {
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

	for (char& c : lowercaseLoginID) { // convert all the characters in the input to lowercase
		c = tolower(c);
	}

	Customer customer = customersTable.get(lowercaseLoginID);

	if (customer.getCustomerID() != 0 && customer.getLoginID() == lowercaseLoginID && customer.getPassword() == password) {
		customerID = customer.getCustomerID(); // convert customerID to from string to integer
		name = customer.getName();
		cout << "Login successful!\n";
		return true;
	}
	else if (customer.getCustomerID() == 0) {
		cout << "Customer with this Login ID does not exist. Please try again.\n";
	}
	else {
		cout << "Incorrect Login ID or password. Please try again.\n";
	}
	return false;
}

void Customer::displayCustomerMenu() {
	cout << "Welcome " << name << "! " << endl;
	cout << "Here is the customer menu:" << endl;
	cout << "=====================================" << endl;
	cout << "           Customer Menu            " << endl;
	cout << "=====================================" << endl;
	cout << "1. Create a new order" << endl;
	cout << "2. View order history" << endl;
	cout << "3. Cancel an order" << endl;
	cout << "4. Notifications" << endl;
	cout << "5. Log out" << endl;
	cout << "=====================================" << endl;
	cout << "Enter your choice: ";
}

HashTable<int, FoodItem> Customer::browseFoodItems(const string& foodItemsFile, const LinkedList<Restaurant>& restaurants, int restaurantID = -1)
{
	// Read food items from the CSV file and store them in the hashtable
	HashTable<int, FoodItem> foodItemsTable; // create a foodItemsTable hash table
	ifstream foodOptionsfile(foodItemsFile);  // input file named "FoodOptionsFile" created and initiated with "foodItemsFile" file
	if (!foodOptionsfile.is_open())
	{
		cout << "Error: Unable to open the file " << foodItemsFile << endl;
		return foodItemsTable; // Return an empty table as there are no food items read
	}

	// Skip the header line
	string header;
	getline(foodOptionsfile, header);

	string line;
	int key = 1;
	while (getline(foodOptionsfile, line)) // read the lines in the file
	{
		istringstream iss(line); // extract comma-separated values from each line
		string foodItemIDStr, name, category, restaurantIDStr, priceStr;

		// Read each field from the CSV line, separated by commas
		getline(iss, foodItemIDStr, ',');
		getline(iss, name, ',');
		getline(iss, category, ',');
		getline(iss, restaurantIDStr, ',');
		getline(iss, priceStr, ',');

		// Convert the read data to appropriate data types
		int foodItemID = stoi(foodItemIDStr);
		double price = stod(priceStr);
		int restaurantIDFromFile = stoi(restaurantIDStr);

		// Check if the restaurant ID is provided and skip items from other restaurants
		if (restaurantID != -1 && restaurantID != restaurantIDFromFile)
		{
			continue;
		}

		// Create a FoodItem object
		FoodItem foodItem(foodItemID, name, category, price, restaurantIDFromFile);

		// Add the FoodItem object to the hashtable, with the id as the key and the food item as the value
		foodItemsTable.add(key, foodItem);
		key++;
	}

	foodOptionsfile.close();

	if (restaurantID == -1)
	{
		// If the restaurant ID is not provided, print all food items
		foodItemsTable.print(restaurants);
	}
	else
	{
		// If the restaurant ID is provided, print only the food items from that restaurant
		foodItemsTable.print(restaurants, restaurantID);
	}

	return foodItemsTable; // Return the total number of food items read
}

void Customer::addOrderItem(FoodItem& fooditem, int quantity) {
	OrderItem order(fooditem, quantity);
	orderItemsList.insert(order);
}

int Customer::orderItemsMenu(const LinkedList<OrderItem>& orderItemsList, const LinkedList<Restaurant>& restaurants)
{
	// Calculate the padding to center the header
	int totalWidth = 50;
	string header = "Here are your ordered items:";
	int padding = (totalWidth - header.length()) / 2;

	// Print header
	cout << setw(padding + header.length()) << header << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << setw(10) << left << "Quantity" << setw(30) << left << "Food Item" << setw(20) << left << "Price" << endl;
	cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;

	long double totalPrice = 0.0; // Initialize the total price to zero

	for (int i = 0; i < orderItemsList.getLength(); i++) // loop through all the items in the orderitemslist list
	{
		OrderItem orderItem = orderItemsList.retrieve(i);
		FoodItem foodItem = orderItem.getFoodItem(); // retrieve the item
		double itemPrice = foodItem.getPrice() * orderItem.getQuantity(); // calculate price with the price * quantity of the item

		cout << setw(10) << left << orderItem.getQuantity()
			<< setw(30) << left << foodItem.getName()
			<< "$" << fixed << setprecision(2) << itemPrice << endl;

		totalPrice += itemPrice; // Add the item's price to the total price
	}

	cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;
	cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl; // Print the total price
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;

	// Get the restaurant name for the first order item
	OrderItem firstOrderItem = orderItemsList.retrieve(0); // retrieve the first order item from the orderitemlist
	string restaurantName = firstOrderItem.getFoodItem().getRestaurantNameByID(firstOrderItem.getFoodItem().getRestaurantID(), restaurants); // get restaurant id of the food item
	cout << "1. Add more items from " << restaurantName << endl;
	cout << "2. Confirm order" << endl;
	cout << "3. Cancel Order (Exit)" << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << "Enter your choice: ";

	return firstOrderItem.getFoodItem().getRestaurantID(); // return restaurant id user entered food from
}

void Customer::customerLoginMenu(Customer& customer, HashTable<string, Customer>& customersTable, Queue<Order>& orderQueue, Stack<Notification>& notificationStack) {
	cout << "\n-------------------------" << endl;
	cout << "      Customer Login      " << endl;
	cout << "-------------------------" << endl;
	if (customer.customerLogin(customersTable, "Customers.csv")) {
		// Filter the order queue to only display the customer's orders
		Order order;
		Queue<Order> customerOrdersQueue = order.filterCustomerOrders(orderQueue, customer.getCustomerID());
		Notification notification;
		Stack<Notification> customerNotificationsStack = notification.filterCustomerNotifications(notificationStack, customer.getCustomerID());
		customerNotificationsStack;
		waitForEnterKey();
		clearScreen();
		string customerOptionStr;
		do {
			customer.displayCustomerMenu();
			cin >> customerOptionStr;

			if (customerOptionStr == "1") {
				Restaurant restaurant;
				browseFoodItemsMenu(customer, restaurant, customerOrdersQueue);
			}
			else if (customerOptionStr == "2") {
				displayOrders(customerOrdersQueue);
			}
			else if (customerOptionStr == "3") {
				cancelOrder(customerOrdersQueue);
				waitForEnterKey();
				clearScreen();
			}
			else if (customerOptionStr == "4") {
				displayNotifications(customerNotificationsStack);
			}
			else if (customerOptionStr == "5") {
				cout << "\nWe are logging you out now. Thank you!" << endl;
				return;
			}
			else {
				cout << "\nInvalid option. Please try again." << endl;
			}
		} while (customerOptionStr != "5");
	}
}

void Customer::displayNotifications(Stack<Notification>& customerNotificationsStack)
{
	// display notifications

	if (customerNotificationsStack.isEmpty())
	{
		cout << "No notifications." << endl;
		waitForEnterKey();
		clearScreen();
		return;
	}

	Stack<Notification> tempStack; // Temporary stack to store the notifications

	int totalWidth = 100;
	string header = "Notifications";

	string dashes(totalWidth, '=');

	int spacesOnEachSide = (totalWidth - header.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + header;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	cout << left << setw(70) << "Message" << setw(10) << "Restaurant Name" << endl;
	cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;

	Restaurant restaurant;
	LinkedList<Restaurant> restaurants = restaurant.getAllRestaurants("Restaurants.csv");
	while (!customerNotificationsStack.isEmpty())
	{
		Notification notification = customerNotificationsStack.pop();
		cout << left << setw(70) << notification.getMessage() << setw(10) << restaurant.getNameByID(notification.getRestaurantID(), restaurants) << endl;
		tempStack.push(notification);
	}

	while (!tempStack.isEmpty())
	{
		customerNotificationsStack.push(tempStack.pop());
	}

	cout << setfill('-') << setw(totalWidth) << "-" << setfill(' ') << endl;

	waitForEnterKey();
	clearScreen();
}

void Customer::displayOrders(Queue<Order>& customerOrdersQueue)
{
	if (customerOrdersQueue.isEmpty())
	{
		cout << "No order history." << endl;
		waitForEnterKey();
		clearScreen();
		return;
	}

	Queue<Order> tempQueue; // Temporary queue to store the orders

	int totalWidth = 80;
	string header = "Order History";

	string dashes(totalWidth, '=');

	int spacesOnEachSide = (totalWidth - header.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + header;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	cout << left << setw(10) << "Order ID" << setw(30) << "Food Item" << setw(10) << "Quantity"
		<< setw(15) << "Status" << setw(15) << "Total Price" << endl;
	cout << string(80, '-') << endl;

	while (!customerOrdersQueue.isEmpty())
	{
		Order order;
		customerOrdersQueue.getFront(order);
		customerOrdersQueue.dequeue();

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
		customerOrdersQueue.enqueue(order);
	}
	waitForEnterKey();
	clearScreen();
}

void Customer::customerRegisterMenu(Customer& customer, HashTable<string, Customer>& customersTable)
{
	cout << "\n-------------------------" << endl;
	cout << "    Customer Register     " << endl;
	cout << "-------------------------" << endl;
	customer.registerCustomer(customersTable, "Customers.csv");
}

void Customer::browseFoodItemsMenu(Customer& customer, Restaurant& restaurant, Queue<Order>& customerOrdersQueue) {
	bool continueOrdering = true;
	while (continueOrdering) {
		HashTable<int, FoodItem> foodItemsHashTable = customer.browseFoodItems("FoodItems.csv", restaurant.getAllRestaurants("Restaurants.csv"), restaurant.getRestaurantID());
		int foodItemLength = foodItemsHashTable.getLength();
		int foodItemChoice;
		do {
			cin >> foodItemChoice;
			if (foodItemChoice >= 1 && foodItemChoice <= foodItemLength) {
				continueOrdering = orderFoodItems(customer, restaurant, foodItemChoice, foodItemsHashTable, customerOrdersQueue);
				break;
			}
			else {
				cout << "Invalid option. Please try again: ";
				foodItemChoice = -1;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		} while (true);
	}
}

bool Customer::orderFoodItems(Customer& customer, Restaurant& restaurant, int foodItemChoice, HashTable<int, FoodItem>& foodItemsTable, Queue<Order>& customerOrdersQueue) {
	int quantity;
	FoodItem foodItem = foodItemsTable.get(foodItemChoice);

	do {
		cout << "Enter quantity for " << foodItem.getName() << ": ";
		cin >> quantity;
		if (quantity >= 1 && quantity <= 20) {
			customer.addOrderItem(foodItem, quantity);
			cout << quantity << " " << foodItem.getName() << " added to your order successfully." << endl;
			waitForEnterKey();
			clearScreen();

			// Ask the customer if they want to add more food items to their order
			string addMoreFoodItemsStr;
			do {
				int restaurantID = customer.orderItemsMenu(customer.orderItemsList, restaurant.getAllRestaurants("Restaurants.csv"));
				restaurant.setRestaurantID(restaurantID);
				cin >> addMoreFoodItemsStr;

				if (addMoreFoodItemsStr == "1") {
					return true; // Continue ordering more food items
				}
				else if (addMoreFoodItemsStr == "2") {
					long double totalPrice = 0.0; // Initialize the total price to zero

					for (int i = 0; i < customer.orderItemsList.getLength(); i++) // loop through all the items in the orderitemslist list
					{
						OrderItem orderItem = customer.orderItemsList.retrieve(i);
						FoodItem foodItem = orderItem.getFoodItem(); // retrieve the item
						double itemPrice = foodItem.getPrice() * orderItem.getQuantity(); // calculate price with the price * quantity of the item
						totalPrice += itemPrice;
					}
					cout << "\nTotal price is $" << totalPrice << "." << endl;
					string confirmOrderStr;
					do
					{
						cout << "Do you want to confirm the order? (Y/N): ";
						cin >> confirmOrderStr;

						if (confirmOrderStr == "n" || confirmOrderStr == "N") {
							cout << "Ordered items cancelled." << endl;
							waitForEnterKey();
							clearScreen();
							break;
						}
						else if (confirmOrderStr == "y" || confirmOrderStr == "Y") {
							createOrder("Orders.csv", customer.getCustomerID(), customer.orderItemsList, restaurant.getRestaurantID(), totalPrice, customerOrdersQueue);
							waitForEnterKey();
							clearScreen();
							return false;
						}
						else {
							cout << "\nInvalid option. Please try again." << endl;
						}
					} while (true);
				}
				else if (addMoreFoodItemsStr == "3") {
					customer.orderItemsList.clear();
					cout << "Ordered items cancelled." << endl;
					waitForEnterKey();
					clearScreen();
					return false; // Stop ordering food items
				}
				else {
					cout << "\nInvalid option. Please try again." << endl;
				}
			} while (true);
		}
		else {
			cout << "Range of quantity is 1-20. Please try again." << endl;
			quantity = -1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (true);
}

void Customer::createOrder(const string& filename, int customerID, LinkedList<OrderItem>& orderItemsList, int restaurantID, long double totalPrice, Queue<Order>& customerOrdersQueue) {
	if (orderItemsList.isEmpty()) {
		cout << "Error: No items in the order. Please add items to the order first." << endl;
		return;
	}
	int orderID = 0; // Default ID if no accounts are present

	// Get the last order ID from the file
	ifstream file(filename); // create input file stream object named file and opens the file
	if (file.is_open()) {
		string line;
		while (getline(file, line)) { // reads the file and getline reads each line into "line" variable
			istringstream iss(line); // extract comma-separated values from each line
			string orderIDFromFile;
			if (getline(iss, orderIDFromFile, ',')) { // read first value up to ',' and store in "orderIDFromFile" variable
				try {
					int tempID = stoi(orderIDFromFile); // convert extracted value from string to int
					if (tempID > orderID) {
						orderID = tempID; // Update orderID with the last ID
					}
				}
				catch (const invalid_argument& e) {
				}
			}
		}
		file.close();
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}

	// Increment the order ID for the new order
	orderID++;

	Order newOrder(orderID, customerID, orderItemsList, restaurantID, totalPrice, "Not Prepared");

	string foodItemsString = newOrder.orderItemsListToString(orderItemsList);

	// Save the order details to the CSV file
	ofstream fileToWrite(filename, ios::app); // creates output file stream object and opens file in APPEND mode
	if (fileToWrite.is_open()) {
		fileToWrite << newOrder.getOrderID() << "," << newOrder.getCustomerID() << ","
			<< foodItemsString << "," // Use the converted string
			<< newOrder.getRestaurantID() << "," << newOrder.getTotalPrice() << ","
			<< newOrder.getStatus() << "\n";
		fileToWrite.close();
		cout << "Order created and sent to restaurant." << endl;
		customerOrdersQueue.enqueue(newOrder);
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}
	orderItemsList.clear();
}

void Customer::cancelOrder(Queue<Order>& customerOrdersQueue) {
	Order order;
	Queue<Order> unPreparedOrdersQueue = order.filterUnPreparedCustomerOrders(customerOrdersQueue);

	if (unPreparedOrdersQueue.isEmpty()) {
		cout << "No available orders to cancel." << endl;
		return;
	}

	Queue<Order> tempQueue; // Temporary queue to store the orders

	int totalWidth = 80;
	string header = "Unprepared Orders";

	string dashes(totalWidth, '=');

	int spacesOnEachSide = (totalWidth - header.length()) / 2;
	string centeredHeader = string(spacesOnEachSide, ' ') + header;

	cout << dashes << endl;
	cout << centeredHeader << endl;
	cout << dashes << endl;

	cout << left << setw(10) << "Order ID" << setw(30) << "Food Item" << setw(10) << "Quantity"
		<< setw(15) << "Status" << setw(15) << "Total Price" << endl;
	cout << string(80, '-') << endl;

	while (!unPreparedOrdersQueue.isEmpty()) {
		unPreparedOrdersQueue.getFront(order);
		unPreparedOrdersQueue.dequeue();

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
					<< setw(15) << order.getTotalPrice() << endl;
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

	// Ask for user input for valid Order ID
	int orderIDToCancel;
	bool validOrderID = false;
	Order cancelledOrder;

	while (!validOrderID) {
		cout << "Enter the Order ID you want to cancel (enter 0 to exit): ";
		cin >> orderIDToCancel;

		if (cin.fail()) {
			cin.clear(); // Clear the error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
			cout << "Invalid input. Please enter a valid Order ID." << endl;
			continue;
		}

		if (orderIDToCancel == 0) {
			cout << "Exiting cancellation process." << endl;
			return;
		}

		while (!tempQueue.isEmpty()) {
			tempQueue.dequeue(order);
			if (order.getOrderID() == orderIDToCancel) {
				validOrderID = true; // Found a valid order ID
				cancelledOrder = order; // Store the cancelled order
				cout << "Order with ID " << orderIDToCancel << " is canceled." << endl;
				break;
			}
			unPreparedOrdersQueue.enqueue(order);
		}

		// Move orders from unPreparedOrdersQueue to tempQueue
		while (!unPreparedOrdersQueue.isEmpty()) {
			unPreparedOrdersQueue.dequeue(order);
			tempQueue.enqueue(order);
		}

		if (!validOrderID) {
			cout << "Invalid Order ID. Please try again." << endl;
		}
	}

	if (validOrderID) {
		cancelledOrder.setStatus("Cancelled");

		// Update the status of the cancelled order in the original queue
		Queue<Order> updatedCustomerOrdersQueue;

		while (!customerOrdersQueue.isEmpty()) {
			Order originalOrder;
			customerOrdersQueue.dequeue(originalOrder);

			if (originalOrder.getOrderID() == cancelledOrder.getOrderID()) {
				originalOrder = cancelledOrder;  // Update status of the cancelled order
			}

			updatedCustomerOrdersQueue.enqueue(originalOrder);
		}

		// Update the original queue with the modified orders
		while (!updatedCustomerOrdersQueue.isEmpty()) {
			Order updatedOrder;
			updatedCustomerOrdersQueue.dequeue(updatedOrder);
			customerOrdersQueue.enqueue(updatedOrder);
		}

		updateOrderStatusInCSV("Orders.csv", cancelledOrder.getOrderID(), cancelledOrder.getStatus());
	}

	// Re-queue the remaining orders
	while (!tempQueue.isEmpty()) {
		tempQueue.dequeue(order);
		unPreparedOrdersQueue.enqueue(order);
	}
}

void Customer::updateOrderStatusInCSV(const string& filename, int orderIDToCancel, const string& newStatus) {
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

		if (orderID == orderIDToCancel) {
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