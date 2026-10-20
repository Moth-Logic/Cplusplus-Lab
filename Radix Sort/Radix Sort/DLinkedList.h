#pragma once
#include <stdexcept>

template <typename T>
class DLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int   count;

public:
    DLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DLinkedList() { clear(); }

    DLinkedList(const DLinkedList&)            = delete;
    DLinkedList& operator=(const DLinkedList&) = delete;

    DLinkedList(DLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    DLinkedList& operator=(DLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head  = other.head;
            tail  = other.tail;
            count = other.count;
            other.head = other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        count = 0;
    }

    void addLast(const T& value) {
        Node* n = new Node(value);
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev    = tail;
            tail       = n;
        }
        count++;
    }

    T removeFirst() {
        if (!head) throw std::runtime_error("DLinkedList: lista vacia");
        Node* n = head;
        T value = n->data;
        head = head->next;
        if (head) head->prev = nullptr;
        else      tail = nullptr;
        delete n;
        count--;
        return value;
    }

    int  size()    const { return count; }
    bool isEmpty() const { return head == nullptr; }
};