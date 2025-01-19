#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(T data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (isEmpty()) {
            throw "Stack underflow";
        }
        Node* temp = top;
        T poppedData = temp->data;
        top = top->next;
        delete temp;
        return poppedData;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    T peek() const {
        if (isEmpty()) {
            throw "Stack is empty";
        }
        return top->data;
    }

    // Save stack to file
    void saveToFile(std::ofstream& file) const {
        Node* temp = top;
        while (temp) {
            file << temp->data << std::endl;
            temp = temp->next;
        }
    }

    // Load stack from file
    void loadFromFile(std::ifstream& file) {
        T data;
        while (file >> data) {
            push(data);
        }
    }
};

#endif
