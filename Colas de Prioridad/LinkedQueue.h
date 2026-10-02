#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedQueue : public Queue<E> {
private:
	Node<E>* front;
	Node<E>* back;
	int size;

public:
	LinkedQueue() {
		front = new Node<E>();
		back = front;
		size = 0;
	}
	~LinkedQueue() {
		clear();
		delete front;
	}
	void enqueue(E element) {
		back->next = new Node<E>(element);
		back = back->next;
		size++;
	}
	E dequeue() {
		if (size == 0)
			throw runtime_error("La cola esta vacia.");

		Node<E>* temp = front->next;
		E result = temp->element;
		front->next = temp->next;
		if (front->next == nullptr)
			back = front;
		delete temp;
		size--;
		return result;
	}
	E frontValue() {
		if (size == 0)
			throw runtime_error("La cola esta vacia.");
		return front->next->element;
	}
	void clear() {
		while (front->next != nullptr) {
			Node<E>* temp = front->next;
			front->next = temp->next;
			delete temp;
		}
		size = 0;
		back = front;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[";
		Node<E>* temp = front->next;
		while (temp != nullptr) {
			cout << temp->element;
			if (temp->next != nullptr)
				cout << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};

