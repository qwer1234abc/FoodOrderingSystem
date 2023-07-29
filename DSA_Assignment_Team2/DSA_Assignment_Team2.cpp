#include <iostream>
#include "Customer.h"
#include "Admin.h"
using namespace std;


void displayMainMenu();
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main()
{
    string selectedOptionStr;

    do {
        displayMainMenu();
        cin >> selectedOptionStr;

        if (selectedOptionStr == "1") {
            cout << "\n-------------------------" << endl;
            cout << "      Customer Login      " << endl;
            cout << "-------------------------" << endl;
            Customer customer;

            if (customer.customerLogin("Customers.csv")) {
                customer.displayCustomerDetails();
                customer.displayCustomerMenu();
            }
        }
        else if (selectedOptionStr == "2") {
            cout << "\n-------------------------" << endl;
            cout << "    Customer Register     " << endl;
            cout << "-------------------------" << endl;
            Customer customer;

            customer.registerCustomer("Customers.csv");
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
        cout << "Press Enter to continue...";
        cin.ignore(); // Ignore any leftover newline characters in the input buffer
        cin.get();    // Wait for the user to press Enter before clearing the screen

    } while (selectedOptionStr != "4");

    return 0;
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
