#pragma once
#include <string>
#include <iostream>
#include "Stack.h"

using namespace std;

class Notification
{
private:
	int customerID;
	int restaurantID;
	string message;

public:
	Notification();
	Notification(int customerID, int restaurantID, const string& message);

	int getCustomerID() const;
	int getRestaurantID() const;
	string getMessage() const;

	Stack<Notification> getAllNotifications(const string& filename);
	Stack<Notification> filterCustomerNotifications(Stack<Notification>& notifications, int customerID);


};

