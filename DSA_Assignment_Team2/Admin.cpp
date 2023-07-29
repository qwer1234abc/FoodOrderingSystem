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

// Function to login as an admin
void Admin::adminLogin(const string& filename) {
	string loginID, password;
	cout << "Enter your login credentials:\n";
	cout << "Login ID: ";
	cin >> ws;
	getline(cin, loginID);
	cout << "Password: ";
	cin >> ws;
	getline(cin, password);

	ifstream file(filename);

	if (file.is_open()) {
		// Skip the header line
		string header;
		getline(file, header);

		string line;
		while (getline(file, line)) { // read each line from the file
			istringstream iss(line); // extract comma-separated values from each line
			string adminIDFromFile, nameFromFile, loginIDFromFile, passwordFromFile, restaurantIDFromFile;

			// Read each field from the CSV line, separated by commas
			getline(iss, adminIDFromFile, ',');
			getline(iss, nameFromFile, ',');
			getline(iss, loginIDFromFile, ',');
			getline(iss, passwordFromFile, ',');
			getline(iss, restaurantIDFromFile, ',');

			string lowercaseLoginID = loginID; // login id from input
			string lowercaseLoginIDFromFile = loginIDFromFile; // login id from file

			for (char& c : lowercaseLoginID) { // convert all the characters in the input to lowercase
				c = tolower(c);
			}
			for (char& c : lowercaseLoginIDFromFile) { // convert all the characters in the file to lowercase
				c = tolower(c);
			}
			if (lowercaseLoginID == lowercaseLoginIDFromFile && password == passwordFromFile) {
				adminID = stoi(adminIDFromFile); // convert adminID to from string to integer
				name = nameFromFile; 
				restaurantID = stoi(restaurantIDFromFile); // convert restaurantID to from string to integer
				file.close();
				cout << "Login successful!\n";
				return;
			}
			else
			{
				cout << "Incorrect Login ID or password. Please try again.\n";

			}
		}
		file.close();
	}
	else {
		cout << "Error: Unable to open the file.\n";
	}
}