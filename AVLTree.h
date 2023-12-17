#ifndef COURSEPROJECT_AVLTREE_H
#define COURSEPROJECT_AVLTREE_H

using namespace std;

#include <iostream>
#include <algorithm>

//class NodeAVL {
//public:
//    int key;
//    NodeAVL *left;
//    NodeAVL *right;
//    int height;
//
//    NodeAVL(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
//};
//
//class AVLTree {
//private:
//    NodeAVL *root;
//
//    int getHeight(NodeAVL *node) {
//        return node == nullptr ? -1 : node->height;
//    }
//
//    NodeAVL *getMax(NodeAVL *node) {
//        if (node == nullptr || node->right == nullptr) {
//            return node;
//        }
//
//        return getMax(node->right);
//    }
//
//    void updateHeight(NodeAVL *node) {
//        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
//    }
//
//    int getBalance(NodeAVL *node) {
//        return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left);
//    }
//
//    void swapAVL(NodeAVL *a, NodeAVL *b) {
//        int aKey = a->key;
//        a->key = b->key;
//        b->key = aKey;
//    }
//
//    void rightRotate(NodeAVL *node) {
//        swapAVL(node, node->left);
//
//        NodeAVL *buffer = node->right;
//        node->right = node->left;
//        node->right->left = node->right->right;
//        node->right->right = buffer;
//        updateHeight(node->right);
//        updateHeight(node);
//    }
//
//    void leftRotate(NodeAVL *node) {
//        swapAVL(node, node->right);
//
//        NodeAVL *buffer = node->left;
//        node->left = node->right;
//        node->left->right = node->left->left;
//        node->left->left = buffer;
//        updateHeight(node->left);
//        updateHeight(node);
//    }
//
//    void balance(NodeAVL *node) {
//        int balance = getBalance(node);
//        if (balance == -2) {
//            if (getBalance(node->left) == 1) {
//                leftRotate(node->left);
//            }
//
//            rightRotate(node);
//        } else if (balance == 2) {
//            if (getBalance(node->right) == -1) {
//                rightRotate(node->right);
//            }
//
//            leftRotate(node);
//        }
//    }
//
//    void insertUtil(NodeAVL *root, int key) {
//        if (key < root->key) {
//            if (root->left == nullptr) {
//                root->left = new NodeAVL(key);
//            } else {
//                insertUtil(root, key);
//            }
//        } else if (key >= root->key) {
//            if (root->right == nullptr) {
//                root->right = new NodeAVL(key);
//            } else {
//                insertUtil(root, key);
//            }
//        }
//
//        updateHeight(root);
//        balance(root);
//    }
//
//    NodeAVL *deleteUtil(NodeAVL *node, int key) {
//        if (node == nullptr) {
//            return nullptr;
//        } else if (key < node->key) {
//            node->left = deleteUtil(node->left, key);
//        } else if (key > node->key) {
//            node->right = deleteUtil(node->right, key);
//        } else {
//            if (node->left == nullptr || node->right == nullptr){
//                node = node->left == nullptr ? node->right : node->left;
//            } else {
//                NodeAVL *maxInLeft = getMax(node->left);
//                node->key = maxInLeft->key;
//                node->right = deleteUtil(node->right, maxInLeft->key);
//            }
//        }
//
//        if (node != nullptr) {
//            updateHeight(node);
//            balance(node);
//        }
//
//        return node;
//    }
//
//public:
//    AVLTree() : root(nullptr) {}
//
//    void insert(int key) {
//        insertUtil(root, key);
//    }
//
//    void remove(int key) {
//        root = deleteUtil(root, key);
//    }
//
//    NodeAVL *search(int key) {
//        NodeAVL *temp = root;
//        while (temp != nullptr && key != temp->key) {
//            if (key < temp->key) temp = temp->left;
//            else temp = temp->right;
//        }
//        return temp;
//    }
//};

#include <iostream>
#include <algorithm>

class NodeAVL {
public:
    int key;
    NodeAVL *left;
    NodeAVL *right;
    int height;

    NodeAVL(int key) : key(key), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    NodeAVL *root;

    int getHeight(NodeAVL *node) {
        return node ? node->height : 0;
    }

    void updateHeight(NodeAVL *node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalanceFactor(NodeAVL *node) {
        return !node ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    NodeAVL *getMinNode(NodeAVL *node) {
        return !node || !node->left ? node : getMinNode(node->left);
    }

    NodeAVL *getMaxNode(NodeAVL *node) {
        if (node == nullptr || node->right == nullptr) {
            return node;
        }

        return getMaxNode(node->right);
    }

    NodeAVL *searchUtil(int key) {
        NodeAVL *x = root;
        while(x != nullptr && key != x->key) {
            if (key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        return x;
    }

    NodeAVL *rightRotate(NodeAVL *node) {
        NodeAVL *A = node->left;
        NodeAVL *Y = A->right;

        A->right = node;
        node->left = Y;
        updateHeight(node);
        updateHeight(A);

        return A;
    }

    NodeAVL *leftRotate(NodeAVL *node) {
        NodeAVL *B = node->right;
        NodeAVL *Y = B->left;

        B->left = node;
        node->right = Y;

        updateHeight(node);
        updateHeight(B);

        return B;
    }

    void balance(NodeAVL *node) {
        int balance = getBalanceFactor(node);
        if (balance == -2) {
            if (getBalanceFactor(node->left) == 1) {
                leftRotate(node->left);
            }

            rightRotate(node);
        } else if (balance == 2) {
            if (getBalanceFactor(node->right)) {
                rightRotate(node->right);
            }

            leftRotate(node);
        }
    }

    NodeAVL *insertUtil(NodeAVL *node, int key) {
        if (!node) {
            return new NodeAVL(key);
        } else if (key < node->key) {
            node->left = insertUtil(node->left, key);
        } else {
            node->right = insertUtil(node->right, key);
        }

        updateHeight(node);

        int bf = getBalanceFactor(node);

        if (bf > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        if (bf < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        if (bf > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    NodeAVL *deleteUtil(NodeAVL *node, int key) {
        NodeAVL *temp;
        if (node == nullptr) {
            return node;
        } else if (key < node->key) {
            node->left = deleteUtil(node->left, key);
        } else if (key > node->key) {
            node->right = deleteUtil(node->right, key);
        } else {
            if (!node->left) {
                temp = node->right;
                node = nullptr;
                return temp;
            } else if (!node->right) {
                temp = node->left;
                node = nullptr;
                return temp;
            }

            temp = getMinNode(node->right);
            node->key = temp->key;
            node->right = deleteUtil(node->right, temp->key);
        }

        updateHeight(node);

        int bf = getBalanceFactor(node);

        if (bf > 1 && getBalanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        if (bf < -1 && getBalanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        if (bf > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bf < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);

        }

        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insertUtil(root, key);
    }

    void remove(int key) {
        root = deleteUtil(root, key);
    }

    void search(int key) {
        searchUtil(key);
    }
};


#endif //COURSEPROJECT_AVLTREE_H
