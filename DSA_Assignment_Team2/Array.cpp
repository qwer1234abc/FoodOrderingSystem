#include "Array.h"

using namespace std;

Array::Array() {
	items = nullptr;
	size = 0;
	length = 0;
}

Array::Array(int size) {
	this->size = size;
	items = new FoodItem[size];
	length = 0;
}

Array::~Array() {
	delete[] items;
}

bool Array::isEmpty() const {
	return length == 0;
}

int Array::getLength() const {
	return length;
}

FoodItem Array::retrieve(int index) const {
	if (index < 0 || index >= length) {
		throw out_of_range("Index out of range");
	}

	return items[index];
}

void Array::insert(FoodItem item) {
	if (length == size) {
		throw out_of_range("Array is full");
	}

	items[length] = item;
	length++;
}

void Array::quickSort(int left, int right) {
	if (left < right) {
		int pivot = partition(left, right);
		quickSort(left, pivot - 1);
		quickSort(pivot + 1, right);
	}
}

int Array::partition(int left, int right) {
	FoodItem pivot = items[right];
	int i = left - 1;

	for (int j = left; j < right; j++) {
		if (items[j].getFoodItemID() < pivot.getFoodItemID()) {
			i++;
			swap(items[i], items[j]);
		}
	}

	swap(items[i + 1], items[right]);
	return i + 1;
}