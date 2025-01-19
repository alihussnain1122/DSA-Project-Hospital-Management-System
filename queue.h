#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(T data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    T dequeue() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        Node* temp = front;
        T dequeuedData = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return dequeuedData;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    T peek() const {
        if (!isEmpty()) {
            return front->data;
        }
        throw "Queue is empty";
    }

    void printQueue() const {
        Node* temp = front;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Save queue to file
    void saveToFile(std::ofstream& file) const {
        Node* temp = front;
        while (temp) {
            file << temp->data << std::endl;
            temp = temp->next;
        }
    }

    // Load queue from file
    void loadFromFile(std::ifstream& file) {
        T data;
        while (file >> data) {
            enqueue(data);
        }
    }
};

#endif
