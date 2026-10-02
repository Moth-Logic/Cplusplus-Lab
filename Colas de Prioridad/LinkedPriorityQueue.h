#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include "PriorityQueue.h"
#include "LinkedQueue.h"

template <typename E>
class LinkedPriorityQueue : public PriorityQueue<E> {
private:
	static constexpr int DEFAULT_PRIORITIES = 20;
	std::unique_ptr<LinkedQueue<E>[]> queues;
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
	explicit LinkedPriorityQueue(int priorities = DEFAULT_PRIORITIES)
		: queues(nullptr), priorities(priorities), size(0) {
		if (priorities < 1)
			throw std::invalid_argument("Priority count must be positive.");
		queues = std::make_unique<LinkedQueue<E>[]>(priorities);
	}

	~LinkedPriorityQueue() override = default;

	void insert(E element, int priority) override {
		if (priority < 0 || priority >= priorities)
			throw std::invalid_argument("Priority is outside the configured range.");
		queues[priority].enqueue(element);
		size++;
	}

	E min() override {
		int index = findFirstNonEmpty();
		if (index == -1)
			throw std::runtime_error("Priority queue is empty.");
		return queues[index].frontValue();
	}

	E removeMin() override {
		int index = findFirstNonEmpty();
		if (index == -1)
			throw std::runtime_error("Priority queue is empty.");
		E value = queues[index].dequeue();
		size--;
		return value;
	}

	void clear() override {
		for (int i = 0; i < priorities; i++)
			queues[i].clear();
		size = 0;
	}

	bool isEmpty() override {
		return size == 0;
	}

	int getSize() override {
		return size;
	}

	void print() override {
		for (int i = 0; i < priorities; i++) {
			std::cout << i << ": ";
			queues[i].print();
			std::cout << std::endl;
		}
	}
};