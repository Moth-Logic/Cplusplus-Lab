#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

// DLinkedList: igual idea que LinkedList (fence = nodo antes de la
// posicion actual), pero con DOS centinelas: uno al inicio (head) y
// uno al final (tail). Los nodos reales viven siempre entre ambos.
// Gracias a los punteros 'prev', previous() ahora es O(1) — esa es
// la ventaja real de la lista doble sobre la simple.
template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;   // centinela inicial
	DNode<E>* tail;   // centinela final
	DNode<E>* fence;  // nodo antes de la posicion actual
	int size;
	int pos;

public:
	DLinkedList() {
		head = new DNode<E>();
		tail = new DNode<E>();
		head->next = tail;
		tail->prev = head;
		fence = head;
		size = 0;
		pos = 0;
	}

	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}

	void insert(E element) {
		DNode<E>* newNode = new DNode<E>(element, fence->next, fence);
		fence->next->prev = newNode;
		fence->next = newNode;
		size++;
	}

	void append(E element) {
		DNode<E>* last = tail->prev;
		DNode<E>* newNode = new DNode<E>(element, tail, last);
		last->next = newNode;
		tail->prev = newNode;
		size++;
	}

	void setElement(E element) {
		if (fence->next == tail)
			throw runtime_error("Posicion invalida.");
		fence->next->element = element;
	}

	E getElement() {
		if (fence->next == tail)
			throw runtime_error("Posicion invalida.");
		return fence->next->element;
	}

	E remove() {
		if (fence->next == tail)
			throw runtime_error("Posicion invalida.");
		DNode<E>* temp = fence->next;
		E removed = temp->element;
		fence->next = temp->next;
		temp->next->prev = fence;
		delete temp;
		size--;
		return removed;
	}

	void clear() {
		DNode<E>* current = head->next;
		while (current != tail) {
			DNode<E>* temp = current;
			current = current->next;
			delete temp;
		}
		head->next = tail;
		tail->prev = head;
		fence = head;
		size = 0;
		pos = 0;
	}

	void goToStart() {
		fence = head;
		pos = 0;
	}

	void goToEnd() {
		fence = tail->prev;
		pos = size;
	}

	void goToPos(int newPos) {
		if (newPos < 0 || newPos > size)
			throw runtime_error("Posicion invalida.");
		fence = head;
		for (int i = 0; i < newPos; i++)
			fence = fence->next;
		pos = newPos;
	}

	void next() {
		if (fence->next != tail) {
			fence = fence->next;
			pos++;
		}
	}

	void previous() {
		if (fence != head) {
			fence = fence->prev;
			pos--;
		}
	}

	bool atStart() {
		return fence == head;
	}

	bool atEnd() {
		return fence->next == tail;
	}

	int getPos() {
		return pos;
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		DNode<E>* current = head->next;
		while (current != tail) {
			cout << current->element;
			if (current->next != tail)
				cout << ", ";
			current = current->next;
		}
		cout << "]" << endl;
	}
};
