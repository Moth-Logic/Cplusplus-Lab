#include <iostream>
#include <cassert>
#include <stdexcept>

#include "List.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "DLinkedList.h"

using std::cout;
using std::endl;

// Runs the same battery of checks on any List implementation.
// The list is expected to start empty with cursor at start.
template <typename E>
void testList(List<E>& list, const char* name) {
    cout << "===== Probando " << name << " =====" << endl << endl;

    // 1. Creacion e inicializacion
    assert(list.getSize() == 0);
    assert(list.atStart());
    assert(list.atEnd());
    cout << "[OK] Inicializacion correcta." << endl;

    // 2. Insert al inicio (current queda en head -> inserta en la posicion 0)
    list.insert(10); // [10]
    list.insert(20); // [20, 10]
    list.insert(30); // [30, 20, 10]
    assert(list.getSize() == 3);
    cout << "Contenido tras inserciones: ";
    list.print();

    // 3. Append al final
    list.append(40); // [30, 20, 10, 40]
    assert(list.getSize() == 4);
    cout << "Contenido tras append(40): ";
    list.print();

    // 4. Navegacion: goToStart, goToPos, next, previous, goToEnd, getPos
    list.goToStart();
    assert(list.getPos() == 0);
    assert(list.atStart());
    assert(list.getElement() == 30);

    list.next();
    assert(list.getPos() == 1);
    assert(list.getElement() == 20);

    list.next();
    assert(list.getPos() == 2);
    assert(list.getElement() == 10);

    list.previous();
    assert(list.getPos() == 1);
    assert(list.getElement() == 20);

    list.goToPos(3);
    assert(list.getPos() == 3);
    assert(list.getElement() == 40);

    list.goToEnd();
    assert(list.atEnd());
    cout << "[OK] Navegacion y posiciones verificadas." << endl;

    // 5. Modificar el elemento actual
    list.goToStart();      // apunta a 30
    list.setElement(99);   // cambia 30 por 99 -> [99, 20, 10, 40]
    assert(list.getElement() == 99);
    cout << "Contenido tras setElement(99) en posicion 0: ";
    list.print();

    // 6. Remove en medio: posicion 1 (elimina el 20)
    list.next();           // posicion 1
    int removedVal = list.remove();
    assert(removedVal == 20);
    assert(list.getSize() == 3);
    cout << "Elemento eliminado: " << removedVal << endl;
    cout << "Contenido tras remove() en posicion 1: ";
    list.print();

    // 7. remove() del ultimo elemento (caso especial de tail)
    list.goToEnd();
    list.previous();       // posicion 2, ultimo elemento real (40)
    assert(list.getElement() == 40);
    removedVal = list.remove();
    assert(removedVal == 40);
    assert(list.getSize() == 2);
    assert(list.atEnd());
    cout << "Contenido tras remove() del ultimo elemento: ";
    list.print();

    // 8. clear
    list.clear();
    assert(list.getSize() == 0);
    assert(list.atStart());
    assert(list.atEnd());
    cout << "Contenido tras clear(): ";
    list.print();
    cout << "[OK] Limpieza realizada correctamente." << endl << endl;
}

// Verifica que las operaciones sobre una lista vacia lancen runtime_error.
void testExceptions(List<int>& list) {
    cout << "--- Verificando excepciones ---" << endl;

    try {
        list.getElement();
        assert(false && "getElement() should throw on empty list");
    }
    catch (const std::runtime_error& e) {
        cout << "[OK] getElement() lanzo excepcion: " << e.what() << endl;
    }

    try {
        list.setElement(50);
        assert(false && "setElement() should throw on empty list");
    }
    catch (const std::runtime_error& e) {
        cout << "[OK] setElement() lanzo excepcion: " << e.what() << endl;
    }

    try {
        list.remove();
        assert(false && "remove() should throw on empty list");
    }
    catch (const std::runtime_error& e) {
        cout << "[OK] remove() lanzo excepcion: " << e.what() << endl;
    }

    try {
        list.goToPos(10);
        assert(false && "goToPos() should throw on invalid position");
    }
    catch (const std::runtime_error& e) {
        cout << "[OK] goToPos() lanzo excepcion: " << e.what() << endl;
    }

    cout << endl;
}

int main() {
    cout << "INICIANDO PRUEBAS DE LISTAS" << endl << endl;

    ArrayList<int> arrayList;
    testList(arrayList, "ArrayList");
    testExceptions(arrayList);

    LinkedList<int> linkedList;
    testList(linkedList, "LinkedList");
    testExceptions(linkedList);

    DLinkedList<int> dLinkedList;
    testList(dLinkedList, "DLinkedList");
    testExceptions(dLinkedList);

    cout << "TODAS LAS PRUEBAS PASARON EXITOSAMENTE" << endl;
    return 0;
}
