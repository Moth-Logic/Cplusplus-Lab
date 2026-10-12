// Estructuras de Datos.cpp : Interactive test program.
// Provides a hierarchical menu to test every data structure in this project.

#include <iostream>
#include <string>
#include <cstdlib>

#include "ArrayList.h"
#include "LinkedList.h"
#include "DLinkedList.h"
#include "CircleList.h"
#include "DCircleList.h"
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "ArrayQueue.h"
#include "LinkedQueue.h"
#include "LinkedPriorityQueue.h"
#include "HeapPriorityQueue.h"
#include "MinHeap.h"
#include "Matrix.h"

using namespace std;

//==============================================================================
// Input helpers
//==============================================================================

// Read an integer from the user. Keeps asking until valid input is given.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value)
            return value;
        cout << "  Entrada invalida. Digite un numero entero.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Read a line of text (used for strings and words).
string readLine(const string& prompt) {
    cin.ignore(10000, '\n');
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

// Generic element reader: everything is tested with int elements by default.
int readElement(const string& prompt = "  Valor (int): ") {
    return readInt(prompt);
}

//==============================================================================
// Shared menu helpers
//==============================================================================

void pauseScreen() {
    cout << "\n  Presione ENTER para volver al menu...";
    cin.ignore(10000, '\n');
    cin.get();
}

void printHeader(const string& title) {
    system("cls");
    cout << "=============================================\n";
    cout << "  " << title << "\n";
    cout << "=============================================\n\n";
}

// Print the current state of any structure that has print() reading well.
// Each test block calls it with its own lambda so it stays type agnostic.
template <typename T, typename F>
void showState(T& ds, F printer) {
    cout << "  Estado actual: ";
    printer(ds);
    cout << "  Size: " << ds.getSize() << "\n\n";
}

//==============================================================================
// 1. LISTS - cursor-based (List interface: ArrayList, LinkedList, DLinkedList)
//==============================================================================

// Generic tester for the three list implementations. The two constructors
// differ, so creation is delegated to a "make" function passed per type.
template <typename ListT, typename MakeFn>
void testCursorList(const string& name, MakeFn make) {
    printHeader("Listas - " + name);

    ListT* list = make();
    int option = 0;

    // Sub-menu with the full List interface, driven by an int state flag so
    // we can demo "empty list" errors safely.
    do {
        showState(*list, [](ListT& l) { l.print(); });
        cout << "  1) insert    (inserta en la posicion del cursor)\n";
        cout << "  2) append    (agrega al final)\n";
        cout << "  3) remove    (elimina el elemento actual)\n";
        cout << "  4) setElement(cambia el elemento actual)\n";
        cout << "  5) getElement(muestra el elemento actual)\n";
        cout << "  6) goToStart\n";
        cout << "  7) goToEnd\n";
        cout << "  8) goToPos\n";
        cout << "  9) next      (si no hay mas, no hace nada)\n";
        cout << " 10) previous  (si esta al inicio, no hace nada)\n";
        cout << " 11) atStart / atEnd / getPos\n";
        cout << " 12) clear\n";
        cout << " 13) Regresar al menu de Listas\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1:
                showState(*list, [](ListT& l) { l.print(); });
                list->insert(readElement());
                break;
            case 2:
                list->append(readElement());
                break;
            case 3: {
                int pos = list->getPos();
                int val = list->remove();
                cout << "  Eliminado " << val << " desde la posicion " << pos << "\n";
                break;
            }
            case 4:
                list->setElement(readElement("  Nuevo valor (int): "));
                cout << "  Elemento actual cambiado.\n";
                break;
            case 5:
                cout << "  Elemento actual: " << list->getElement() << "\n";
                break;
            case 6:
                list->goToStart();
                cout << "  Cursor al inicio.\n";
                break;
            case 7:
                list->goToEnd();
                cout << "  Cursor al final.\n";
                break;
            case 8:
                list->goToPos(readInt("  Posicion: "));
                cout << "  Cursor a la posicion indicada.\n";
                break;
            case 9:
                list->next();
                cout << "  next() ejecutado.\n";
                break;
            case 10:
                list->previous();
                cout << "  previous() ejecutado.\n";
                break;
            case 11:
                cout << "  atStart: " << (list->atStart() ? "si" : "no")
                    << " | atEnd: " << (list->atEnd() ? "si" : "no")
                    << " | getPos: " << list->getPos() << "\n";
                break;
            case 12:
                list->clear();
                cout << "  Lista vaciada.\n";
                break;
            case 13:
                break;
            default:
                cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 13) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("Listas - " + name);
        }
    } while (option != 13);

    delete list;
}

