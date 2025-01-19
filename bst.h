#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    Node(T data) : data(data), left(nullptr), right(nullptr), parent(nullptr){}
};

template <typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, T data) {
        if (node == nullptr) {
            return new Node<T>(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }
        return node;
    }

    bool search(Node<T>* node, T data) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == data) {
            return true;
        }
        if (data < node->data) {
            return search(node->left, data);
        } else {
            return search(node->right, data);
        }
    }

    void inorder(Node<T>* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(T data) {
        root = insert(root, data);
    }

    bool search(T data) {
        return search(root, data);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

#endif
