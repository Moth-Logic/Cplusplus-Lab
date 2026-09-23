#pragma once

#define DEFAULT_MAX 1024

#include <stdexcept>
#include <iostream>
#include "Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

// ArrayStack: a stack implemented using a plain dynamic array.
// Elements are stored contiguously in memory, and 'size' tracks how many
// are currently in use. Push adds at index 'size', pop removes from 'size-1'.
// This gives O(1) push/pop, but the stack has a fixed maximum capacity.
template <typename E>
class ArrayStack : public Stack<E> {
private:
	E* elements;  // Dynamic array that holds the stack data
	int max;      // Maximum capacity of the array
	int size;     // Current number of elements (top of stack = elements[size-1])

public:
	// Constructor: allocate an array of 'max' elements. Default capacity is 1024.
	ArrayStack(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("invalid max size.");
		elements = new E[max];  // Allocate the array on the heap
		this->max = max;
		size = 0;  // Stack starts empty
	}

	// Destructor: free the array to prevent memory leaks.
	~ArrayStack() {
		delete[] elements;
	}

	// Push: add an element to the top of the stack.
	// If the array is full, we throw an error (no automatic resizing).
	void push(E element) {
		if (size == max)
			throw runtime_error("Stack overflow.");
		elements[size] = element;  // Place the new element at the next available slot
		size++;
	}

	// Pop: remove and return the top element.
	// We just decrement size — the old data stays in memory but is "forgotten".
	E pop() {
		if (size == 0)
			throw runtime_error("Stack underflow.");
		size--;                     // Shrink the stack by one
		return elements[size];      // Return the element that was on top
	}

	// Peek at the top element without removing it.
	E topValue() {
		if (size == 0)
			throw runtime_error("Stack is empty.");
		return elements[size - 1];  // The top is always at index size-1
	}

	// Clear: just reset size to 0. The old data stays in the array but is ignored.
	void clear() {
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	// Print the stack from top to bottom: [top, ..., bottom].
	void print() {
		cout << "[";
		for (int i = size - 1; i >= 0; i--) {
			cout << elements[i];
			if (i != 0)
				cout << ", ";
		}
		cout << "]" << endl;
	}
};