void listsMenu() {
    printHeader("LISTAS");
    cout << "  Las tres implementan la interfaz List<E> con cursor.\n";
    cout << "  El elemento actual es el que esta DESPUES del cursor." << endl;
    cout << "\n  Elemento de prueba: int. Presione ENTER...";
    cin.get();

    int option = 0;
    do {
        printHeader("LISTAS");
        cout << "  1) ArrayList.h            (arreglo dinamico)\n";
        cout << "  2) LinkedList.h           (lista sencillamente enlazada)\n";
        cout << "  3) DLinkedList.h          (lista doblemente enlazada)\n";
        cout << "  4) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        switch (option) {
        case 1:
            testCursorList<ArrayList<int>>("ArrayList", []() {
                return new ArrayList<int>(); });
            break;
        case 2:
            testCursorList<LinkedList<int>>("LinkedList", []() {
                return new LinkedList<int>(); });
            break;
        case 3:
            testCursorList<DLinkedList<int>>("DLinkedList", []() {
                return new DLinkedList<int>(); });
            break;
        case 4:
            break;
        default:
            cout << "  Opcion invalida.\n";
        }
    } while (option != 4);
}

//==============================================================================
// 2. CIRCULAR LISTS (Clist interface: CircleList, DCircleList)
//==============================================================================

template <typename ListT>
void testCircleList(const string& name) {
    printHeader("Listas Circulares - " + name);

    ListT* list = new ListT();
    int option = 0;

    do {
        showState(*list, [](ListT& l) { l.print(); });
        cout << "  ( \"frente\" = el elemento despues del current ; \"atras\" = current )\n\n";
        cout << "  1) insert    (inserta al frente del nodo current)\n";
        cout << "  2) insertBack(inserta atras, la current avanza a él)\n";
        cout << "  3) remove    (elimina el frente)\n";
        cout << "  4) removeBack(elimina el atras)\n";
        cout << "  5) getFront\n";
        cout << "  6) getBack\n";
        cout << "  7) next      (current avanza)\n";
        cout << "  8) previous  (current retrocede)\n";
        cout << "  9) clear\n";
        cout << " 10) Regresar al menu de Listas\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: list->insert(readElement()); break;
            case 2: list->insertBack(readElement()); break;
            case 3: cout << "  remove -> " << list->remove() << "\n"; break;
            case 4: cout << "  removeBack -> " << list->removeBack() << "\n"; break;
            case 5: cout << "  getFront -> " << list->getFront() << "\n"; break;
            case 6: cout << "  getBack -> " << list->getBack() << "\n"; break;
            case 7:
                list->next();
                cout << "  current avanzado. Estado:\n  ";
                list->print();
                break;
            case 8:
                list->previous();
                cout << "  current retrocedido. Estado:\n  ";
                list->print();
                break;
            case 9:
                list->clear();
                cout << "  Lista circle vacia.\n";
                break;
            case 10: break;
            default: cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 10) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("Listas Circulares - " + name);
        }
    } while (option != 10);

    delete list;
}

