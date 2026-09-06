#pragma once

#define DEFAULT_PRIORITIES 20

#include <stdexcept>
#include <iostream>
#include "PriorityQueue.h"
#include "LinkedQueue.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E> {
private:
	LinkedQueue<E>* queues;
	int priorities;
	int size;

	int findFirstNonEmpty() {
		for (int i = 0; i < priorities; i++) {
			if (!queues[i].isEmpty())
				return i;
		}
		return -1;
	}

public:
	LinkedPriorityQueue(int priorities = DEFAULT_PRIORITIES) {
		if (priorities < 1)
			throw runtime_error("invalid priorities amount.");
		queues = new LinkedQueue<E>[priorities];
		this->priorities = priorities;
		size = 0;
	}
	~LinkedPriorityQueue() {
		delete[] queues;
	}
	void insert(E element, int priority) {
		if (priority < 0 || priority >= priorities)
			throw runtime_error("invalid priority.");
		queues[priority].enqueue(element);
		size++;
	}
	E min() {
		int index = findFirstNonEmpty();
		if (index == -1)
			throw runtime_error("Priority queue is empty.");
		return queues[index].frontValue();
	}
	E removeMin() {
		int index = findFirstNonEmpty();
		if (index == -1)
			throw runtime_error("Priority queue is empty.");
		E value = queues[index].dequeue();
		size--;
		return value;
	}
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
	void print() {
		for (int i = 0; i < priorities; i++) {
			cout << i << ": ";
			queues[i].print();
			cout << endl;
		}
	}
};