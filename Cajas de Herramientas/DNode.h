#pragma once

// Nodo para lista doblemente enlazada: guarda un valor y punteros
// al siguiente Y al anterior. Eso es lo que permite hacer previous()
// en O(1), a diferencia de la lista simple.
template <typename E>
class DNode {
public:
	E element;
	DNode<E>* next;
	DNode<E>* prev;

	DNode(E element, DNode<E>* next = nullptr, DNode<E>* prev = nullptr) {
		this->element = element;
		this->next = next;
		this->prev = prev;
	}
	DNode(DNode<E>* next = nullptr, DNode<E>* prev = nullptr) {
		this->next = next;
		this->prev = prev;
	}
};