void circularListsMenu() {
    int option = 0;
    do {
        printHeader("LISTAS CIRCULARES");
        cout << "  Ambas implementan la interfaz Clist<E>.\n\n";
        cout << "  1) CircleList.h  (lista circular sencilla)\n";
        cout << "  2) DCircleList.h (lista circular doble)\n";
        cout << "  3) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        switch (option) {
        case 1: testCircleList<CircleList<int>>("CircleList"); break;
        case 2: testCircleList<DCircleList<int>>("DCircleList"); break;
        case 3: break;
        default: cout << "  Opcion invalida.\n";
        }
    } while (option != 3);
}

//==============================================================================
// 3. STACKS - LIFO (ArrayStack, LinkedStack)
//==============================================================================

template <typename StackT>
void testStack(const string& name) {
    printHeader("Pilas - " + name);

    StackT* stack = new StackT();
    int option = 0;

    do {
        showState(*stack, [](StackT& s) { s.print(); });
        cout << "  1) push\n";
        cout << "  2) pop    (saca y devuelve el tope)\n";
        cout << "  3) topValue (mira el tope sin sacarlo)\n";
        cout << "  4) isEmpty\n";
        cout << "  5) clear\n";
        cout << "  6) Regresar al menu de Pilas\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: stack->push(readElement()); cout << "  push listo.\n"; break;
            case 2: cout << "  pop -> " << stack->pop() << "\n"; break;
            case 3: cout << "  topValue -> " << stack->topValue() << "\n"; break;
            case 4: cout << "  isEmpty -> " << (stack->isEmpty() ? "si" : "no") << "\n"; break;
            case 5:
                stack->clear();
                cout << "  Pila vaciada.\n";
                break;
            case 6: break;
            default: cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 6) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("Pilas - " + name);
        }
    } while (option != 6);

    delete stack;
}

void stacksMenu() {
    int option = 0;
    do {
        printHeader("PILAS");
        cout << "  Ambas implementan la interfaz Stack<E>.\n\n";
        cout << "  1) ArrayStack.h  (arreglo fijo, DEFAULT_MAX=1024)\n";
        cout << "  2) LinkedStack.h (nodes enlazados, sin limite practico)\n";
        cout << "  3) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        switch (option) {
        case 1: testStack<ArrayStack<int>>("ArrayStack"); break;
        case 2: testStack<LinkedStack<int>>("LinkedStack"); break;
        case 3: break;
        default: cout << "  Opcion invalida.\n";
        }
    } while (option != 3);
}

//==============================================================================
// 4. QUEUES - FIFO (ArrayQueue, LinkedQueue)
//==============================================================================

template <typename QueueT>
void testQueue(const string& name) {
    printHeader("Colas - " + name);

    QueueT* queue = new QueueT();
    int option = 0;

    do {
        showState(*queue, [](QueueT& q) { q.print(); });
        cout << "  1) enqueue   (agrega al final)\n";
        cout << "  2) dequeue   (saca y devuelve el frente)\n";
        cout << "  3) frontValue(mira el frente sin sacarlo)\n";
        cout << "  4) isEmpty\n";
        cout << "  5) clear\n";
        cout << "  6) Regresar al menu de Colas\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: queue->enqueue(readElement()); cout << "  enqueue listo.\n"; break;
            case 2: cout << "  dequeue -> " << queue->dequeue() << "\n"; break;
            case 3: cout << "  frontValue -> " << queue->frontValue() << "\n"; break;
            case 4: cout << "  isEmpty -> " << (queue->isEmpty() ? "si" : "no") << "\n"; break;
            case 5:
                queue->clear();
                cout << "  Cola vaciada.\n";
                break;
            case 6: break;
            default: cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 6) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("Colas - " + name);
        }
    } while (option != 6);

    delete queue;
}

