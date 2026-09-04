#include <iostream>
#include <cstdlib>
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "ArrayQueue.h"
#include "LinkedQueue.h"

using std::cout;
using std::endl;

int main()
{
    cout << "\nArray Stack (int)" << endl;
    ArrayStack<int> pilaEnteros(100);
    pilaEnteros.push(10);
    pilaEnteros.push(20);
    pilaEnteros.push(30);
    pilaEnteros.print();
    cout << "pop: " << pilaEnteros.pop() << endl;
    pilaEnteros.print();

    cout << "\nLinked Stack (double)" << endl;
    Stack<double>* pilaDobles = new LinkedStack<double>();
    pilaDobles->push(100.55);
    pilaDobles->push(200.99);
    pilaDobles->push(300.12);
    cout << "Size of Linked Stack:" << pilaDobles->getSize() << endl;
    pilaDobles->print();
    cout << "pop: " << pilaDobles->pop() << endl;
    pilaDobles->print();
    delete pilaDobles;

    cout << "\nArray Queue (float)" << endl;
    Queue<float>* colaFloats = new ArrayQueue<float>();
    colaFloats->enqueue(11.1f);
    colaFloats->enqueue(22.2f);
    colaFloats->enqueue(33.3f);
    colaFloats->enqueue(44.4f);
    colaFloats->enqueue(55.5f);
    colaFloats->print();
    cout << "dequeue: " << colaFloats->dequeue() << endl;
    colaFloats->print();
    cout << "dequeue: " << colaFloats->dequeue() << endl;
    colaFloats->print();
    cout << "Queue Size: " << colaFloats->getSize() << endl;
    cout << "Is Empty? " << colaFloats->isEmpty() << endl;
    delete colaFloats;

    cout << "\nLinked Queue (long)" << endl;
    Queue<long>* colaLongs = new LinkedQueue<long>();
    colaLongs->enqueue(1000000);
    colaLongs->enqueue(2000000);
    colaLongs->enqueue(3000000);
    colaLongs->enqueue(4000000);
    colaLongs->print();
    cout << "dequeue: " << colaLongs->dequeue() << endl;
    colaLongs->print();
    cout << "dequeue: " << colaLongs->dequeue() << endl;
    colaLongs->print();
    cout << "Queue Size: " << colaLongs->getSize() << endl;
    cout << "Is Empty? " << colaLongs->isEmpty() << endl;
    delete colaLongs;

    return 0;
}