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
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;
  Node* tail;
  int count;

 public:
  TPQueue() : head(nullptr), tail(nullptr), count(0) {}

  ~TPQueue() {
    while (!isEmpty()) {
      pop();
    }
  }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (isEmpty()) {
      head = tail = newNode;
      count++;
      return;
    }

    if (item.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      count++;
      return;
    }

    Node* current = head;
    while (current->next != nullptr &&
           current->next->data.prior >= item.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    if (newNode->next == nullptr) {
      tail = newNode;
    }

    count++;
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }

    Node* temp = head;
    T result = head->data;
    head = head->next;

    if (head == nullptr) {
      tail = nullptr;
    }

    delete temp;
    count--;
    return result;
  }

  T front() const {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }
    return head->data;
  }

  bool isEmpty() const {
    return head == nullptr;
  }

  int size() const {
    return count;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
