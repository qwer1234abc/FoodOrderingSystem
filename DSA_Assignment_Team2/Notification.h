#pragma once
#include <string>
#include <iostream>

using namespace std;

class Notification
{
private:
	int notificationID;
	int customerID;
	int restaurantID;
	string message;
	string date;

public:
	Notification();
	Notification(int notificationID, int customerID, int restaurantID, const string& message, const string& date);

	int getNotificationID() const;
	int getCustomerID() const;
	int getRestaurantID() const;
	string getMessage() const;
	string getDate() const;

};

