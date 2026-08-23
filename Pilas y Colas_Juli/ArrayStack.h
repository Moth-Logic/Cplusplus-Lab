#pragma once

#define DEFAULT_STACK_SIZE 1024

#include "Stack.h"
#include <stdexcept>

using std::runtime_error

template <typename E>
class ArrayStack : public Stack {
private:
	E* elements;
	int max;
	int size;

public:
	ArrayStack(int max = DEFAULT_STACK_SIZE) {
		if (max < 1) {
			throw runtime_error("Invalid stack size");
		elements = new E[max];
		this->max = max;
		size = 0;
	}
		~ArrayStack() {
			delete[] elements;
	}
};

