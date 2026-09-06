#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
struct QueueNode {
	E data;
	QueueNode<E>* next;
};

template <typename E>
class LinkedQueue : public Queue<E> {
private:
	QueueNode<E>* front;
	QueueNode<E>* rear;
	int size;

public:
	LinkedQueue() {
		front = nullptr;
		rear = nullptr;
		size = 0;
	}
	~LinkedQueue() {
		clear();
	}
	void enqueue(E element) {
		QueueNode<E>* newNode = new QueueNode<E>();
		newNode->data = element;
		newNode->next = nullptr;

		if (isEmpty()) {
			front = newNode;
			rear = newNode;
		}
		else {
			rear->next = newNode;
			rear = newNode;
		}
		size++;
	}
	E dequeue() {
		if (isEmpty())
			throw runtime_error("Queue underflow.");

		QueueNode<E>* temp = front;
		E value = temp->data;

		front = front->next;
		if (front == nullptr)
			rear = nullptr;

		delete temp;
		size--;
		return value;
	}
	E frontValue() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		return front->data;
	}
	void clear() {
		while (!isEmpty())
			dequeue();
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[ ";
		QueueNode<E>* current = front;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << "]";
	}
};