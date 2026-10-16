#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

// Doubly linked list with a head sentinel and a tail pointer to the last
// real node. The cursor (current) points to the node BEFORE the current
// element, exactly like LinkedList, so an empty list is both atStart()
// and atEnd(), and previous() works in O(1).
template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;    // sentinel node: never holds a real element
	DNode<E>* tail;    // last real node (head itself when the list is empty)
	DNode<E>* current; // cursor: points to the node BEFORE the current element
	int size;          // number of real elements

public:
	DLinkedList() {
		head = new DNode<E>();
		tail = current = head;
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
	}
	// Insert at the cursor: same O(1) linking trick as a singly linked list,
	// plus fixing the prev pointer of the following node.
	void insert(E element) {
		current->next = new DNode<E>(element, current->next, current);
		if (current->next->next != nullptr)
			current->next->next->prev = current->next;
		if (current == tail)
			tail = current->next;
		size++;
	}
	// Append at the end in O(1) thanks to the tail pointer.
	void append(E element) {
		tail->next = new DNode<E>(element, nullptr, tail);
		tail = tail->next;
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	// Remove the current element (the one after the cursor) and patch both
	// neighbours so the chain stays consistent.
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		E result = current->next->element;
		DNode<E>* temp = current->next->next;
		delete current->next;
		current->next = temp;
		if (temp != nullptr)
			temp->prev = current;
		else
			tail = current;
		size--;
		return result;
	}
	void clear() {
		while (head->next != nullptr) {
			DNode<E>* temp = head->next->next;
			delete head->next;
			head->next = temp;
		}
		tail = current = head;
		size = 0;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	// Walk from the head: O(n).
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->prev;
	}
	bool atEnd() {
		return current == tail;
	}
	bool atStart() {
		return current == head;
	}
	int getPos() {
		int pos = 0;
		DNode<E>* temp = head;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[";
		DNode<E>* temp = head->next;
		while (temp != nullptr) {
			cout << temp->element;
			if (temp->next != nullptr)
				cout << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};
