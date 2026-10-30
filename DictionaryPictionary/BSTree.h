#pragma once

#include <iostream>
#include <stdexcept>
#include "BSTNode.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class BSTree {
private:
	BSTNode<E>* root;
	int size;

	BSTNode<E>* insertAux(BSTNode<E>* node, const E& element) {
		if (node == nullptr) {
			BSTNode<E>* inserted = new BSTNode<E>(element);
			size++;
			return inserted;
		}
		if (element < node->data)
			node->left = insertAux(node->left, element);
		else if (element > node->data)
			node->right = insertAux(node->right, element);
		else
			throw runtime_error("Duplicated element.");
		return node;
	}

	BSTNode<E>* findAux(BSTNode<E>* node, const E& element) const {
		if (node == nullptr || (!(element < node->data) && !(element > node->data)))
			return node;
		if (element < node->data)
			return findAux(node->left, element);
		return findAux(node->right, element);
	}

	BSTNode<E>* removeAux(BSTNode<E>* node, const E& element) {
		if (element < node->data) {
			node->left = removeAux(node->left, element);
		}
		else if (element > node->data) {
			node->right = removeAux(node->right, element);
		}
		else if (node->left == nullptr) {
			BSTNode<E>* right = node->right;
			delete node;
			return right;
		}
		else if (node->right == nullptr) {
			BSTNode<E>* left = node->left;
			delete node;
			return left;
		}
		else {
			BSTNode<E>* successor = node->right;
			while (successor->left != nullptr)
				successor = successor->left;
			node->data = successor->data;
			node->right = removeMinAux(node->right);
		}
		return node;
	}

	BSTNode<E>* removeMinAux(BSTNode<E>* node) {
		if (node->left == nullptr) {
			BSTNode<E>* right = node->right;
			delete node;
			return right;
		}
		node->left = removeMinAux(node->left);
		return node;
	}

	void clearAux(BSTNode<E>* node) {
		if (node == nullptr)
			return;
		clearAux(node->left);
		clearAux(node->right);
		delete node;
	}

	void printAux(BSTNode<E>* node, bool& first) const {
		if (node == nullptr)
			return;
		printAux(node->left, first);
		if (!first)
			cout << ", ";
		cout << node->data;
		first = false;
		printAux(node->right, first);
	}

public:
	BSTree() : root(nullptr), size(0) {}

	BSTree(const BSTree<E>&) = delete;
	void operator=(const BSTree<E>&) = delete;

	~BSTree() {
		clear();
	}

	void insert(const E& element) {
		root = insertAux(root, element);
	}

	E remove(const E& element) {
		BSTNode<E>* node = findAux(root, element);
		if (node == nullptr)
			throw runtime_error("Element not found.");
		E removed = node->data;
		root = removeAux(root, element);
		size--;
		return removed;
	}

	bool contains(const E& element) const {
		return findAux(root, element) != nullptr;
	}

	E getMin() const {
		if (root == nullptr)
			throw runtime_error("Tree is empty.");
		BSTNode<E>* node = root;
		while (node->left != nullptr)
			node = node->left;
		return node->data;
	}

	E getMax() const {
		if (root == nullptr)
			throw runtime_error("Tree is empty.");
		BSTNode<E>* node = root;
		while (node->right != nullptr)
			node = node->right;
		return node->data;
	}

	void clear() {
		clearAux(root);
		root = nullptr;
		size = 0;
	}

	int getSize() const {
		return size;
	}

	bool isEmpty() const {
		return size == 0;
	}

	void print() const {
		cout << "[";
		bool first = true;
		printAux(root, first);
		cout << "]" << endl;
	}
};
