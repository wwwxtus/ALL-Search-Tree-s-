#ifndef COURSEPROJECT_BTREE_H
#define COURSEPROJECT_BTREE_H
#include <iostream>
#include <vector>
using namespace std;

const int MAX_KEYS = 3; // Максимальное количество ключей в узле

class Node {
public:
    vector<int> keys;
    vector<Node*> children;
    bool leaf;

    Node(bool is_leaf = false) : leaf(is_leaf) {}

    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class BTree {
private:
    int t;

    Node* search(int key, Node* node = nullptr) {
        node = (node == nullptr) ? root : node;
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
            i++;
        }
        if (i < node->keys.size() && key == node->keys[i]) {
            return node;
        } else if (node->leaf) {
            return nullptr;
        } else {
            return search(key, node->children[i]);
        }
    }

    void splitChild(Node* x, int i) {
        Node* y = x->children[i];
        Node* z = new Node(y->leaf);
        x->children.insert(x->children.begin() + i + 1, z);
        x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
        z->keys = vector<int>(y->keys.begin() + t, y->keys.end());
        y->keys = vector<int>(y->keys.begin(), y->keys.begin() + t - 1);
        if (!y->leaf) {
            z->children = vector<Node*>(y->children.begin() + t, y->children.end());
            y->children = vector<Node*>(y->children.begin(), y->children.begin() + t);
        }
    }

    void insertNonFull(Node* x, int k) {
        int i = x->keys.size() - 1;
        if (x->leaf) {
            x->keys.push_back(0);
            while (i >= 0 && k < x->keys[i]) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }
            x->keys[i + 1] = k;
        } else {
            while (i >= 0 && k < x->keys[i]) {
                i--;
            }
            i++;
            if (x->children[i]->keys.size() == (2 * t) - 1) {
                splitChild(x, i);
                if (k > x->keys[i]) {
                    i++;
                }
            }
            insertNonFull(x->children[i], k);
        }
    }

    void deleteSibling(Node* x, int i, int j) {
        Node* cnode = x->children[i];
        if (i < j) {
            Node* rsnode = x->children[j];
            cnode->keys.push_back(x->keys[i]);
            x->keys[i] = rsnode->keys[0];
            if (rsnode->children.size() > 0) {
                cnode->children.push_back(rsnode->children[0]);
                rsnode->children.erase(rsnode->children.begin());
            }
            rsnode->keys.erase(rsnode->keys.begin());
        } else {
            Node* lsnode = x->children[j];
            cnode->keys.insert(cnode->keys.begin(), x->keys[i - 1]);
            x->keys[i - 1] = lsnode->keys.back();
            if (lsnode->children.size() > 0) {
                cnode->children.insert(cnode->children.begin(), lsnode->children.back());
                lsnode->children.pop_back();
            }
            lsnode->keys.pop_back();
        }
    }

    void deleteMerge(Node* x, int i, int j) {
        Node* cnode = x->children[i];

        if (j > i) {
            Node* rsnode = x->children[j];
            cnode->keys.push_back(x->keys[i]);
            for (int k = 0; k < rsnode->keys.size(); ++k) {
                cnode->keys.push_back(rsnode->keys[k]);
                if (rsnode->children.size() > 0) {
                    cnode->children.push_back(rsnode->children[k]);
                }
            }
            if (rsnode->children.size() > 0) {
                cnode->children.push_back(rsnode->children.back());
            }
            x->keys.erase(x->keys.begin() + i);
            x->children.erase(x->children.begin() + j);
            delete rsnode;
        } else {
            Node* lsnode = x->children[j];
            lsnode->keys.push_back(x->keys[j]);
            for (int k = 0; k < cnode->keys.size(); ++k) {
                lsnode->keys.push_back(cnode->keys[k]);
                if (cnode->children.size() > 0) {
                    lsnode->children.push_back(cnode->children[k]);
                }
            }
            if (cnode->children.size() > 0) {
                lsnode->children.push_back(cnode->children.back());
            }
            x->keys.erase(x->keys.begin() + j);
            x->children.erase(x->children.begin() + i);
            delete cnode;
        }

        if (x == root && x->keys.empty()) {
            root = x->children[0];
            delete x;
        }
    }

    int deletePredecessor(Node* x) {
        if (x->leaf) {
            int key = x->keys.back();
            x->keys.pop_back();
            return key;
        }
        Node* lastChild = x->children.back();
        if (lastChild->keys.size() >= t) {
            return deletePredecessor(lastChild);
        }
        deleteSibling(x, x->children.size() - 1, x->children.size() - 2);
        return deletePredecessor(lastChild);
    }

    int deleteSuccessor(Node* x) {
        if (x->leaf) {
            int key = x->keys.front();
            x->keys.erase(x->keys.begin());
            return key;
        }
        Node* firstChild = x->children.front();
        if (firstChild->keys.size() >= t) {
            return deleteSuccessor(firstChild);
        }
        deleteSibling(x, 0, 1);
        return deleteSuccessor(firstChild);
    }

    void deleteInternalNode(Node* x, int k, int i) {
        if (x->leaf) {
            if (x->keys[i] == k) {
                x->keys.erase(x->keys.begin() + i);
            }
            return;
        }
        if (x->children[i]->keys.size() >= t) {
            x->keys[i] = deletePredecessor(x->children[i]);
            return;
        }
        if (x->children[i + 1]->keys.size() >= t) {
            x->keys[i] = deleteSuccessor(x->children[i + 1]);
            return;
        }
        deleteMerge(x, i, i + 1);
        deleteInternalNode(x->children[i], k, t - 1);
    }

public:
    BTree(int degree) : t(degree) {
        root = new Node(true);
    }

    ~BTree() {
        delete root;
    }

    void insert(int key) {
        Node* r = root;
        if (r->keys.size() == (2 * t) - 1) {
            Node* s = new Node(false);
            s->children.push_back(root);
            root = s;
            splitChild(s, 0);
            insertNonFull(s, key);
        } else {
            insertNonFull(r, key);
        }
    }

    void remove(int key) {
        if (!root) {
            cout << "Дерево пустое, невозможно удалить ключ" << endl;
            return;
        }
        deleteInternalNode(root, key, 0);
        if (root->keys.empty() && !root->leaf) {
            Node* tmp = root;
            root = root->children[0];
            delete tmp;
        }
    }

    void printTree(Node* x, int level = 0) {
        cout << "Level " << level << ": ";
        for (int i = 0; i < x->keys.size(); ++i) {
            cout << x->keys[i] << " ";
        }
        cout << endl;
        level++;
        if (!x->leaf) {
            for (int i = 0; i < x->children.size(); ++i) {
                printTree(x->children[i], level);
            }
        }
    }

    Node* root;
};

#endif //COURSEPROJECT_BTREE_H
