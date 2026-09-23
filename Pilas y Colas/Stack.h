#pragma once

// Stack (LIFO) abstract interface — Last In, First Out.
// Think of a stack of plates: you always add to the top and remove from the top.
// This is an abstract class, so you must use a concrete implementation
// like ArrayStack or LinkedStack.
// Copy constructor and assignment operator are deleted (= delete) because
// managing shared pointers to the same stack data would cause bugs.
template <typename E>
class Stack {
public:
	Stack() {}
	Stack(const Stack<E>&) = delete;              // Prevent copying (no shallow copies of stacks)
	void operator = (const Stack<E>&) = delete;   // Prevent assignment for the same reason
	virtual ~Stack() {}
	virtual void push(E element) = 0;   // Add an element to the top of the stack
	virtual E pop() = 0;               // Remove and return the top element
	virtual E topValue() = 0;          // Peek at the top element without removing it
	virtual void clear() = 0;          // Remove all elements
	virtual bool isEmpty() = 0;        // Check if the stack is empty
	virtual int getSize() = 0;         // Get the number of elements
	virtual void print() = 0;          // Print all elements (top to bottom)
};