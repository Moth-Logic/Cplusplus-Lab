#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E> 
class ArrayQueue : public Queue<E> {
private:
	E* elements;
	int front;
	int max;
	int size;
	int back;

public:
	ArrayQueue(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		front = back = size = 0;
	}
	~ArrayQueue() {
		delete[] elements;
	}
	void enqueue(E element) {
		if (size == max)
			throw runtime_error("Queue is full.");
		elements[back] = element;
		back = (back + 1) % max;
		size++;
	}
	E dequeue() {
		if (size == 0)
			throw runtime_error("Queue is empty.");
		front = (front + 1) % max;
		size--;
		return elements[(front + max - 1) % max];
	}
	E frontValue() {
		if (size == 0)
			throw runtime_error("Queue is empty.");
		return elements[front];
	}
	void clear() {
		front = back = size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[";
		for (int i = 0; i != back; i++) {
			cout << elements[(front+1) % max];
			if (i < size - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
};

