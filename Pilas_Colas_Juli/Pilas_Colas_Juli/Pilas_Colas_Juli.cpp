#include <iostream>
#include <cstdlib>
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "ArrayQueue.h"
#include "LinkedQueue.h"

using std::cout;
using std::endl;

// Demo program that tests all four data structure implementations:
// ArrayStack, LinkedStack, ArrayQueue, and LinkedQueue.
// Each section demonstrates push/pop (stacks) or enqueue/dequeue (queues)
// with different data types to show the templates work with any type.
int main()
{
    // --- Array Stack (int) ---
    // ArrayStack stores elements in a contiguous array.
    // Push adds to the end, pop removes from the end (LIFO).
    cout << "\nArray Stack (int)" << endl;
    ArrayStack<int> pilaEnteros(100);  // Stack with max capacity of 100
    pilaEnteros.push(10);  // Stack: [10]
    pilaEnteros.push(20);  // Stack: [10, 20]
    pilaEnteros.push(30);  // Stack: [10, 20, 30]
    pilaEnteros.print();   // Prints: [30, 20, 10] (top first)
    cout << "pop: " << pilaEnteros.pop() << endl;  // Removes 30 (last in, first out)
    pilaEnteros.print();   // Prints: [20, 10]

    // --- Linked Stack (double) ---
    // LinkedStack uses a linked list — no fixed capacity, grows dynamically.
    // We use a Stack* pointer to demonstrate polymorphism (interface-based usage).
    cout << "\nLinked Stack (double)" << endl;
    Stack<double>* pilaDobles = new LinkedStack<double>();  // Created via base class pointer
    pilaDobles->push(100.55);  // Stack: [100.55]
    pilaDobles->push(200.99);  // Stack: [100.55, 200.99]
    pilaDobles->push(300.12);  // Stack: [100.55, 200.99, 300.12]
    cout << "Size of Linked Stack:" << pilaDobles->getSize() << endl;  // 3
    pilaDobles->print();   // Prints: [300.12, 200.99, 100.55]
    cout << "pop: " << pilaDobles->pop() << endl;  // Removes 300.12
    pilaDobles->print();   // Prints: [200.99, 100.55]
    delete pilaDobles;     // Destructor calls clear() to free all nodes

    // --- Array Queue (float) ---
    // ArrayQueue uses a circular buffer — enqueue adds at back, dequeue removes from front.
    cout << "\nArray Queue (float)" << endl;
    Queue<float>* colaFloats = new ArrayQueue<float>();
    colaFloats->enqueue(11.1f);  // Queue: [11.1]
    colaFloats->enqueue(22.2f);  // Queue: [11.1, 22.2]
    colaFloats->enqueue(33.3f);  // Queue: [11.1, 22.2, 33.3]
    colaFloats->enqueue(44.4f);  // Queue: [11.1, 22.2, 33.3, 44.4]
    colaFloats->enqueue(55.5f);  // Queue: [11.1, 22.2, 33.3, 44.4, 55.5]
    colaFloats->print();         // Prints: [11.1, 22.2, 33.3, 44.4, 55.5]
    cout << "dequeue: " << colaFloats->dequeue() << endl;  // Removes 11.1 (first in)
    colaFloats->print();         // Prints: [22.2, 33.3, 44.4, 55.5]
    cout << "dequeue: " << colaFloats->dequeue() << endl;  // Removes 22.2
    colaFloats->print();         // Prints: [33.3, 44.4, 55.5]
    cout << "Queue Size: " << colaFloats->getSize() << endl;  // 3
    cout << "Is Empty? " << colaFloats->isEmpty() << endl;    // 0 (false)
    delete colaFloats;

    // --- Linked Queue (long) ---
    // LinkedQueue uses a linked list with a sentinel node for cleaner edge cases.
    cout << "\nLinked Queue (long)" << endl;
    Queue<long>* colaLongs = new LinkedQueue<long>();
    colaLongs->enqueue(1000000);  // Queue: [1000000]
    colaLongs->enqueue(2000000);  // Queue: [1000000, 2000000]
    colaLongs->enqueue(3000000);  // Queue: [1000000, 2000000, 3000000]
    colaLongs->enqueue(4000000);  // Queue: [1000000, 2000000, 3000000, 4000000]
    colaLongs->print();           // Prints: [1000000, 2000000, 3000000, 4000000]
    cout << "dequeue: " << colaLongs->dequeue() << endl;  // Removes 1000000
    colaLongs->print();           // Prints: [2000000, 3000000, 4000000]
    cout << "dequeue: " << colaLongs->dequeue() << endl;  // Removes 2000000
    colaLongs->print();           // Prints: [3000000, 4000000]
    cout << "Queue Size: " << colaLongs->getSize() << endl;  // 2
    cout << "Is Empty? " << colaLongs->isEmpty() << endl;    // 0 (false)
    delete colaLongs;

    return 0;
}