void queuesMenu() {
    int option = 0;
    do {
        printHeader("COLAS");
        cout << "  Ambas implementan la interfaz Queue<E>.\n\n";
        cout << "  1) ArrayQueue.h  (arreglo circular / ring buffer)\n";
        cout << "  2) LinkedQueue.h (lista enlazada con nodo centinela)\n";
        cout << "  3) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        switch (option) {
        case 1: testQueue<ArrayQueue<int>>("ArrayQueue"); break;
        case 2: testQueue<LinkedQueue<int>>("LinkedQueue"); break;
        case 3: break;
        default: cout << "  Opcion invalida.\n";
        }
    } while (option != 3);
}

//==============================================================================
// 5. PRIORITY QUEUES (LinkedPriorityQueue, HeapPriorityQueue)
//==============================================================================

template <typename PQ>
void testPriorityQueue(const string& name) {
    printHeader("Colas de Prioridad - " + name);

    PQ* pq;
    if (name == "LinkedPriorityQueue") {
        // The linked one lets us decide how many priority LEVELS to use.
        int levels = readInt("  Cuantas prioridades (niveles 0..N-1)? [default 5]: ");
        if (levels < 1) levels = 5;
        pq = new PQ(levels);
    }
    else {
        pq = new PQ();
    }

    int option = 0;
    do {
        cout << "  Contenido:\n";
        try { pq->print(); }
        catch (exception& e) { cout << "  (vacia o error: " << e.what() << ")\n"; }
        cout << "  isEmpty: " << (pq->isEmpty() ? "si" : "no")
            << " | size: " << pq->getSize() << "\n\n";

        cout << "  1) insert (elemento, prioridad)\n";
        cout << "  2) min    (consulta el minimo sin sacarlo)\n";
        cout << "  3) removeMin (saca el minimo)\n";
        cout << "  4) clear\n";
        cout << "  5) Regresar\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: {
                int val = readInt("  Valor (int): ");
                int pri = readInt("  Prioridad (int menor = mas urgente): ");
                pq->insert(val, pri);
                cout << "  insert listo.\n";
                break;
            }
            case 2: cout << "  min -> " << pq->min() << "\n"; break;
            case 3: cout << "  removeMin -> " << pq->removeMin() << "\n"; break;
            case 4:
                pq->clear();
                cout << "  Cola de prioridad vaciada.\n";
                break;
            case 5: break;
            default: cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 5) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("Colas de Prioridad - " + name);
        }
    } while (option != 5);

    delete pq;
}

void priorityQueuesMenu() {
    int option = 0;
    do {
        printHeader("COLAS DE PRIORIDAD");
        cout << "  Ambas implementan la interfaz PriorityQueue<E>.\n";
        cout << "  La de heap usa MinHeap + Pair<key,value>, la enlazada usa N colas.\n\n";
        cout << "  1) LinkedPriorityQueue.h (N colas por nivel de prioridad)\n";
        cout << "  2) HeapPriorityQueue.h   (heap binario + Pair)\n";
        cout << "  3) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        switch (option) {
        case 1: testPriorityQueue<LinkedPriorityQueue<int>>("LinkedPriorityQueue"); break;
        case 2: testPriorityQueue<HeapPriorityQueue<int>>("HeapPriorityQueue"); break;
        case 3: break;
        default: cout << "  Opcion invalida.\n";
        }
    } while (option != 3);
}

//==============================================================================
// 6. MINHEAP (standalone)
//==============================================================================

void testMinHeap() {
    printHeader("MinHeap");

    MinHeap<int>* heap = new MinHeap<int>();
    int option = 0;

    do {
        showState(*heap, [](MinHeap<int>& h) { h.print(); });
        cout << "  1) insert\n";
        cout << "  2) first       (el minimo, sin sacarlo)\n";
        cout << "  3) removeFirst (saca el minimo)\n";
        cout << "  4) remove(pos  pos arbitraria del arreglo interno)\n";
        cout << "  5) isEmpty\n";
        cout << "  6) clear\n";
        cout << "  7) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: heap->insert(readElement()); cout << "  insert listo.\n"; break;
            case 2: cout << "  first -> " << heap->first() << "\n"; break;
            case 3: cout << "  removeFirst -> " << heap->removeFirst() << "\n"; break;
            case 4: {
                int pos = readInt("  Posicion en el arreglo interno: ");
                cout << "  remove -> " << heap->remove(pos) << "\n";
                break;
            }
            case 5: cout << "  isEmpty -> " << (heap->isEmpty() ? "si" : "no") << "\n"; break;
            case 6:
                heap->clear();
                cout << "  Heap vaciado.\n";
                break;
            case 7: break;
            default: cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 7) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("MinHeap");
        }
    } while (option != 7);

    delete heap;
}

