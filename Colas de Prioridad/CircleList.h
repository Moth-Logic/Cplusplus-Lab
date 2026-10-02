#pragma once

#include <stdexcept>
#include <iostream>
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class CircleList {
private:
	Node<E>* current;
	int size;

public:
	void operator = (const CircleList<E>&) = delete;
	CircleList(const CircleList<E>&) = delete;
	CircleList() {
		current = nullptr;
		size = 0;
	}
	void insert(E element) {
		if (size == 0) {
			current = new Node<E>(element);
			current->next = current;
		}
		else {
			current->next = new Node<E>(element, current->next);
		}
		size++;
	}  
	void insertBack(E element) {
		insert(element);
		current = current->next;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("La lista está vacía");
		if (size == 1) {
			E result = current->next->element;
			delete current;
			size--;
			return result;
		}
		else {
			E result = current->element;
			Node<E>* temp = current;
			delete current;
			current->next = temp;
			size--;
			return result;
		}
	}
	E removeBack() {
		if (size == 0)
			throw runtime_error("La lista está vacía");
		if (size == 1) {
			remove();
		}
		else {
			Node<E>* temp = current;
			for (int i = 0; i < size; i++) {
				temp = temp->next;
				if (i == size - 1) {
					current = temp;
					remove();
				}
			}
		}
	}
	void clear() {
		for (int i = 0; i < size; i++) {
			Node<E>* temp = current->next;
			delete current;
			current = temp;
		}
		size = 0;
	}
	E getFront() {
		if (size == 0)
			throw runtime_error("Lista esta vacia");
		return current->next->element;
	}
	E getBack() {
		if (size == 0)
			throw runtime_error("Lista esta vacia");
		return current->element;

	}
	void next() {
		if (size == 0)
			throw runtime_error("Lista esta vacia");
		current = current->next;
	}
	void previous() {
		if (size == 0)
			throw runtime_error("Lista esta vacia");
		Node<E>* temp = current;
		for (int i = 0; i <= size - 1; i++) {
			temp = temp->next;
		}
		current = temp;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[";
		Node<E>* temp = current->next;
		while (temp != current) {
				cout << temp->element;
				if (temp->next != current)
					cout << ", ";
				temp = temp->next;
		}
		cout << "]" << endl;
	}
};

