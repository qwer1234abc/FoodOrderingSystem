#include "Notification.h"
#include <fstream>
#include <iomanip>
#include <sstream>

Notification::Notification() {}

Notification::Notification(int cID, int rID, const string& m)
{
	customerID = cID;
	restaurantID = rID;
	message = m;
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

// Return a stack with all notifications
Stack<Notification> Notification::getAllNotifications(const string& filename)
{
	Stack<Notification> notifications;
	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "File not found!" << endl;
		return notifications;
	}

	string header;
	getline(file, header);

	string line;

	while (getline(file, line))
	{
		stringstream ss(line);
		string messageID, customerID, restaurantID, message, date;

		getline(ss, customerID, ',');
		getline(ss, restaurantID, ',');
		getline(ss, message, ',');

		Notification notification(stoi(customerID), stoi(restaurantID), message);
		notifications.push(notification);
	}

	file.close();
	return notifications;
}

// Return a stack of notifications that belongs to a customer
Stack<Notification> Notification::filterCustomerNotifications(Stack<Notification>& notifications, int customerID)
{
	Stack<Notification> filteredNotifications;
	Stack<Notification> tempNotifications;

	while (!notifications.isEmpty())
	{
		Notification notification = notifications.pop();
		if (notification.getCustomerID() == customerID)
		{
			filteredNotifications.push(notification);
		}
		tempNotifications.push(notification);
	}

	while (!tempNotifications.isEmpty())
	{
		notifications.push(tempNotifications.pop());  // Push the notifications back in the same order
	}

	// Reverse the filtered notifications to maintain the original order
	Stack<Notification> finalFilteredNotifications;
	while (!filteredNotifications.isEmpty())
	{
		finalFilteredNotifications.push(filteredNotifications.pop());
	}

	return finalFilteredNotifications;
}