//==============================================================================
// 7. MATRIX
//==============================================================================

void testMatrix() {
    printHeader("Matrix");

    int r = readInt("  Filas: ");
    int c = readInt("  Columnas: ");
    Matrix<int>* m = nullptr;
    try {
        m = new Matrix<int>(r, c);
    }
    catch (exception& e) {
        cout << "  ERROR al crear: " << e.what() << "\n";
        cout << "\n  Presione ENTER para regresar...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    int option = 0;
    // Matrix has no print(); we build one locally with getValue.
    auto printMatrix = [&m]() {
        for (int i = 0; i < m->getRows(); i++) {
            cout << "    ";
            for (int j = 0; j < m->getColumns(); j++) {
                cout << m->getValue(i, j);
                if (j + 1 < m->getColumns())
                    cout << "\t";
            }
            cout << "\n";
        }
    };
    do {
        cout << "  Dimension: " << m->getRows() << " x " << m->getColumns() << "\n";
        printMatrix();
        cout << "\n  1) setValue (fila, columna, valor)\n";
        cout << "  2) getValue (fila, columna)\n";
        cout << "  3) Regresar al menu principal\n";
        option = readInt("  Opcion: ");

        try {
            switch (option) {
            case 1: {
                int row = readInt("  Fila: ");
                int col = readInt("  Columna: ");
                int val = readInt("  Valor: ");
                m->setValue(row, col, val);
                cout << "  Valor asignado.\n";
                break;
            }
            case 2: {
                int row = readInt("  Fila: ");
                int col = readInt("  Columna: ");
                cout << "  getValue -> " << m->getValue(row, col) << "\n";
                break;
            }
            case 3: break;
            default: cout << "  Opcion invalida.\n";
            }
        }
        catch (exception& e) {
            cout << "  ERROR: " << e.what() << "\n";
        }

        if (option != 3) {
            cout << "\n  Presione ENTER para continuar...";
            cin.ignore(10000, '\n');
            cin.get();
            printHeader("Matrix");
        }
    } while (option != 3);

    delete m;
}

//==============================================================================
// MAIN MENU
//==============================================================================

int main() {
    int option = 0;
    do {
        printHeader("MENU PRINCIPAL - Tester de Estructuras de Datos");
        cout << "  1) Listas                 (ArrayList, LinkedList, DLinkedList)\n";
        cout << "  2) Listas Circulares      (CircleList, DCircleList)\n";
        cout << "  3) Pilas                  (ArrayStack, LinkedStack)\n";
        cout << "  4) Colas                  (ArrayQueue, LinkedQueue)\n";
        cout << "  5) Colas de Prioridad     (LinkedPriorityQueue, HeapPriorityQueue)\n";
        cout << "  6) MinHeap\n";
        cout << "  7) Matrix                 (bidimensional dinamica)\n";
        cout << "  0) Salir\n";
        option = readInt("  Opcion: ");

        switch (option) {
        case 1: listsMenu(); break;
        case 2: circularListsMenu(); break;
        case 3: stacksMenu(); break;
        case 4: queuesMenu(); break;
        case 5: priorityQueuesMenu(); break;
        case 6: testMinHeap(); break;
        case 7: testMatrix(); break;
        case 0:
            cout << "\nHasta luego!\n";
            break;
        default:
            cout << "  Opcion invalida.\n";
        }
    } while (option != 0);

    return 0;
}
