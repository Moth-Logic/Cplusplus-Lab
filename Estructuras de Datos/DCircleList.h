#pragma once
#ifndef DCIRCLELIST_H
#define DCIRCLELIST_H

#include "Clist.h"
#include "DNode.h"
#include <iostream>
#include <stdexcept>

template <typename E>
class DCircleList : public Clist<E> {
private:
    DNode<E>* current;
    int size;

public:
    DCircleList() : current(nullptr), size(0) {}

    virtual ~DCircleList() {
        clear();
    }

    void insert(E element) override {
        DNode<E>* newNode = new DNode<E>(element);
        if (size == 0) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        }
        else {
            DNode<E>* front = current->next;
            newNode->next = front;
            newNode->prev = current;
            front->prev = newNode;
            current->next = newNode;
        }
        size++;
    }

    void insertBack(E element) override {
        DNode<E>* newNode = new DNode<E>(element);
        if (size == 0) {
            newNode->next = newNode;
            newNode->prev = newNode;
            current = newNode;
        }
        else {
            DNode<E>* front = current->next;
            newNode->next = front;
            newNode->prev = current;
            front->prev = newNode;
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
            DNode<E>* front = current->next;
            current->next = front->next;
            front->next->prev = current;
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
            DNode<E>* back = current;
            DNode<E>* prev = current->prev;
            prev->next = back->next;
            back->next->prev = prev;
            delete back;
            current = prev;
        }

        size--;
        return element;
    }

    void clear() override {
        if (size > 0) {
            DNode<E>* aux = current->next;
            while (aux != current) {
                DNode<E>* next = aux->next;
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
            current = current->prev;
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

        DNode<E>* aux = current->next;
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