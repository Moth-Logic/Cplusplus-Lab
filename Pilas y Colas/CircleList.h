#pragma once

#include <stdexcept>
#include <iostream>
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class CircleList {
private:
    Node<E>* current;
    int size;

public:
    void operator = (const CircleList<E>&) = delete;
    CircleList(const CircleList<E>&) = delete;

    CircleList() {
        current = nullptr;
        size = 0;
    }

    // Inserta al frente (el nuevo nodo queda antes de current)
    void insert(E element) {
        if (size == 0) {
            current = new Node<E>(element);
            current->next = current;
        }
        else {
            // El nuevo nodo se enlaza al siguiente de current,
            // pero NO movemos current, así el nuevo queda "al frente".
            current->next = new Node<E>(element, current->next);
        }
        size++;
    }

    // Inserta al final (el nuevo nodo queda después de current, y current pasa a ser el nuevo)
    void insertBack(E element) {
        insert(element);
        current = current->next;
    }

    // Elimina el elemento del frente
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty.");

        E result;
        if (size == 1) {
            result = current->element;
            delete current;
            current = nullptr;
        }
        else {
            Node<E>* temp = current->next;   // nodo a eliminar
            result = temp->element;
            current->next = temp->next;
            delete temp;
        }
        size--;
        return result;
    }

    // Elimina el elemento del final
    E removeBack() {
        if (size == 0)
            throw runtime_error("List is empty.");

        E result;
        if (size == 1) {
            result = current->element;
            delete current;
            current = nullptr;
        }
        else {
            // Nos paramos en el nodo ANTERIOR al último (el que apunta al último).
            // El "último" es current, entonces el anterior es el que está
            // size-1 posiciones antes de current.
            Node<E>* prev = current;
            for (int i = 0; i < size - 2; i++)
                prev = prev->next;

            Node<E>* toDelete = current;     // current es el último
            result = toDelete->element;
            prev->next = current->next;
            current = prev;                  // el nuevo "back" es el anterior
            delete toDelete;
        }
        size--;
        return result;
    }

    // Vacía la lista
    void clear() {
        if (current == nullptr) return;

        Node<E>* temp = current->next;
        while (temp != current) {
            Node<E>* next = temp->next;
            delete temp;
            temp = next;
        }
        delete current;
        current = nullptr;
        size = 0;
    }

    // Retorna el elemento del frente
    E getFront() {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->next->element;
    }

    // Retorna el elemento del final
    E getBack() {
        if (size == 0)
            throw runtime_error("List is empty.");
        return current->element;
    }

    // Mueve la posición actual a la siguiente
    void next() {
        if (size == 0)
            throw runtime_error("List is empty.");
        current = current->next;
    }

    // Mueve la posición actual a la anterior
    void previous() {
        if (size == 0)
            throw runtime_error("List is empty.");

        // Recorremos desde current hasta encontrar el nodo cuyo next sea current
        Node<E>* temp = current;
        while (temp->next != current)
            temp = temp->next;
        current = temp;
    }

    int getSize() {
        return size;
    }

    void print() {
        cout << "[ ";
        if (size > 0) {
            Node<E>* temp = current->next;
            for (int i = 0; i < size; i++) {
                cout << temp->element;
                if (i < size - 1) cout << ", ";
                temp = temp->next;
            }
        }
        cout << " ]" << endl;
    }
};