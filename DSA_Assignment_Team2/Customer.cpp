#include "Customer.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream> 

using namespace std;

Customer::Customer() {}

Customer::Customer(int id, const string& n, const string& l, const string& p, int lp) {
	customerID = id;
	name = n;
	loginID = l;
	password = p;
	loyaltyPoints = lp;
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

int Customer::getLoyaltyPoints() const {
	return loyaltyPoints;
}

LinkedList<OrderItem> Customer::getOrderItemsList() const {
	return orderItemsList;
}

// Function to register a new customer
void Customer::registerCustomer(const string& filename) {
	string name, loginID, password;
	int loyaltyPoints = 0;

	cout << "Enter customer details:\n";
	cout << "Name: ";
	cin >> ws;
	getline(cin, name);
	cout << "Login ID: ";
	cin >> ws;
	getline(cin, loginID);
	cout << "Password: ";
	cin >> ws;
	getline(cin, password);

	if (!uniqueLoginID(filename, loginID)) {
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
	Customer newCustomer(customerID, name, loginID, password, loyaltyPoints);

	// Save the customer details to the CSV file
	ofstream fileToWrite(filename, ios::app); // creates output file stream object and opens file in APPEND mode
	if (fileToWrite.is_open()) {
		fileToWrite << newCustomer.getCustomerID() << "," << newCustomer.getName() << ","
			<< newCustomer.getLoginID() << "," << newCustomer.getPassword() << ","
			<< newCustomer.getLoyaltyPoints() << "\n";
		fileToWrite.close();
		cout << "Registration successful!\n";
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}
}

// Function to check if the customer with the given email and password exists
bool Customer::customerExists(const string& filename, const string& loginID, const string& password) {
	ifstream file(filename); // create  input file stream object called "file" and opens the file
	if (file.is_open()) {
		// Skip the header line
		string header;
		getline(file, header);

		string line;
		while (getline(file, line)) { // read each line from the file
			istringstream iss(line); // extract comma-separated values from each line
			string customerIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile, loyaltyPointsFromFile;

			// Read each field from the CSV line, separated by commas
			getline(iss, customerIDFromFile, ',');
			getline(iss, nameFromFile, ',');
			getline(iss, loginIDFromFile, ','); // Read the email from the third column
			getline(iss, passwordFromFile, ','); // Read the password from the fourth column
			getline(iss, loyaltyPointsFromFile, ',');

			string lowercaseLoginID = loginID;
			string lowercaseLoginIDFromFile = loginIDFromFile;

			for (char& c : lowercaseLoginID) { // convert all the characters in the input to lowercase
				c = tolower(c);
			}
			for (char& c : lowercaseLoginIDFromFile) { // convert all the characters in the file to lowercase
				c = tolower(c);
			}
			if (lowercaseLoginID == lowercaseLoginIDFromFile && password == passwordFromFile) {
				customerID = stoi(customerIDFromFile); // convert customerID to from string to integer
				name = nameFromFile;
				loyaltyPoints = stoi(loyaltyPointsFromFile); // convert loyalty points to integer
				file.close();
				return true; // return true if customer exists
			}
		}
		file.close();
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}
	return false;
}

bool Customer::uniqueLoginID(const string& filename, const string& loginID)
{
	ifstream file(filename); // create  input file stream object called "file" and opens the file
	if (file.is_open()) {
		// Skip the header line
		string header;
		getline(file, header);

		string line;
		while (getline(file, line)) { // read each line from the file
			istringstream iss(line); // extract comma-separated values from each line
			string customerIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile, loyaltyPointsFromFile;

			// Read each field from the CSV line, separated by commas
			getline(iss, customerIDFromFile, ',');
			getline(iss, nameFromFile, ',');
			getline(iss, loginIDFromFile, ','); // Read the email from the third column
			getline(iss, passwordFromFile, ','); // Read the password from the fourth column
			getline(iss, loyaltyPointsFromFile, ',');

			string lowercaseLoginID = loginID; // login id from input
			string lowercaseLoginIDFromFile = loginIDFromFile; // login id from file

			for (char& c : lowercaseLoginID) { // convert all the characters in the input to lowercase
				c = tolower(c);
			}
			for (char& c : lowercaseLoginIDFromFile) { // convert all the characters in the file to lowercase
				c = tolower(c);
			}

			if (lowercaseLoginID == lowercaseLoginIDFromFile) { // if id already exists
				file.close();
				return false;
			}
		}
		file.close();
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}
	return true;
}

// Function to perform customer login
bool Customer::customerLogin(const string& filename) {
	string loginID, password;
	cout << "Enter your login credentials:\n";
	cout << "Login ID: ";
	cin >> ws;
	getline(cin, loginID);
	cout << "Password: ";
	cin >> ws;
	getline(cin, password);

	// Check if the customer exists with the given credentials
	if (customerExists(filename, loginID, password)) {
		cout << "Login successful!\n";
		return true;
	}
	else {
		cout << "Incorrect Login ID or password. Please try again.\n";
		return false;
	}
	return false;
}

void Customer::displayCustomerMenu() {
	cout << "Welcome " << name << "! " << "You have " << loyaltyPoints << " loyalty points." << endl;
	cout << "Here is the customer menu:" << endl;
	cout << "=====================================" << endl;
	cout << "           Customer Menu            " << endl;
	cout << "=====================================" << endl;
	cout << "1. Create a new order" << endl;
	cout << "2. View order history" << endl;
	cout << "3. Cancel an order" << endl;
	cout << "4. Log out" << endl;
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
		foodItemsTable.add(foodItem.getFoodItemID(), foodItem);
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

<<<<<<< HEAD
void Customer::addOrderItem(FoodItem fooditem, int quantity) {
	OrderItem order(fooditem, quantity);
	orderItemsList.insert(order);
=======
LinkedList<OrderItem> Customer::addOrderItem(FoodItem fooditem, int quantity) {
	OrderItem order(fooditem, quantity); 
	LinkedList<OrderItem> orderItemsList;
	orderItemsList.insert(order); // Insert the OrderItem into the LinkedList
	return orderItemsList;        // Return the modified LinkedList
>>>>>>> 0882c03aa081db288c311ed83b54a7a1a1b7dba8
}

int Customer::orderItemsMenu(const LinkedList<OrderItem>& orderItemsList, const LinkedList<Restaurant>& restaurants)
{
	// Calculate the padding to center the header
	int totalWidth = 45;
	string header = "Here are your ordered items:";
	int padding = (totalWidth - header.length()) / 2;

	// Print header
	cout << setw(padding + header.length()) << header << endl;

	cout << setw(10) << left << "Quantity" << setw(25) << left << "Food Item" << setw(15) << left << "Price" << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;

	for (int i = 0; i < orderItemsList.getLength(); i++) // loop through all the items in the orderitemslist list
	{
		OrderItem orderItem = orderItemsList.retrieve(i);
		FoodItem foodItem = orderItem.getFoodItem(); // retrieve the item
		double totalPrice = foodItem.getPrice() * orderItem.getQuantity(); // calculate price with the price * quantity of the item

		cout << setw(10) << left << orderItem.getQuantity()
			<< setw(25) << left << foodItem.getName()
			<< "$" << fixed << setprecision(2) << totalPrice << endl;
	}

	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;

	// Get the restaurant name for the first order item
	OrderItem firstOrderItem = orderItemsList.retrieve(0); // retrieve the first order item from the orderitemlist
	string restaurantName = firstOrderItem.getFoodItem().getRestaurantNameByID(firstOrderItem.getFoodItem().getRestaurantID(), restaurants); // get restaurant id of the food item
	cout << "1. Add more items from " << restaurantName << endl;

	cout << "2. Remove an item" << endl;
	cout << "3. Confirm order" << endl;
	cout << "4. Cancel Order (Exit)" << endl;
	cout << setfill('=') << setw(totalWidth) << "=" << setfill(' ') << endl;
	cout << "Enter your choice: ";

	return firstOrderItem.getFoodItem().getRestaurantID(); // return restaurant id user entered food from
}

void Customer::customerLoginMenu(Customer& customer) {
	cout << "\n-------------------------" << endl;
	cout << "      Customer Login      " << endl;
	cout << "-------------------------" << endl;
	if (customer.customerLogin("Customers.csv")) {
		waitForEnterKey();
		clearScreen();
		string customerOptionStr;
		do {
			customer.displayCustomerMenu();
			cin >> customerOptionStr;

			if (customerOptionStr == "1") {
				Restaurant restaurant;
				browseFoodItemsMenu(customer, restaurant);
			}
			else if (customerOptionStr == "2") {
				// Implement other options as needed
			}
			else if (customerOptionStr == "3") {
				// Implement other options as needed
			}
			else if (customerOptionStr == "4") {
				cout << "\nWe are logging you out now. Thank you!" << endl;
			}
			else {
				cout << "\nInvalid option. Please try again." << endl;
			}
		} while (customerOptionStr != "4");
	}
}

void Customer::customerRegisterMenu(Customer& customer)
{
	cout << "\n-------------------------" << endl;
	cout << "    Customer Register     " << endl;
	cout << "-------------------------" << endl;
	customer.registerCustomer("Customers.csv");
}

void Customer::browseFoodItemsMenu(Customer& customer, Restaurant& restaurant) {
	HashTable<int, FoodItem> foodItemsHashTable = customer.browseFoodItems("FoodItems.csv", restaurant.getAllRestaurants("Restaurants.csv"), restaurant.getRestaurantID());
	int foodItemLength = foodItemsHashTable.getLength();
	int foodItemChoice;

	do {
		cin >> foodItemChoice;

		// Change this part ***
		if (foodItemChoice >= 1 && foodItemChoice <= foodItemLength) {
			orderFoodItems(customer, restaurant, foodItemChoice, foodItemsHashTable);
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

void Customer::orderFoodItems(Customer& customer, Restaurant& restaurant, int foodItemChoice, HashTable<int, FoodItem>& foodItemsTable) {
	int quantity;
	FoodItem foodItem = foodItemsTable.get(foodItemChoice);

	do {
		cout << "Enter quantity for " << foodItem.getName() << ": ";
		cin >> quantity;

		if (quantity >= 1 && quantity <= 99) {
			// Use the existing orderItemsList from the member variable
			customer.addOrderItem(foodItem, quantity);
			cout << quantity << " " << foodItem.getName() << " added to your order successfully." << endl;
			waitForEnterKey();
			clearScreen();

			// Ask the customer if they want to add more food items to their order
			string addMoreFoodItemsStr;
			do {
				int restaurantID = customer.orderItemsMenu(customer.getOrderItemsList(), restaurant.getAllRestaurants("Restaurants.csv"));
				restaurant.setRestaurantID(restaurantID);
				cin >> addMoreFoodItemsStr;

				if (addMoreFoodItemsStr == "1") {
					browseFoodItemsMenu(customer, restaurant);
				}
				else if (addMoreFoodItemsStr == "2") {
					// Implement other options as needed
				}
				else if (addMoreFoodItemsStr == "3") {
					// Implement other options as needed
				}
				else if (addMoreFoodItemsStr == "4") {
					cout << "Ordered items cancelled." << endl;
					waitForEnterKey();
					clearScreen();
				}
				else {
					cout << "\nInvalid option. Please try again." << endl;
				}
			} while (addMoreFoodItemsStr != "4");
			break;
		}
		else {
			cout << "Invalid quantity. Please try again." << endl;
			quantity = -1;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (true);
}

void Customer::createOrder(const string& foodItemsFile, const string& ordersFile) {
	// TODO: Implement this. Read the food items file, let the customer choose an item, and add the order to the orders file.
}

void Customer::cancelOrder(const string& ordersFile) {
	// TODO: Implement this. Read the orders file, let the customer choose an order to cancel, and update the order status in the file.
}

void Customer::redeemPoints() {
	// TODO: Implement this. Deduct points from the customer's loyalty points and display a success message.
}