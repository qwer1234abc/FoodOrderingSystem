# Food Ordering System

This console application was created as an assignment for the Data Structures and Algorithms module at Ngee Ann Polytechnic. This assigment tests the understanding of data structure and algorithms in C++.

## Purpose

The purpose of this assignment is to demonstrate the use of data structures and algorithms to develop a food ordering system with features like user registration, browsing menu, placing orders, viewing order history etc.

## Features

**Customer:**

- Register new account
- Login  
- View all food menu offerings
- Create new order
    - Add/remove food items
    - Confirm order
- View order history
- Cancel unpaid orders
- View notifications

**Admin:**  

- Login
- View incoming orders
- Update order status
- View customer information
- View revenue report

## Data Structures Used

- Linked List 
- Queue
- Hash Table
- Stack
- Array

## Algorithms Used

- Linear Search
- Quick Sort

## Classes

- `Customer`: Handles registration, login and order placement
- `Admin`: Handles order processing and analytics  
- `Order`: Represents order with details like items ordered, status, etc
- `OrderItem`: Represents list of food items
- `Restaurant`: Represents list of restaurants
- `FoodItem`: Represents a menu item 
- `Notification`: Message for order status updates

## Usage

The application presents text-based menus and prompts to guide the user.

Sample usage flow:

**Customer**

1. Register
2. Login
3. Browse menu  
4. Add items to new order
5. Confirm order
6. View notifications 
7. View order history

**Admin** 

1. Login 
2. View incoming orders
3. Change order status  
4. View customer info
5. View revenue metrics

