#pragma once
#include <iostream>
#include <string>

using namespace std;

class Customer {
private:
    int customerID;
    string name;
    string loginID;
    string password;
    int loyaltyPoints;

public:
    Customer();
    Customer(int id, const string& n, const string& l, const string& p, int lp);

    // Getters
    int getCustomerID() const;
    string getName() const;
    string getLoginID() const;
    string getPassword() const;
    int getLoyaltyPoints() const;

    // Member functions
    void registerCustomer(const string& filename);
    bool customerExists(const string& filename, const string& loginID, const string& password);
    bool uniqueLoginID(const string& filename, const string& loginID);
    bool customerLogin(const string& filename);


    void displayCustomerMenu();  // To show the customer menu after logging in
    void browseFoodItems(const string& filename);  // To browse all food items
    void createOrder(const string& foodItemsFile, const string& ordersFile);  // To create a new order
    void cancelOrder(const string& ordersFile);  // To cancel an existing order
    void redeemPoints();
};