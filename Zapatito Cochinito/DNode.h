#pragma once
#ifndef DNODE_H
#define DNODE_H

template <typename E>
class DNode {
public:
    E element;
    DNode<E>* next;
    DNode<E>* prev;

    DNode(E element, DNode<E>* next = nullptr, DNode<E>* prev = nullptr)
        : element(element), next(next), prev(prev) {
    }
};

#endif