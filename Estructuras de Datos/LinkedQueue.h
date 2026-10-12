#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

// LinkedQueue: a FIFO queue implemented with a sentinel (dummy) node.
// The sentinel node sits before the first real element and simplifies edge cases.
// front->next is always the first real element, and back points to the last one.
// This avoids special-casing an empty list — there's always at least the sentinel.
template<typename E>
class LinkedQueue : public Queue<E> {
private:
	Node<E>* front;  // Points to the sentinel node (front->next is the first real element)
	Node<E>* back;   // Points to the last real element in the queue
	int size;        // Current number of real elements (not counting the sentinel)

public:
	// Constructor: create the sentinel node. Both front and back point to it.
	LinkedQueue() {
		front = back = new Node<E>();  // Sentinel node with no data
		size = 0;
	}

	// Destructor: clear all real nodes, then delete the sentinel.
	~LinkedQueue() {
		clear();
		delete front;  // Don't forget to free the sentinel!
	}

	// Enqueue: add a new node after 'back' and move back forward.
	// The chained assignment 'back = back->next = new Node<E>(element)'
	// creates the node, links it, and updates back — all in one line.
	void enqueue(E element) {
		back = back->next = new Node<E>(element);  // Create node, link it, move back
		size++;
	}

	// Dequeue: remove the first real element (front->next).
	// We bypass the node by updating front->next to skip over it.
	E dequeue() {
		if (size == 0)
			throw runtime_error("Queue is empty");

		E result = front->next->element;          // Save the data from the first real node
		Node<E>* temp = front->next->next;        // Save pointer to the second real node
		delete front->next;                       // Free the first real node
		front->next = temp;                       // Link sentinel directly to the second node

		// If the queue is now empty, back should point back to the sentinel.
		if (size == 1) {
			back = front;
		}

		size--;
		return result;
	}

	// Peek at the front element without removing it.
	E frontValue() {
		if (size == 0)
			throw runtime_error("Queue is empty");

		return front->next->element;  // The first real element is always after the sentinel
	}

	// Clear: remove all real nodes, keeping only the sentinel.
	void clear() {
		while (front->next != nullptr) {
			Node<E>* temp = front->next;          // Save the node to delete
			front->next = temp->next;             // Skip over it
			delete temp;                          // Free it
		}
		back = front;  // Reset back to point to the sentinel (queue is now empty)
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	// Print all elements by walking from front->next to the end.
	void print() {
		if (size == 0) {
			cout << "La cola esta vacia." << endl;
		}
		else {
			Node<E>* current = front->next;  // Start at the first real element
			cout << "Contenido de la cola: ";
			while (current != nullptr) {
				cout << current->element << " ";
				current = current->next;  // Walk to the next node
			}
			cout << endl;
		}
	}
};