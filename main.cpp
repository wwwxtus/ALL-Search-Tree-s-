#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "BTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "binaryTree.h"
#include "SplayTree.h"


using namespace std;
using namespace std::chrono;

void testInsertDelete(BTree& bTree, SplayTree &splayTree,  RedBlackTree &rbTree, BinaryTree &binarySearchTree, AVLTree& avlTree, vector<int>& data) {
    auto start = high_resolution_clock::now();
    for (int key : data) {
        bTree.insert(key);
    }
    auto stop = high_resolution_clock::now();
    auto durationBTreeInsert = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        splayTree.insert(key);
    }
    stop = high_resolution_clock::now();
    auto durationSplayInsert = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        rbTree.insert(key);
    }
    stop = high_resolution_clock::now();
    auto durationRBInsert = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        avlTree.insert(key);
    }
    stop = high_resolution_clock::now();
    auto durationAVLInsert = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        binarySearchTree.insert(key);
    }
    stop = high_resolution_clock::now();
    auto durationBinaryInsert = duration_cast<milliseconds>(stop - start);

//     Теперь проведем тесты удаления
    start = high_resolution_clock::now();
    for (int key : data) {
        bTree.remove(key);
    }
    stop = high_resolution_clock::now();
    auto durationBTreeDelete = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        splayTree.deleteNode(key);
    }
    stop = high_resolution_clock::now();
    auto durationSplayDelete = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        rbTree.remove(key);
    }
    stop = high_resolution_clock::now();
    auto durationRBDelete = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        avlTree.remove(key);
    }
    stop = high_resolution_clock::now();
    auto durationAVLDelete = duration_cast<milliseconds>(stop - start);

    start = high_resolution_clock::now();
    for (int key : data) {
        binarySearchTree.remove(key);
    }
    stop = high_resolution_clock::now();
    auto durationBinaryDelete = duration_cast<milliseconds>(stop - start);

    // Вывод результатов
    cout << "=================================================" << endl;
    cout << "|        Data insertion and deletion time        |" << endl;
    cout << "|================================================|" << endl;
    cout << "| Tree      |   Insert (ms)   |  Removal (ms)    |" << endl;
    cout << "|===========|=================|==================|" << endl;
    cout << "| Binary    | " << durationBinaryInsert.count() << " ms            | " << durationBinaryDelete.count() << " ms             |" << endl;
    cout << "| AVL       | " << durationAVLInsert.count() << " ms            | " << durationAVLDelete.count() << " ms             |" << endl;
    cout << "| Red-Black | " << durationRBInsert.count() << " ms            |  " << " ms            |" << endl;
    cout << "| B-tree    | " << durationBTreeInsert.count() << " ms            | " << durationBTreeDelete.count() << " ms             |" << endl;
    cout << "| Splay     | " << durationSplayInsert.count() << " ms           | " << durationSplayDelete.count() << " ms             |" << endl;
    cout << "|===========|=================|==================|" << endl;
}

vector<int> generateRandomData(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);

    vector<int> testData;
    for (int i = 0; i < size; ++i) {
        testData.push_back(distrib(gen));
    }

    return testData;
}

int main() {
    int testDataSize = 10000;

    vector<int> testData = generateRandomData(testDataSize);

    BTree bTree(16);
    SplayTree splayTree;
    RedBlackTree rbTree;
    AVLTree avlTree;
    BinaryTree binarySearchTree;

    // Запуск теста вставки и удаления
    testInsertDelete(bTree, splayTree, rbTree, binarySearchTree, avlTree,  testData);

    return 0;
}
