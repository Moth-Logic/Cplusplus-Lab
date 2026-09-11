#pragma once

// Queue (FIFO) abstract interface — First In, First Out.
// Elements enter at the back and leave from the front, like a line at a store.
// Copy and assignment are deleted to prevent accidental sharing of queue data.
template <typename E>
class Queue {
public:
	Queue(const Queue<E>&) = delete;              // Prevent copying
	void operator= (const Queue<E>&) = delete;   // Prevent assignment

	Queue() {}
	virtual ~Queue() {}

	virtual void enqueue(E element) = 0;   // Add element to the back
	virtual E dequeue() = 0;               // Remove and return the front element
	virtual E frontValue() = 0;            // Peek at the front element
	virtual void clear() = 0;              // Remove all elements
	virtual bool isEmpty() = 0;            // Check if the queue is empty
	virtual int getSize() = 0;             // Get the number of elements
	virtual void print() = 0;              // Print all elements
};