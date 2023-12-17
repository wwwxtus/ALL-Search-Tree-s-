#ifndef COURSEPROJECT_SPLAYTREE_H
#define COURSEPROJECT_SPLAYTREE_H
#include <iostream>

using namespace std;

class NodeSplay {
private:
    int data;
    NodeSplay* leftChild;
    NodeSplay* rightChild;
    NodeSplay* parent;

public:
    NodeSplay(int data) : data(data), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}

    NodeSplay* getGrandParent() {
        return parent != nullptr ? parent->getParent() : nullptr;
    }

    bool isLeftChild() {
        return this == parent->getLeftChild();
    }

    bool isRightChild() {
        return this == parent->getRightChild();
    }

    int getData() {
        return data;
    }

    NodeSplay* getLeftChild() {
        return leftChild;
    }

    NodeSplay* getRightChild() {
        return rightChild;
    }

    NodeSplay* getParent() {
        return parent;
    }

    void setParent(NodeSplay* parent) {
        this->parent = parent;
    }

    void setData(int data) {
        this->data = data;
    }

    void setLeftChild(NodeSplay* leftChild) {
        this->leftChild = leftChild;
    }

    void setRightChild(NodeSplay* rightChild) {
        this->rightChild = rightChild;
    }

    void printData() {
        cout << data << " ";
    }
};

class SplayTree {
private:
    NodeSplay* root;

public:
    SplayTree() : root(nullptr) {}

    NodeSplay* getRoot() {
        return root;
    }

    NodeSplay* insert(int data) {
        root = insert(root, new NodeSplay(data));
        return root;
    }

    NodeSplay* insert(NodeSplay* node, NodeSplay* nodeToInsert) {
        if (node == nullptr) {
            return nodeToInsert;
        }
        if (nodeToInsert->getData() < node->getData()) {
            node->setLeftChild(insert(node->getLeftChild(), nodeToInsert));
            node->getLeftChild()->setParent(node);
        } else if (nodeToInsert->getData() > node->getData()) {
            node->setRightChild(insert(node->getRightChild(), nodeToInsert));
            node->getRightChild()->setParent(node);
        }
        return node;
    }

    NodeSplay* deleteNode(int data) {
        root = deleteNode(data, root);
        return root;
    }

    NodeSplay* deleteNode(int data, NodeSplay* node) {
        if (node == nullptr) return nullptr;

        if (data < node->getData()) {
            node->setLeftChild(deleteNode(data, node->getLeftChild()));
            if (node->getLeftChild() != nullptr) node->getLeftChild()->setParent(node);
        } else if (data > node->getData()) {
            node->setRightChild(deleteNode(data, node->getRightChild()));
            if (node->getRightChild() != nullptr) node->getRightChild()->setParent(node);
        } else {
            if (node->getLeftChild() == nullptr) return node->getRightChild();
            else if (node->getRightChild() == nullptr) return node->getLeftChild();
            node->setData(getMax(node->getLeftChild()));
            node->setLeftChild(deleteNode(node->getData(), node->getLeftChild()));
            if (node->getLeftChild() != nullptr) node->getLeftChild()->setParent(node);
        }
        return node;
    }

    NodeSplay* find(int data) {
        NodeSplay* node = root;
        while (node != nullptr) {
            if (node->getData() == data) {
                splay(node);
                return node;
            }
            node = data < node->getData() ? node->getLeftChild() : node->getRightChild();
        }
        return nullptr;
    }

    NodeSplay* findRecursively(int data) {
        return find(root, data);
    }

    NodeSplay* find(NodeSplay* node, int data) {
        if (node != nullptr) {
            if (node->getData() == data) {
                splay(node);
                return node;
            }
            NodeSplay* nextNode = data > node->getData() ? node->getRightChild() : node->getLeftChild();
            find(nextNode, data);
        }
        return nullptr;
    }

    void splay(NodeSplay* node) {
        while (node != root) {
            NodeSplay* parent = node->getParent();
            if (node->getGrandParent() == nullptr) {
                if (node->isLeftChild()) {
                    rotateRight(parent);
                } else {
                    rotateLeft(parent);
                }
            } else if (node->isLeftChild() && parent->isLeftChild()) {
                rotateRight(node->getGrandParent());
                rotateRight(parent);
            } else if (node->isRightChild() && parent->isRightChild()) {
                rotateLeft(node->getGrandParent());
                rotateLeft(parent);
            } else if (node->isLeftChild() && parent->isRightChild()) {
                rotateRight(parent);
                rotateLeft(parent);
            } else {
                rotateLeft(parent);
                rotateRight(parent);
            }
        }
    }

    void rotateRight(NodeSplay* node) {
        NodeSplay* leftNode = node->getLeftChild();
        node->setLeftChild(leftNode->getRightChild());
        if (node->getLeftChild() != nullptr) {
            node->getLeftChild()->setParent(node);
        }
        updateChildrenOfParentNode(node, leftNode);
        leftNode->setParent(node->getParent());
        leftNode->setRightChild(node);
        node->setParent(leftNode);
    }

    void rotateLeft(NodeSplay* node) {
        NodeSplay* rightNode = node->getRightChild();
        node->setRightChild(rightNode->getLeftChild());
        if (node->getRightChild() != nullptr) {
            node->getRightChild()->setParent(node);
        }
        updateChildrenOfParentNode(node, rightNode);
        rightNode->setParent(node->getParent());
        rightNode->setLeftChild(node);
        node->setParent(rightNode);
    }

    void updateChildrenOfParentNode(NodeSplay* node, NodeSplay* tempNode) {
        if (node->getParent() == nullptr) {
            root = tempNode;
        } else if (node->isLeftChild()) {
            node->getParent()->setLeftChild(tempNode);
        } else {
            node->getParent()->setRightChild(tempNode);
        }
    }

    void traverse() {
        traverseInOrder(root);
    }

    void traverseInOrder(NodeSplay* node) {
        if (node != nullptr) {
            traverseInOrder(node->getLeftChild());
            node->printData();
            traverseInOrder(node->getRightChild());
        }
    }

    int getMax() {
        if (isEmpty()) {
            return -1;
        }
        return getMax(root);
    }

    int getMax(NodeSplay* node) {
        if (node->getRightChild() != nullptr) {
            return getMax(node->getRightChild());
        }
        return node->getData();
    }

    int getMin() {
        if (isEmpty()) {
            return -1;
        }
        return getMin(root);
    }

    int getMin(NodeSplay* node) {
        if (node->getLeftChild() != nullptr) {
            return getMin(node->getLeftChild());
        }
        return node->getData();
    }

    bool isEmpty() {
        return root == nullptr;
    }
};

#endif //COURSEPROJECT_SPLAYTREE_H
