#pragma once

#include <stdexcept>
#include <iostream>
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class MinHeap {
private:
	E* elements;
	int max;
	int size;

	int parent(int pos) {
		return (pos - 1) / 2;
	}
	int leftChild(int pos) {
		return pos * 2 + 1;
	}
	int rightChild(int pos) {
		return pos * 2 + 2;
	}
	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}
	int minChild(int pos) {
		int left = leftChild(pos);
		int right = rightChild(pos);
		if (right < size && elements[right] < elements[left])
			return right;
		return left;
	}
	void siftUp(int pos) {
		while (pos > 0 && elements[pos] < elements[parent(pos)]) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	void siftDown(int pos) {
		while (!isLeaf(pos)) {
			int child = minChild(pos);
			if (elements[pos] <= elements[child])
				break;
			swap(pos, child);
			pos = child;
		}
	}
	void swap(int pos1, int pos2) {
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}

public:
	MinHeap(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		size = 0;
	}
	~MinHeap() {
		delete[] elements;
	}
	void insert(E element) {
		if (size == max)
			throw runtime_error("Heap is full.");
		elements[size] = element;
		siftUp(size);
		size++;
	}
	E first() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return elements[0];
	}
	E removeFirst() {
		if (size == 0)
			throw runtime_error("Heap is empty");
		return remove(0);
	}
	E remove(int pos) {
		if (pos < 0 || pos >= size)
			throw runtime_error("Index out of bounds.");

		E removed = elements[pos];
		if (size == 1) {
			size = 0;
			return removed;
		}

		swap(pos, size - 1);
		size--;
		if (pos < size) {
			if (pos > 0 && elements[pos] < elements[parent(pos)])
				siftUp(pos);
			else
				siftDown(pos);
		}
		return removed;
	}
	void clear() {
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i < size - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
};