#pragma once
#ifndef NODE_H
#define NODE_H

template <typename E>
class Node {
public:
    E element;
    Node<E>* next;

    Node(E element, Node<E>* next = nullptr)
        : element(element), next(next) {
    }

    // Default constructor: used for sentinel (dummy) nodes, e.g. in LinkedList and LinkedQueue.
    Node() : next(nullptr) {
    }
};

#endif