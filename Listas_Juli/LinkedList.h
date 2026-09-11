#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template<typename E>
class LinkedList : public List<E> {
private:
	Nodo<E>* head;
	Nodo<E>* current;
	Nodo<E>* tail;
	int size;
public:
	LinkedList() {
		tail = current = head = new Node<E>();
		size = 0;
	}
	~LinkedList() {
		clear();
		delete head;
	}
	void insert(E element) {
		new Node<E>(element, current->next);
		if(current == tail)
			tail = current->next;
		size++;
	}
	void append(E element) {
		tail = tail->next= new Node<E>(element);
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty")
		if size (current == tail)
			throw runtime_error("No current element")
		current->next->element = element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty")
		if (current == tail)
			 throw runtime_error("No current element")
		E result = current->next->element;
		Node<E>* temp = current->next->next;
		delete current->next;
		current->next = temp;
		size--;
		return result;
	}
	void clear() {
		while (head->next != nullptr) {
			Node<E>* temp = head->next->next;
			delete head->next;
			head->next = temp;
		}
		tail = current = head;
		size = 0
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("Index out of bounds")
		if (pos == size)
			throw runtime_error("No current element.");
		return current->element;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	void goToPost(int pos) {
		if(pos < 0 || pos > size)
			throw runtime_error("Index Out of Range.")
		current = head;
		for(int i = 0; i < pos; i++)
			 current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {

	}
	bool atEnd() {
		return
	}

};

