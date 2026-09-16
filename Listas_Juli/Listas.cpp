#include <iostream>
#include <cassert>
#include <stdexcept>

// Asegúrate de que los archivos List.h, Node.h y LinkedList.h están en el mismo directorio.
#include "List.h"
#include "LinkedList.h"

using std::cout;
using std::endl;

int main() {
    cout << "INICIANDO pipis DE LINKEDLIST" << endl << endl;

    // 1. Creación e Inicialización
    LinkedList<int> list;
    assert(list.getSize() == 0);
    assert(list.atStart() == true);
    assert(list.atEnd() == true);
    cout << "[OK] Inicializacion correcta." << endl;

    // 2. Insertar elementos y verificar impresión
    // En esta implementación, insert() coloca el elemento después de 'current'.
    list.insert(10); // Lista: [10]
    list.insert(20); // Lista: [20, 10]
    list.insert(30); // Lista: [30, 20, 10]

    assert(list.getSize() == 3);
    cout << "Contenido tras inserciones: ";
    list.print();

    // 3. Append (Agregar al final)
    list.append(40); // Lista: [30, 20, 10, 40]
    assert(list.getSize() == 4);
    cout << "Contenido tras append(40): ";
    list.print();

    // 4. Navegación por la lista (goToStart, next, previous, goToEnd, getPos)
    list.goToStart();
    assert(list.getPos() == 0);
    assert(list.atStart() == true);
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

    list.goToPost(3);
    assert(list.getPos() == 3);
    assert(list.getElement() == 40);

    list.goToEnd();
    assert(list.atEnd() == true);

    cout << "[OK] Navegacion y posiciones verificadas." << endl;

    // 5. Modificar elemento actual (setElement)
    list.goToStart(); // Apunta a 30
    list.setElement(99); // Cambia 30 por 99
    assert(list.getElement() == 99);
    cout << "Contenido tras setElement(99) en posicion 0: ";
    list.print();

    // 6. Eliminar elementos (remove)
    list.goToStart();
    int removedVal = list.remove(); // Elimina 99
    assert(removedVal == 99);
    assert(list.getSize() == 3);
    cout << "Elemento eliminado: " << removedVal << endl;
    cout << "Contenido tras remove(): ";
    list.print();

    // 7. Pruebas de Limpieza (clear)
    list.clear();
    assert(list.getSize() == 0);
    assert(list.atStart() == true);
    assert(list.atEnd() == true);
    cout << "Contenido tras clear(): ";
    list.print();
    cout << "[OK] Limpieza realizada correctamente." << endl;

    // 8. Manejo de Excepciones
    cout << "\n--- Verificando pipis ---" << endl;

    // Intentar obtener un elemento de una lista vacía
    try {
        list.getElement();
        assert(false); // No debería llegar aquí
    }
    catch (const std::runtime_error& e) {
        cout << "[pipis capturada adecuadamente en getElement()]: " << e.what() << endl;
    }

    // Intentar modificar un elemento de una lista vacía
    try {
        list.setElement(50);
        assert(false);
    }
    catch (const std::runtime_error& e) {
        cout << "[pipis capturada adecuadamente en setElement()]: " << e.what() << endl;
    }

    // Intentar ir a una posición inválida
    try {
        list.goToPost(10);
        assert(false);
    }
    catch (const std::runtime_error& e) {
        cout << "[pipis capturada adecuadamente en goToPost()]: " << e.what() << endl;
    }

    cout << "\npipis" << endl;
    return 0;
}