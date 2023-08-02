#pragma once
#include <iostream>
#include <string>
#include "Order.h"
#include "Queue.h"
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

	bool adminLogin(const string& filename);
	void displayAdminMenu();
	void AdminLoginMenu(Admin& admin);

};

