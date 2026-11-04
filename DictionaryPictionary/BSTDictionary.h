#ifndef BST_DICTIONARY_H
#define BST_DICTIONARY_H

#include <cstddef>
#include <utility>

template <typename Key, typename Value>
class BSTDictionary {
private:
	struct Node {
		Key key;
		Value value;
		Node* left;
		Node* right;

		Node(const Key& k, const Value& v)
			: key(k), value(v), left(nullptr), right(nullptr) {}
	};

	Node* root_ = nullptr;
	std::size_t size_ = 0;

	static Node* clone(const Node* node) {
		if (!node) return nullptr;
		Node* copy = new Node(node->key, node->value);
		copy->left = clone(node->left);
		copy->right = clone(node->right);
		return copy;
	}

	static void destroy(Node* node) {
		if (!node) return;
		destroy(node->left);
		destroy(node->right);
		delete node;
	}

	static Node* findNode(Node* node, const Key& key) {
		while (node) {
			if (key < node->key) node = node->left;
			else if (node->key < key) node = node->right;
			else return node;
		}
		return nullptr;
	}

	static Node* insertNode(Node* node, const Key& key, const Value& value,
							bool& inserted) {
		if (!node) {
			inserted = true;
			return new Node(key, value);
		}
		if (key < node->key) node->left = insertNode(node->left, key, value, inserted);
		else if (node->key < key) node->right = insertNode(node->right, key, value, inserted);
		else node->value = value;
		return node;
	}

	static Node* detachMinimum(Node* node, Node*& minimum) {
		if (!node->left) {
			minimum = node;
			return node->right;
		}
		node->left = detachMinimum(node->left, minimum);
		return node;
	}

	static Node* eraseNode(Node* node, const Key& key, bool& erased) {
		if (!node) return nullptr;
		if (key < node->key) node->left = eraseNode(node->left, key, erased);
		else if (node->key < key) node->right = eraseNode(node->right, key, erased);
		else {
			erased = true;
			if (!node->left) {
				Node* right = node->right;
				delete node;
				return right;
			}
			if (!node->right) {
				Node* left = node->left;
				delete node;
				return left;
			}
			Node* successor = nullptr;
			Node* right = detachMinimum(node->right, successor);
			successor->left = node->left;
			successor->right = right;
			delete node;
			return successor;
		}
		return node;
	}

public:
	BSTDictionary() = default;

	BSTDictionary(const BSTDictionary& other)
		: root_(clone(other.root_)), size_(other.size_) {}

	BSTDictionary& operator=(const BSTDictionary& other) {
		if (this != &other) {
			Node* copy = clone(other.root_);
			destroy(root_);
			root_ = copy;
			size_ = other.size_;
		}
		return *this;
	}

	~BSTDictionary() { destroy(root_); }

	// Adds a pair, or replaces the value when the key already exists.
	void insert(const Key& key, const Value& value) {
		bool inserted = false;
		root_ = insertNode(root_, key, value, inserted);
		if (inserted) ++size_;
	}

	Value* find(const Key& key) {
		Node* node = findNode(root_, key);
		return node ? &node->value : nullptr;
	}

	const Value* find(const Key& key) const {
		const Node* node = root_;
		while (node) {
			if (key < node->key) node = node->left;
			else if (node->key < key) node = node->right;
			else return &node->value;
		}
		return nullptr;
	}

	bool contains(const Key& key) const { return find(key) != nullptr; }

	bool erase(const Key& key) {
		bool erased = false;
		root_ = eraseNode(root_, key, erased);
		if (erased) --size_;
		return erased;
	}

	std::size_t size() const { return size_; }
	bool empty() const { return size_ == 0; }

	void clear() {
		destroy(root_);
		root_ = nullptr;
		size_ = 0;
	}
};

#endif // BST_DICTIONARY_H
