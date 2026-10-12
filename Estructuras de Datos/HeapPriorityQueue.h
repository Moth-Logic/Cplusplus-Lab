#pragma once

#include <stdexcept>
#include <iostream>
#include "PriorityQueue.h"
#include "MinHeap.h"
#include "Pair.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
	MinHeap<Pair<int, E>>* pairs;

public:
	HeapPriorityQueue(int max = DEFAULT_MAX) {
		pairs = new MinHeap<Pair<int, E>>(max);
	}
	~HeapPriorityQueue() {
		delete pairs;
	}
	void insert(E element, int priority) {
		Pair<int, E> p(priority, element);
		pairs->insert(p);
	}
	E min() {
		Pair<int, E> p = pairs->first();
		return p.value;
	}
	E removeMin() {
		Pair<int, E> p = pairs->removeFirst();
		return p.value;
	}
	void clear() {
		pairs->clear();
	}
	int getSize() {
		return pairs->getSize();
	}
	bool isEmpty() {
		return pairs->getSize() == 0;
	}
	void print() {
		pairs->print();
	}
};

