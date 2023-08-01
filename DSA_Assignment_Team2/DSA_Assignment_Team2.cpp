#include <iostream>
#include "Customer.h"
#include "Admin.h"
#include "LinkedList.h"

using namespace std;


void displayMainMenu();

void clearScreen() {
	cout << "\033[2J\033[1;1H";
}

void waitForEnterKey() {
	cout << "Press Enter to continue...";
	cin.ignore(); // Ignore any leftover newline characters in the input buffer
	cin.get();    // Wait for the user to press Enter before continuing
}

int main()
{
	string selectedOptionStr;

	do {
		displayMainMenu();
		cin >> selectedOptionStr;

		if (selectedOptionStr == "1") {
			Customer customer;
<<<<<<< HEAD
			customer.customerLoginMenu(customer);
=======

			if (customer.customerLogin("Customers.csv")) {
				waitForEnterKey();
				clearScreen();
				string customerOptionStr;
				do
				{
					customer.displayCustomerMenu();
					cin >> customerOptionStr;

					if (customerOptionStr == "1")
					{
						Restaurant restaurant;
						HashTable<int, FoodItem> foodItemsHashTable = customer.browseFoodItems("FoodItems.csv", restaurant.getAllRestaurants("Restaurants.csv"), restaurant.getRestaurantID());
						int foodItemLength = foodItemsHashTable.getLength();
						int foodItemChoice;

						do
						{
							cin >> foodItemChoice;

							if (foodItemChoice >= 1 && foodItemChoice <= foodItemLength)
							{
								int quantity;
								FoodItem foodItem = foodItemsHashTable.get(foodItemChoice);

								do {
									cout << "Enter quantity for " << foodItem.getName() << ": ";
									cin >> quantity;

									if (quantity >= 1 && quantity <= 99)
									{
										// Add the selected food item to the customer's order
										LinkedList<OrderItem> orderItemsList = customer.addOrderItem(foodItem, quantity);
										cout << quantity << " " << foodItem.getName() << " added to your order successfully." << endl;
										waitForEnterKey();
										clearScreen();
										// Ask the customer if they want to add more food items to their order
										string addMoreFoodItemsStr;
										do {
											
											int restaurantID = customer.orderItemsMenu(orderItemsList, restaurant.getAllRestaurants("Restaurants.csv")); // get the restaurant id user ordered food from
											cin >> addMoreFoodItemsStr;

											if (addMoreFoodItemsStr == "1")
											{
												foodItemsHashTable = customer.browseFoodItems("FoodItems.csv", restaurant.getAllRestaurants("Restaurants.csv"), restaurantID); // only get the food items from the same restaurant
											}
											else if (addMoreFoodItemsStr == "2")
											{

											}
											else if (addMoreFoodItemsStr == "3")
											{

											}
											else if (addMoreFoodItemsStr == "4")
											{
												cout << "Ordered items cancelled." << endl;
												waitForEnterKey();
												clearScreen();
											}
											else
											{
												cout << "\nInvalid option. Please try again." << endl;
											}

										} while (addMoreFoodItemsStr != "4");
										break;
									}
									else
									{
										cout << "Invalid quantity. Please try again." << endl;
										quantity = -1;
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
								} while (true);

								break;
							}
							else
							{
								cout << "Invalid option. Please try again: ";
								foodItemChoice = -1;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
						} while (true);
					}

					else if (customerOptionStr == "2")
					{

					}
					else if (customerOptionStr == "3")
					{

					}
					else if (customerOptionStr == "4")
					{
						cout << "\nWe are logging you out now. Thank you!" << endl;
					}
					else
					{
						cout << "\nInvalid option. Please try again." << endl;
					}
				} while (customerOptionStr != "4");
			}
>>>>>>> 0882c03aa081db288c311ed83b54a7a1a1b7dba8
		}
		else if (selectedOptionStr == "2") {
			Customer customer;
			customer.customerRegisterMenu(customer);
		}
		else if (selectedOptionStr == "3") {
			cout << "\n-------------------------" << endl;
			cout << "       Admin Login        " << endl;
			cout << "-------------------------" << endl;
			Admin admin;

			admin.adminLogin("Admins.csv");
		}
		else if (selectedOptionStr == "4") {
			cout << "\nThank you for using our app. Goodbye!" << endl;
		}
		else {
			cout << "\nInvalid option. Please try again." << endl;
		}
		waitForEnterKey();

	} while (selectedOptionStr != "4");
}

void displayMainMenu() {
	clearScreen();
	cout << "==================================" << endl;
	cout << "        WELCOME TO OUR APP        " << endl;
	cout << "==================================" << endl;
	cout << "1. Customer Login" << endl;
	cout << "2. Customer Register" << endl;
	cout << "3. Admin Login" << endl;
	cout << "4. Exit" << endl;
	cout << "==================================" << endl;
	cout << "Enter your choice: ";
}
