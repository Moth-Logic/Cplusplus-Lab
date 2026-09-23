#pragma once

// Nodo para lista enlazada simple: guarda un valor y un puntero al siguiente.
template <typename E>
class Node {
public:
	E element;
	Node<E>* next;

	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}
};
