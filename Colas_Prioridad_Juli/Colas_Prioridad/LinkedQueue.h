#pragma once

#include <stdexcept>
#include <iostream>
#include "Queue.h"

using std::runtime_error;
using std::cout;
using std::endl;

// A single node in the linked list. Each node holds data and a pointer to the next node.
template <typename E>
struct QueueNode {
	E data;
	QueueNode<E>* next = nullptr;  // Points to the next node, or nullptr if this is the last one
};

// LinkedQueue: a FIFO queue implemented as a singly-linked list.
// We keep track of both 'front' (where we dequeue from) and 'rear' (where we enqueue to)
// so both operations are O(1) — no need to traverse the list each time.
template <typename E>
class LinkedQueue : public Queue<E> {
private:
	QueueNode<E>* front;  // Pointer to the first node (the one we remove next)
	QueueNode<E>* rear;   // Pointer to the last node (the one we add after)
	int size;             // Current number of elements in the queue

public:
	// Constructor: empty queue has no nodes, so both pointers start as nullptr.
	LinkedQueue() {
		front = nullptr;
		rear = nullptr;
		size = 0;
	}

	// Destructor: clean up all nodes to avoid memory leaks.
	~LinkedQueue() {
		clear();
	}

	// Add an element to the back of the queue.
	// If the queue is empty, the new node becomes both front AND rear.
	// Otherwise, we link it after the current rear and move rear forward.
	void enqueue(E element) {
		QueueNode<E>* newNode = new QueueNode<E>();
		newNode->data = element;

		if (isEmpty()) {
			front = newNode;
			rear = newNode;
		}
		else {
			rear->next = newNode;  // Link the new node after the current rear
			rear = newNode;        // Update rear to point to the new last node
		}
		size++;
	}

	// Remove and return the front element.
	// We save the front node, move front forward, then delete the old node.
	// If the queue becomes empty, we also reset rear to nullptr.
	E dequeue() {
		if (isEmpty())
			throw runtime_error("Queue underflow.");

		QueueNode<E>* temp = front;      // Save pointer to the node we're removing
		E value = temp->data;            // Save the data before deleting

		front = front->next;             // Move front to the next node
		if (front == nullptr)
			rear = nullptr;              // Queue is now empty, reset rear too

		delete temp;                     // Free the memory of the removed node
		size--;
		return value;
	}

	// Peek at the front element without removing it.
	E frontValue() {
		if (isEmpty())
			throw runtime_error("Queue is empty.");
		return front->data;
	}

	// Remove all elements by repeatedly dequeuing until empty.
	void clear() {
		while (!isEmpty())
			dequeue();
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}

	// Print the queue contents in [ a b c ] format.
	void print() {
		cout << "[ ";
		QueueNode<E>* current = front;
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;  // Walk to the next node
		}
		cout << "]";
	}
};