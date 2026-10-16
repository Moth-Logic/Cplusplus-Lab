#pragma once
#ifndef DNODE_H
#define DNODE_H

// Node for a doubly linked list: it knows the next node AND the previous one.
template <typename E>
class DNode {
public:
    E element;
    DNode<E>* next;
    DNode<E>* prev;

    DNode(E element, DNode<E>* next = nullptr, DNode<E>* prev = nullptr)
        : element(element), next(next), prev(prev) {
    }

    // Default constructor: used for sentinel (dummy) nodes in DLinkedList.
    DNode() : next(nullptr), prev(nullptr) {
    }
};

#endif