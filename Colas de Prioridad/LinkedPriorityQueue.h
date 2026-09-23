#pragma once

#define DEFAULT_PRIORITIES 20

#include <stdexcept>
#include <iostream>
#include "PriorityQueue.h"
#include "LinkedQueue.h"

using std::runtime_error;
using std::cout;
using std::endl;

// LinkedPriorityQueue: implements a priority queue using an array of LinkedQueues.
// The idea is simple: we have one queue per priority level. Priority 0 is the
// most urgent, so we always check queues[0] first, then queues[1], etc.
// This is called a "bucket" or "multi-queue" approach — it's not the fastest
// (O(k) to find the first non-empty queue where k = number of priorities),
// but it's very simple and works great when k is small (like 5 triage levels).
template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E> {
private:
	LinkedQueue<E>* queues;  // Array of queues, one per priority level
	int priorities;          // How many priority levels exist (e.g., 5 for triage)
	int size;                // Total number of elements across all queues

	// Scan from priority 0 upward to find the first non-empty queue.
	// Returns the index of that queue, or -1 if all queues are empty.
	int findFirstNonEmpty() {
		for (int i = 0; i < priorities; i++) {
			if (!queues[i].isEmpty())
				return i;  // Found the highest-priority non-empty queue
		}
		return -1;  // All queues are empty
	}

public:
	// Constructor: create an array of 'priorities' empty LinkedQueues.
	LinkedPriorityQueue(int priorities = DEFAULT_PRIORITIES) {
		if (priorities < 1)
			throw runtime_error("invalid priorities amount.");
		queues = new LinkedQueue<E>[priorities];  // Dynamic array of queues
		this->priorities = priorities;
		size = 0;
	}

	// Destructor: free the array of queues. Each LinkedQueue's destructor
	// handles cleaning up its own nodes.
	~LinkedPriorityQueue() {
		delete[] queues;
	}

	// Insert an element into the queue at the specified priority level.
	void insert(E element, int priority) {
		if (priority < 0 || priority >= priorities)
			throw runtime_error("invalid priority.");
		queues[priority].enqueue(element);  // Add to the appropriate bucket
		size++;
	}

	// Peek at the highest-priority element (the front of the first non-empty queue).
	E min() {
		int index = findFirstNonEmpty();
		if (index == -1)
			throw runtime_error("Priority queue is empty.");
		return queues[index].frontValue();  // Look at the front without removing
	}

	// Remove and return the highest-priority element.
	E removeMin() {
		int index = findFirstNonEmpty();
		if (index == -1)
			throw runtime_error("Priority queue is empty.");
		E value = queues[index].dequeue();  // Remove from the front of the highest-priority queue
		size--;
		return value;
	}

	// Clear all elements from all priority queues.
	void clear() {
		for (int i = 0; i < priorities; i++)
			queues[i].clear();
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	// Print each priority level and its queue contents.
	void print() {
		for (int i = 0; i < priorities; i++) {
			cout << i << ": ";
			queues[i].print();
			cout << endl;
		}
	}
};