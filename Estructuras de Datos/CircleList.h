#pragma once
#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "Clist.h"
#include "Node.h"
#include <iostream>
#include <stdexcept>

template <typename E>
class CircleList : public Clist<E> {
private:
    Node<E>* current;
    int size;

public:
    CircleList() : current(nullptr), size(0) {}

    virtual ~CircleList() {
        clear();
    }

    void insert(E element) override {
        Node<E>* newNode = new Node<E>(element);
        if (size == 0) {
            newNode->next = newNode;
            current = newNode;
        }
        else {
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    void insertBack(E element) override {
        Node<E>* newNode = new Node<E>(element);
        if (size == 0) {
            newNode->next = newNode;
            current = newNode;
        }
        else {
            newNode->next = current->next;
            current->next = newNode;
            current = newNode;
        }
        size++;
    }

    E remove() override {
        if (size == 0) {
            throw std::runtime_error("Lista vacia");
        }

        E element = current->next->element;

        if (size == 1) {
            delete current;
            current = nullptr;
        }
        else {
            Node<E>* front = current->next;
            current->next = front->next;
            delete front;
        }

        size--;
        return element;
    }

    E removeBack() override {
        if (size == 0) {
            throw std::runtime_error("Lista vacia");
        }

        E element = current->element;

        if (size == 1) {
            delete current;
            current = nullptr;
        }
        else {
            Node<E>* prev = current->next;
            while (prev->next != current) {
                prev = prev->next;
            }
            prev->next = current->next;
            delete current;
            current = prev;
        }

        size--;
        return element;
    }

    void clear() override {
        if (size > 0) {
            Node<E>* aux = current->next;
            while (aux != current) {
                Node<E>* next = aux->next;
                delete aux;
                aux = next;
            }
            delete current;
            current = nullptr;
            size = 0;
        }
    }

    E getFront() override {
        if (size == 0) {
            throw std::runtime_error("Lista vacia");
        }
        return current->next->element;
    }

    E getBack() override {
        if (size == 0) {
            throw std::runtime_error("Lista vacia");
        }
        return current->element;
    }

    void next() override {
        if (size > 0) {
            current = current->next;
        }
    }

    void previous() override {
        if (size > 0) {
            Node<E>* prev = current->next;
            while (prev->next != current) {
                prev = prev->next;
            }
            current = prev;
        }
    }

    int getSize() override {
        return size;
    }

    void print() override {
        if (size == 0) {
            std::cout << "[]" << std::endl;
            return;
        }

        Node<E>* aux = current->next;
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << aux->element;
            if (i < size - 1) {
                std::cout << ", ";
            }
            aux = aux->next;
        }
        std::cout << "]" << std::endl;
    }
};

#endif