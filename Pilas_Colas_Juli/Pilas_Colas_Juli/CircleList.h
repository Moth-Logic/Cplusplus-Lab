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
    void insert(E element) {
        if (size == 0) {
                new Node<E>(element);
                current->next = current;
        }
        else {
            current->next = new Node<E>(element, current->next);
        }
        size++;
    }
    void insertBack(E element) {
        insert(element);
        current = current->next;
    }
};

