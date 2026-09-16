#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	void insert(E element) {
		current->next = new DNode(element, current->next, current);
		current->next->next->previous = current->next;
		size++;
	}
	void append(E element) {
		tail->previous->next = new DNode(element, tail, tail->previous);
        tail->previous = tail->previous->next;
        size++;
	}
    void setElement(E element) {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current->previous == tail)
            throw runtime_error("No current element");
        current->next->element = element;
    }
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current->previous == tail)
            throw runtime_error("No current element");
        E result = current->next->element;
        current->next = current->next->element;
        delete current->next->previous;
        current->next->previous = current;
        size--;
        return result;
    }
    void clear() {
        while (current->next != tail) {
            current->next = current->next->next;
            delete head->next->previous;
        }
        tail->previous = head;
        size = 0;
    }
};
