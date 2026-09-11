#pragma once

#include <iostream>
#include <stdexcept>
#include "Stack.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

// LinkedStack: a stack implemented as a singly-linked list.
// The 'top' pointer always points to the most recently pushed element.
// Push creates a new node and makes it the new top. Pop removes the top
// and moves the pointer to the next node. No fixed capacity — it grows
// as needed (until you run out of memory).
template<typename E>
class LinkedStack : public Stack<E> {
private:
	Node<E>* top;  // Pointer to the top node (the most recently pushed element)
	int size;      // Current number of elements

public:
	// Constructor: empty stack has no nodes, so top is nullptr.
	LinkedStack() {
		top = nullptr;
		size = 0;
	}

	// Destructor: clean up all nodes to prevent memory leaks.
	~LinkedStack() {
		clear();
	}

	// Push: create a new node that points to the current top, then update top.
	// This is O(1) — we just create one node and update one pointer.
	void push(E element) {
		top = new Node<E>(element, top);  // New node's 'next' = old top
		size++;
	}

	// Pop: save the top element, move top to the next node, delete the old top.
	E pop() {
		if (size == 0)
			throw runtime_error("Stack is empty");
		E result = top->element;    // Save the data we're about to remove
		Node<E>* temp = top->next;  // Save pointer to the next node
		delete top;                 // Free the old top node
		top = temp;                 // Move top to the next node
		size--;
		return result;
	}

	// Peek at the top element without removing it.
	E topValue() {
		if (size == 0)
			throw runtime_error("Stack is empty");
		return top->element;
	}

	// Clear: walk through the list, deleting each node one by one.
	void clear() {
		Node<E>* temp;
		while (top != nullptr) {
			temp = top->next;  // Save the next node before deleting
			delete top;        // Free the current node
			top = temp;        // Move to the next node
		}
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	// Print from top to bottom by walking the linked list.
	void print() {
		cout << "[";
		Node<E>* temp = top;
		while (temp != nullptr) {
			cout << temp->element;
			if (temp->next != nullptr)
				cout << ", ";
			temp = temp->next;  // Walk to the next node
		}
		cout << "]" << endl;
	}
};