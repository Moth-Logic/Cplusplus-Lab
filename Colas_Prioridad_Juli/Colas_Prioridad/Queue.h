#pragma once

// Queue (FIFO) abstract interface — First In, First Out.
// Elements enter at the back and leave from the front, like a line at a store.
// This is an abstract class (= 0 means pure virtual), so you can't create
// a Queue directly — you must use a concrete implementation like LinkedQueue.
template <typename E>
class Queue {
public:
	virtual void enqueue(E element) = 0;   // Add element to the back of the queue
	virtual E dequeue() = 0;               // Remove and return the front element
	virtual E frontValue() = 0;            // Peek at the front element without removing it
	virtual void clear() = 0;              // Remove all elements from the queue
	virtual bool isEmpty() = 0;            // Returns true if the queue has no elements
	virtual int getSize() = 0;             // Returns how many elements are in the queue
	virtual void print() = 0;              // Print all elements (for debugging)
	virtual ~Queue() {}                    // Virtual destructor ensures proper cleanup of derived classes
};