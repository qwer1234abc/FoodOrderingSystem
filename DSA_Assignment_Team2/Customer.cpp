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
	cout << "1. Browse food selections" << endl;
	cout << "2. Create a new order" << endl;
	cout << "3. Cancel an order" << endl;
	cout << "4. Log out" << endl;
	cout << "=====================================" << endl;
	cout << "Enter your choice: ";
}

void Customer::handleCustomerChoice(int choice, const string& filename) {
	switch (choice) {
	case 1:
		browseFoodItems(filename);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		redeemPoints();
		break;
	case 5:
		cout << "Logging out..." << endl;
		break;
	default:
		cout << "Invalid choice!" << endl;
		break;
	}
}

void Customer::browseFoodItems(const string& filename) {
	// TODO: Implement this. Read the food items file and display the items.
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