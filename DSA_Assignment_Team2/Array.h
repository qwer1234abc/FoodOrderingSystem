#pragma once
#include <iostream>
#include <string>
#include "FoodItem.h"
class Array
{
private:
	FoodItem* items;
	int size;
	int length;

public:
	Array();
	Array(int size);
	~Array();

	bool isEmpty() const;
	int getLength() const;
	FoodItem retrieve(int index) const;
	void insert(FoodItem item);
	void quickSort(int left, int right);
	int partition(int left, int right);
};

