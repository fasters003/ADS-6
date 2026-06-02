// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
    };
    
    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node* newNode = new Node{item, nullptr};

        if (head == nullptr || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->data.prior >= item.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    T pop() {
        if (head == nullptr) {
            throw std::runtime_error("Queue is empty!");
        }
        
        Node* temp = head;
        T item = temp->data;
        head = head->next;
        delete temp;
        
        return item;
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
