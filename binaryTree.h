#ifndef COURSE_PROJECT_BINARYTREE_H
#define COURSE_PROJECT_BINARYTREE_H
#include <iostream>

using namespace std;

class NodeBinary {
public:
    int key;
    NodeBinary *left = nullptr;
    NodeBinary *right = nullptr;

    NodeBinary(int key) {
        this->key = key;
    }
};

class BinaryTree {
private:
    NodeBinary *node;

    NodeBinary * insert(NodeBinary *node, int key) {
        if (node == nullptr) {
            return new NodeBinary(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    NodeBinary *search(NodeBinary *node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        return (key < node->key) ? search(node->left, key) : search(node->right, key);
    }

    NodeBinary *getMin(NodeBinary *node) {
        if (node == nullptr || node->left == nullptr) {
            return node;
        }

        return getMin(node->left);
    }

    NodeBinary *getMax(NodeBinary *node) {
        if (node == nullptr || node->right == nullptr) {
            return node;
        }

        return getMax(node->right);
    }

    NodeBinary *deleteElement(NodeBinary *node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = deleteElement(node->left, key);
        } else if (key > node->key) {
            node->right = deleteElement(node->right, key);
        } else {
            if (node->left == nullptr) {
                NodeBinary *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                NodeBinary *temp = node->left;
                delete node;
                return temp;
            }

            NodeBinary *temp = getMin(node->right);
            node->key = temp->key;
            node->right = deleteElement(node->right, temp->key);
        }
        return node;
    }

public:
    BinaryTree() : node(nullptr) {}

    void insert(int key) {
        node = insert(node, key);
    }

    void remove(int key) {
        node = deleteElement(node, key);
    }
};


#endif //COURSE_PROJECT_BINARYTREE_H
