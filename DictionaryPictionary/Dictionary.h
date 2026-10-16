#pragma once
#include "List.h"

// Abstract Dictionary ADT: maps unique keys (K) to values (V).
// One key -> one value; "unsorted" refers to how it is stored, not to the API.
template <typename K, typename V>
class Dictionary {
public:
	// The dictionary owns heap memory, so copying is disabled to avoid double frees.
	Dictionary(const Dictionary<K, V>&) = delete;
	void operator = (const Dictionary<K, V>&) = delete;
	Dictionary() {}
	virtual ~Dictionary() {}

	virtual void insert(K key, V value) = 0;   // add a NEW key (duplicated keys are rejected)
	virtual V remove(K key) = 0;               // delete the pair and return its value
	virtual V getValue(K key) = 0;             // read the value stored under key
	virtual void setValue(K key, V value) = 0; // overwrite the value of an existing key
	virtual bool contains(K key) = 0;          // true when key exists
	virtual void clear() = 0;                  // drop every pair
	virtual int getSize() = 0;                 // number of stored pairs
	virtual bool isEmpty() = 0;                // true when size == 0

	// These two build and return a NEW list on the heap; the caller must delete it.
	virtual List<K>* getKeys() = 0;
	virtual List<V>* getValues() = 0;

	virtual void print() = 0;                  // show all pairs
};
