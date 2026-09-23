#pragma once

// Node: a building block for linked data structures (stacks, queues, lists).
// Each node holds one data element and a pointer to the next node in the chain.
// The last node's 'next' pointer is nullptr, marking the end of the list.
template <typename E>
class Node {
public:
	E element;       // The data stored in this node
	Node<E>* next;   // Pointer to the next node (nullptr if this is the last one)

	// Constructor with data: creates a node holding 'element' and pointing to 'next'.
	Node(E element, Node<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}

	// Constructor without data: creates an empty node (used for sentinel/dummy nodes).
	Node(Node<E>* next = nullptr) {
		this->next = next;
	}

};