#pragma once

// PriorityQueue abstract interface — elements are removed by priority, not insertion order.
// Lower priority number = higher urgency (priority 0 is the most urgent).
// Think of an emergency room: critical patients (priority 0) are seen before minor ones (priority 4).
template <typename E>
class PriorityQueue {
public:
	virtual void insert(E element, int priority) = 0;  // Add element with a given priority level
	virtual E min() = 0;                               // Peek at the highest-priority element
	virtual E removeMin() = 0;                         // Remove and return the highest-priority element
	virtual void clear() = 0;                          // Remove all elements
	virtual bool isEmpty() = 0;                        // Check if the queue is empty
	virtual int getSize() = 0;                         // Get the number of elements
	virtual void print() = 0;                          // Print all priority levels and their elements
	virtual ~PriorityQueue() {}
};