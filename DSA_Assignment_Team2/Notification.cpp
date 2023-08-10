#include "Notification.h"

Notification::Notification() {}

Notification::Notification(int id, int cID, int rID, const string& m, const string& d)
{
	notificationID = id;
	customerID = cID;
	restaurantID = rID;
	message = m;
	date = d;
}

int Notification::getNotificationID() const
{
	return notificationID;
}

int Notification::getCustomerID() const
{
	return customerID;
}

int Notification::getRestaurantID() const
{
	return restaurantID;
}

string Notification::getMessage() const
{
	return message;
}

string Notification::getDate() const
{
	return date;
}

