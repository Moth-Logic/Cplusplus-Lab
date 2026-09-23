#pragma once

#define DEFAULT_MAX 1024

#include <stdexcept>
#include <iostream>
#include "List.h"

using std::runtime_error;
using std::cout;
using std::endl;

// ArrayList: la lista posicional implementada con un arreglo.
// 'pos' es la posicion actual, y puede valer desde 0 hasta size (size
// significa "una posicion despues del ultimo elemento" = atEnd()).
template <typename E>
class ArrayList : public List<E> {
private:
	E* elements;
	int max;
	int size;
	int pos;

public:
	ArrayList(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Tamano invalido.");
		elements = new E[max];
		this->max = max;
		size = 0;
		pos = 0;
	}

	~ArrayList() {
		delete[] elements;
	}

	void insert(E element) {
		if (size == max)
			throw runtime_error("La lista esta llena.");
		// corre todo un espacio a la derecha, desde el final hasta pos
		for (int i = size; i > pos; i--)
			elements[i] = elements[i - 1];
		elements[pos] = element;
		size++;
	}

	void append(E element) {
		if (size == max)
			throw runtime_error("La lista esta llena.");
		elements[size] = element;
		size++;
	}

	void setElement(E element) {
		if (pos < 0 || pos >= size)
			throw runtime_error("Posicion invalida.");
		elements[pos] = element;
	}

	E getElement() {
		if (pos < 0 || pos >= size)
			throw runtime_error("Posicion invalida.");
		return elements[pos];
	}

	E remove() {
		if (pos < 0 || pos >= size)
			throw runtime_error("Posicion invalida.");
		E removed = elements[pos];
		// corre todo un espacio a la izquierda, tapando el hueco
		for (int i = pos; i < size - 1; i++)
			elements[i] = elements[i + 1];
		size--;
		return removed;
	}

	void clear() {
		size = 0;
		pos = 0;
	}

	void goToStart() {
		pos = 0;
	}

	void goToEnd() {
		pos = size;
	}

	void goToPos(int newPos) {
		if (newPos < 0 || newPos > size)
			throw runtime_error("Posicion invalida.");
		pos = newPos;
	}

	void next() {
		if (pos < size)
			pos++;
	}

	void previous() {
		if (pos > 0)
			pos--;
	}

	bool atStart() {
		return pos == 0;
	}

	bool atEnd() {
		return pos == size;
	}

	int getPos() {
		return pos;
	}

	int getSize() {
		return size;
	}

	void print() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i != size - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
};
