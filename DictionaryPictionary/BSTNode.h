#pragma once

template <typename E>
class BSTNode {
public:
    E data;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(const E& element)
        : data(element), left(nullptr), right(nullptr) {}
};
