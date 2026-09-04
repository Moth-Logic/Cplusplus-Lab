#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class LinkedQueue : public Queue<E> {
private:
	Node<E>* front;
	Node<E>* back;
	int size;

public:
	LinkedQueue() {
		front = back = new Node<E>();
		size = 0;
	}

	~LinkedQueue() {
		clear();
		delete front;
	}

	void enqueue(E element) {
		back = back->next = new Node<E>(element);
		size++;
	}

	E dequeue() {
		if (size == 0)
			throw runtime_error("Queue is empty");

		E result = front->next->element;
		Node<E>* temp = front->next->next;
		delete front->next;
		front->next = temp;

		if (size == 1) {
			back = front;
			cout << "Sic seben" << endl;
		}

		size--;
		return result;
	}

	E frontValue() {
		if (size == 0)
			throw runtime_error("Queue is empty");

		cout << "Bro el elemento del frente es:" << endl;
		return front->next->element;
	}

	void clear() {
		while (front->next != nullptr) {
			Node<E>* temp = front->next;
			front->next = temp->next;
			delete temp;
		}
		back = front;
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	void print() {
		if (size == 0) {
			cout << "La cola esta vacia." << endl;
		}
		else {
			Node<E>* current = front->next;
			cout << "Contenido de la cola: ";
			while (current != nullptr) {
				cout << current->element << " ";
				current = current->next;
			}
			cout << endl;
		}
	}
};