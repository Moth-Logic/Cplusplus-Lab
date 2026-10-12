#pragma once
#ifndef CLIST_H
#define CLIST_H

template <typename E>
class Clist {
public:
    Clist() {}
    virtual ~Clist() {}

    Clist(const Clist&) = delete;
    Clist& operator=(const Clist&) = delete;

    virtual void insert(E element) = 0;
    virtual void insertBack(E element) = 0;
    virtual E remove() = 0;
    virtual E removeBack() = 0;
    virtual void clear() = 0;
    virtual E getFront() = 0;
    virtual E getBack() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual int getSize() = 0;
    virtual void print() = 0;
};

#endif