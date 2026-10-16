#pragma once

#include <iostream>

using std::ostream;

// A (key, value) entry used inside the dictionary.
// IMPORTANT: ordering and equality compare ONLY the key, so two pairs with the
// same key are considered equal no matter what value they hold. This is what
// lets the dictionary search by key.
template <typename K, typename V>
class Pair {
public:
	K key;
	V value;

	Pair(K key, V value) {
		this->key = key;
		this->value = value;
	}
	Pair(K key) { // key-only pair, used when searching for a key
		this->key = key;
	}
	Pair() {}

	// All comparisons delegate to the key.
	bool operator==(const Pair<K, V>& other) {
		return key == other.key;
	}
	bool operator!=(const Pair<K, V>& other) {
		return key != other.key;
	}
	bool operator<(const Pair<K, V>& other) {
		return key < other.key;
	}
	bool operator<=(const Pair<K, V>& other) {
		return key <= other.key;
	}
	bool operator>(const Pair<K, V>& other) {
		return key > other.key;
	}
	bool operator>=(const Pair<K, V>& other) {
		return key >= other.key;
	}

	// Prints as "(key, value)"; used by List::print().
	friend ostream& operator<<(ostream& os, const Pair<K, V>& pair) {
		os << "(" << pair.key << ", " << pair.value << ")";
		return os;
	}
};
