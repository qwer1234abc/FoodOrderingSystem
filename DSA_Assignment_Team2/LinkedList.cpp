#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;

LinkedList::LinkedList() {
	head = nullptr;
	size = 0;
}

LinkedList::~LinkedList() {
	Node* temp = head;
	while (head != nullptr) {
		head = head->next;
		delete temp;
		temp = head;
	}
}

bool LinkedList::isEmpty() const {
	return size == 0;
}

int LinkedList::getLength() const {
	return size;
}

bool LinkedList::retrieve(int index, OrderItem& orderItem) const {
	if (index < 0 || index >= size) {
		return false;
	}

	Node* current = head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	orderItem = current->item;
	return true;
}

bool LinkedList::insert(OrderItem orderItem) {
	Node* newNode = new Node;
	newNode->item = orderItem;
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

bool LinkedList::remove(int index) {
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
