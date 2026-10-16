#pragma once

#include <stdexcept>
#include "Dictionary.h"
#include "ArrayList.h"
#include "DLinkedList.h"
#include "Pair.h"

using std::runtime_error;

// Dictionary stored as an UNSORTED list of (key, value) pairs.
// Storage is an ArrayList (random access, O(n) insert/remove), so EVERY
// operation that has to locate a key is a linear scan -> O(n).
template <typename K, typename V>
class UnsortedListDictionary : public Dictionary<K, V> {
private:
	List<Pair<K, V>>* pairs; // the actual data

	// Linear search by key. If the key is found it leaves the cursor ON that
	// pair (so callers can read/remove it) and returns true; otherwise the
	// cursor ends at the end of the list and it returns false.
	bool find(K key) {
		Pair<K, V> p(key); // Pair compares by key only
		pairs->goToStart();
		while (!pairs->atEnd()) {
			if (p == pairs->getElement())
				return true;
			pairs->next();
		}
		return false;
	}

public:
	UnsortedListDictionary(int max = DEFAULT_MAX) {
		pairs = new ArrayList<Pair<K, V>>(max); // fixed capacity, default DEFAULT_MAX
	}
	~UnsortedListDictionary() {
		delete pairs; // frees the list, which frees its own array
	}

	void insert(K key, V value) {
		if (find(key))
			throw runtime_error("Duplicated key."); // keys must be unique
		Pair<K, V> p(key, value);
		pairs->append(p);
	}
	V remove(K key) {
		if (!find(key))
			throw runtime_error("Key not found.");
		// find() left the cursor on the match, so remove() drops that pair.
		Pair<K, V> p = pairs->remove();
		return p.value;
	}
	V getValue(K key) {
		if (!find(key))
			throw runtime_error("Key not found.");
		Pair<K, V> p = pairs->getElement(); // cursor is on the match
		return p.value;
	}
	void setValue(K key, V value) {
		if (!find(key))
			throw runtime_error("Key not found.");
		Pair<K, V> p(key, value); // replaces the current pair (same key, new value)
		pairs->setElement(p);
	}
	bool contains(K key) {
		return find(key);
	}
	void clear() {
		pairs->clear();
	}
	bool isEmpty() {
		return pairs->getSize() == 0; // List exposes getSize(), not isEmpty()
	}
	int getSize() {
		return pairs->getSize();
	}

	// Walk the pairs once and collect every key into a fresh linked list.
	// The CALLER owns the returned pointer and must delete it.
	List<K>* getKeys() {
		List<K>* keys = new DLinkedList<K>();
		pairs->goToStart();
		while (!pairs->atEnd()) {
			Pair<K, V> p = pairs->getElement();
			keys->append(p.key);
			pairs->next();
		}
		return keys;
	}
	// Same idea, but collects the values.
	List<V>* getValues() {
		List<V>* values = new DLinkedList<V>();
		pairs->goToStart();
		while (!pairs->atEnd()) {
			Pair<K, V> p = pairs->getElement();
			values->append(p.value);
			pairs->next();
		}
		return values;
	}
	void print() {
		pairs->print(); // List::print uses Pair::operator<<
	}
};
