#pragma once

// Abstract List ADT with a cursor.
// The cursor sits ON a position (0..size); the "current element" is the one at
// that position. When the cursor is at size there is no current element, which
// is how the implementations detect "at the end".
template <typename E>
class List {
public:
	// Owns heap memory -> copying disabled to prevent double frees.
	List(const List<E>&) = delete;
	void operator = (const List<E>&) = delete;
	List() {}
	virtual ~List() {}

	virtual void insert(E element) = 0;   // insert AT the cursor, shifting the rest right
	virtual void append(E element) = 0;   // add at the end (cursor does not move)
	virtual void setElement(E element) = 0; // overwrite the current element
	virtual E remove() = 0;               // delete and return the current element
	virtual void clear() = 0;             // empty the list and reset the cursor
	virtual E getElement() = 0;           // read the current element

	// Cursor movement / inspection.
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;              // advance one position (stops at the end)
	virtual void previous() = 0;          // go back one position (stops at the start)
	virtual bool atEnd() = 0;             // cursor is past the last element
	virtual bool atStart() = 0;           // cursor is at position 0
	virtual int getPos() = 0;             // current cursor position
	virtual int getSize() = 0;            // number of stored elements

	virtual void print() = 0;
};
