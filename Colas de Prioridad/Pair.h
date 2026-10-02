#pragma once

#include <iostream>

using std::ostream;

template <typename K, typename V>
class Pair{
public:
	K key;
	V value;

	Pair(K key, V value) {
		this->key = key;
		this->value = value;
	}
	Pair(K key) {
		this->key = key;
	}
	Pair() {}
	bool operator==(const Pair<K, V>& other) {
		return key == other.key;
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
	bool operator!=(const Pair<K, V>& other) {
		return key != other.key;
	}
	friend ostream& operator<<(ostream& os, Pair<K, V>& pair) {
		os << "(" << pair.key << ", " << pair.value << ")";
		return os;
	}
};

