#include "LinkedList.h"
#include <iostream>
#include <string>
#include "Restaurant.h"
#include "OrderItem.h"

using namespace std;

template <class T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node* temp = head;
	while (head != nullptr) {
		head = head->next;
		delete temp;
		temp = head;
	}
}

template <class T>
bool LinkedList<T>::isEmpty() const {
	return size == 0;
}

template <class T>
int LinkedList<T>::getLength() const {
	return size;
}

template <class T>
bool LinkedList<T>::retrieve(int index, T& item) const {
	if (index < 0 || index >= size) {
		return false;
	}

	Node* current = head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	item = current->item;
	return true;
}

template <class T>
T LinkedList<T>::retrieve(int index) const {
	if (index < 0 || index >= size) {
		throw out_of_range("Index out of range");
	}

	Node* current = head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	return current->item;
}

template <class T>
bool LinkedList<T>::insert(T item) {
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}

	size++;
	return true;
}

template <class T>
bool LinkedList<T>::remove(int index) {
	if (index < 0 || index >= size) {
		return false;
	}

	Node* current = head;
	Node* previous = nullptr;
	for (int i = 0; i < index; i++) {
		previous = current;
		current = current->next;
	}

	if (previous == nullptr) {
		head = current->next;
	}
	else {
		previous->next = current->next;
	}

	delete current;
	size--;
	return true;
}

template <class T>
void LinkedList<T>::clear() {
	Node* temp = head;
	while (head != nullptr) {
		head = head->next;
		delete temp;
		temp = head;
	}
	size = 0;
}

// Explicit instantiation for supported types
template class LinkedList<Restaurant>;
template class LinkedList<OrderItem>;