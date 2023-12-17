#ifndef COURSEPROJECT_REDBLACKTREE_H
#define COURSEPROJECT_REDBLACKTREE_H
#include <iostream>
#include <deque>

#define BLACK true
#define RED false

class NodeRedBlack {
public:
    int key;
    NodeRedBlack* p; // parent
    bool color;
    NodeRedBlack* left;
    NodeRedBlack* right;

    NodeRedBlack(int key) : key(key), p(nullptr), color(RED), left(nullptr), right(nullptr) {}

    std::string printColor() {
        return (color == BLACK) ? "(b)" : "(r)";
    }
};

class RedBlackTree {
private:
    NodeRedBlack* NIL;
    NodeRedBlack* root;

    void leftRotate(NodeRedBlack* x) {
        NodeRedBlack* y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->p = x;

        y->p = x->p;

        if (x->p == nullptr)
            root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;

        y->left = x;
        x->p = y;
    }

    void rightRotate(NodeRedBlack* x) {
        NodeRedBlack* y = x->left;
        x->left = y->right;

        if (y->right != NIL)
            y->right->p = x;

        y->p = x->p;

        if (x->p == nullptr)
            root = y;
        else if (x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;

        y->right = x;
        x->p = y;
    }

    void insertFixup(NodeRedBlack* z) {
        while (z->p != nullptr && z->p->color == RED) {
            if (z->p == z->p->p->left) {
                NodeRedBlack* y = z->p->p->right;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    rightRotate(z->p->p);
                }
            } else {
                NodeRedBlack* y = z->p->p->left;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    leftRotate(z->p->p);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(NodeRedBlack* u, NodeRedBlack* v) {
        if (u->p == nullptr)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;

        v->p = u->p;
    }

    void deleteFixup(NodeRedBlack* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->p->left) {
                NodeRedBlack* w = x->p->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->p->color = RED;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->p);
                    x = root;
                }
            } else {
                NodeRedBlack* w = x->p->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->p->color = RED;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->p;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    NodeRedBlack* searchNode(int key) {
        NodeRedBlack* x = root;
        while (x != NIL && key != x->key) {
            if (key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        return x;
    }

    NodeRedBlack* minimumNode(NodeRedBlack* x) {
        while (x->left != NIL)
            x = x->left;
        return x;
    }

public:
    RedBlackTree() {
        NIL = new NodeRedBlack(99999);
        NIL->color = BLACK;
        NIL->left = nullptr;
        NIL->right = nullptr;
        root = NIL;
    }

    void insert(int key) {
        NodeRedBlack* z = new NodeRedBlack(key);
        NodeRedBlack* y = nullptr;
        NodeRedBlack* x = root;

        while (x != NIL) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->p = y;
        if (y == nullptr)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        insertFixup(z);
    }

    void remove(int key) {
        NodeRedBlack* z = searchNode(key);

        if (z == NIL) {
            std::cout << "Key not found!";
            return;
        }

        NodeRedBlack* y = z;
        NodeRedBlack* x;
        bool yOrigColor = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimumNode(z->right);
            yOrigColor = y->color;
            x = y->right;

            if (y->p == z)
                x->p = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }

        if (yOrigColor == BLACK)
            deleteFixup(x);
    }

    void printTree(bool printColor = false) {
        std::deque<NodeRedBlack*> queue;
        queue.push_back(root);

        while (!queue.empty()) {
            NodeRedBlack* node = queue.front();
            queue.pop_front();

            if (printColor)
                std::cout << node->key << node->printColor() << " ";
            else
                std::cout << node->key << " ";

            if (node->left != NIL)
                queue.push_back(node->left);
            if (node->right != NIL)
                queue.push_back(node->right);
        }
    }
};

#endif //COURSEPROJECT_REDBLACKTREE_H
