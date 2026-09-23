#pragma once
#include <stdexcept>
#include <iostream>
#include "Queue.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

// ArrayQueue: a queue implemented using a circular array (ring buffer).
// Instead of shifting all elements when we dequeue (which would be O(n)),
// we use modular arithmetic to wrap the front and back indices around.
// Example: with max=5, if front=3 and back=1, the queue spans indices 3,4,0.
// This gives O(1) enqueue AND dequeue, which is the whole point of a circular buffer.
template <typename E>
class ArrayQueue : public Queue<E> {
private:
    E* elements;  // The circular array holding queue data
    int front;    // Index of the front element (the one we dequeue next)
    int max;      // Maximum capacity of the array
    int size;     // Current number of elements in the queue
    int back;     // Index where the next element will be enqueued

public:
    // Constructor: allocate the array and start with front=back=size=0.
    ArrayQueue(int max = DEFAULT_MAX) {
        if (max < 1)
            throw runtime_error("Invalid max size.");
        elements = new E[max];
        this->max = max;
        front = back = size = 0;  // Empty queue: front and back point to the same spot
    }

    // Destructor: free the array.
    ~ArrayQueue() {
        delete[] elements;
    }

    // Enqueue: add an element at the back and advance back using modulo.
    // The modulo (%) wraps back to 0 when it reaches the end of the array.
    void enqueue(E element) {
        if (size == max)
            throw runtime_error("Queue is full.");
        elements[back] = element;       // Place element at the current back position
        back = (back + 1) % max;        // Advance back, wrapping around if needed
        size++;
    }

    // Dequeue: remove and return the front element, then advance front.
    E dequeue() {
        if (size == 0)
            throw runtime_error("Queue is empty.");
        E result = elements[front];     // Save the front element
        front = (front + 1) % max;      // Advance front, wrapping around if needed
        size--;
        return result;
    }

    // Peek at the front element without removing it.
    E frontValue() {
        if (size == 0)
            throw runtime_error("Queue is empty");
        return elements[front];
    }

    // Clear: reset all indices to 0. The data stays but is logically empty.
    void clear() {
        front = back = size = 0;
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    // Print elements from front to back, using modulo to wrap around the array.
    void print() {
        if (size == 0)
            throw runtime_error("Queue is empty");

        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << elements[(front + i) % max];  // Wrap around with modulo
            if (i < size - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
};