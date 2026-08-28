#include <iostream>
#include <cstdlib>
#include <time.h>
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "ArrayQueue.h"

using std::cout;
using std::endl;

int main()
{
    
    ArrayStack<int> pila(100);
    pila.push(10);
    pila.push(20);
    pila.push(30);
    pila.print();
    cout << "pop: " << pila.pop() << endl;
    pila.print();

    
    Stack<int>* pila2 = new ArrayStack<int>(100);
    pila2->push(100);
    pila2->push(200);
    pila2->print();
    delete pila2;

   
    Stack<int>* pila3 = new LinkedStack<int>();
    pila3->push(100);
    pila3->push(200);
    cout << "Size of pila3: " << pila3->getSize() << endl; 
    pila3->print();
    delete pila3;

    Queue<int>* cola = new ArrayQueue<int>();
    cola->enqueue(11);
    cola->enqueue(22);
    cola->enqueue(33);
    cola->enqueue(44);
    cola->enqueue(55);
    cout << "dequeue: " << cola->dequeue() << endl;
    cola->print();
    cout << "dequeue: " << cola->dequeue() << endl;
    cola->print();
    cout << "Queue Size: " << cola->getSize() << endl; 
    cout << "Is Empty? " << cola->isEmpty() << endl;   
    cola->print();

    delete cola;

    return 0;
}