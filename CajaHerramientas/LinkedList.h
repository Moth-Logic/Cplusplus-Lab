#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

// LinkedList: la lista posicional con nodos simples (con centinela).
//
// La idea clave: 'fence' apunta SIEMPRE al nodo justo ANTES de la
// posicion actual. Asi, el elemento "actual" es siempre fence->next.
//   - Si fence == head           -> estamos en la posicion 0 (atStart)
//   - Si fence->next == nullptr  -> estamos despues del ultimo (atEnd)
// Esto hace insert/remove/getElement O(1) sobre la posicion actual.
// Lo unico caro es previous(), porque una lista simple no tiene forma
// de ir "hacia atras" sin recorrer desde el inicio otra vez — por eso
// existe DLinkedList, que soluciona justo este problema.
template <typename E>
class LinkedList : public List<E> {
private:
	Node<E>* head;   // centinela
	Node<E>* tail;   // ultimo nodo real (o head si esta vacia)
	Node<E>* fence;  // nodo antes de la posicion actual
	int size;
	int pos;         // posicion actual, en paralelo con 'fence'

public:
	LinkedList() {
		head = new Node<E>();
		tail = head;
		fence = head;
		size = 0;
		pos = 0;
	}

	~LinkedList() {
		clear();
		delete head;
	}

	void insert(E element) {
		fence->next = new Node<E>(element, fence->next);
		if (fence == tail)
			tail = fence->next;
		size++;
	}

	void append(E element) {
		tail = tail->next = new Node<E>(element);
		size++;
	}

	void setElement(E element) {
		if (fence->next == nullptr)
			throw runtime_error("Posicion invalida.");
		fence->next->element = element;
	}

	E getElement() {
		if (fence->next == nullptr)
			throw runtime_error("Posicion invalida.");
		return fence->next->element;
	}

	E remove() {
		if (fence->next == nullptr)
			throw runtime_error("Posicion invalida.");
		Node<E>* temp = fence->next;
		E removed = temp->element;
		fence->next = temp->next;
		if (temp == tail)
			tail = fence;
		delete temp;
		size--;
		return removed;
	}

	void clear() {
		while (head->next != nullptr) {
			Node<E>* temp = head->next;
			head->next = temp->next;
			delete temp;
		}
		tail = head;
		fence = head;
		size = 0;
		pos = 0;
	}

	void goToStart() {
		fence = head;
		pos = 0;
	}

	void goToEnd() {
		fence = tail;
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
		if (fence->next != nullptr) {
			fence = fence->next;
			pos++;
		}
	}

	void previous() {
		// no hay puntero "prev" en un nodo simple, asi que hay que
		// recorrer desde el inicio para encontrar al que esta justo
		// antes de fence. Caro (O(n)), pero es la limitacion real
		// de una lista enlazada simple.
		if (fence != head) {
			Node<E>* temp = head;
			while (temp->next != fence)
				temp = temp->next;
			fence = temp;
			pos--;
		}
	}

	bool atStart() {
		return fence == head;
	}

	bool atEnd() {
		return fence->next == nullptr;
	}

	int getPos() {
		return pos;
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		Node<E>* current = head->next;
		while (current != nullptr) {
			cout << current->element;
			if (current->next != nullptr)
				cout << ", ";
			current = current->next;
		}
		cout << "]" << endl;
	}
};
