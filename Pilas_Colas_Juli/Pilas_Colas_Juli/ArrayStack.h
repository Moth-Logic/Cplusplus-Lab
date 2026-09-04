#pragma once

#define DEFAULT_MAX 1024

#include <stdexcept>
#include <iostream>
#include "Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack<E> {
private:
	E* elements;
	int max;
	int size;

public:
	ArrayStack(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("invalid max size.");
		elements = new E[max];
		this->max = max;
		size = 0;
	}
	~ArrayStack() {
		delete[] elements;
	}
	void push(E element) {
		if (size == max)
			throw runtime_error("Stack overflow.");
		elements[size] = element;
		size++;
	}
	E pop() {
		if (size == 0)
			throw runtime_error("Stack underflow.");
		size--;
		return elements[size];
	}
	E topValue() {
		if (size == 0)
			throw runtime_error("Stack is empty.");
		return elements[size - 1];
	}
	void clear() {
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
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