#include <iostream>
#include <cstdlib>
#include <time.h>
#include "ArrayStack.h"
#include "LinkedStack.h"

using std::cout;
using std::endl;

int main()
{
    ArrayStack<int> pila(100);
    pila.push(10);
    pila.push(20);
    pila.push(30);
    pila.print();
    cout << pila.pop() << endl;
    pila.print();

    Stack<int>* pila2 = new ArrayStack<int>(100);
    pila2->push(100);
    pila2->push(200);
    pila2->print();
    delete pila2;

    Stack<int>* pila3 = new LinkedStack<int>();
    pila3->push(100);
    pila3->push(200);
    pila3->getSize();
    pila3->print();
    delete pila3;
    return 0;
}
