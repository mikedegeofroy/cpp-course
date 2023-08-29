#pragma once

// Wait, this is dumb. Those should be blocks. Should they be blocks?

template <typename T>
class LinkedList {
 public:
  struct Node {
    T* data;
    Node* next = nullptr;
  };

  Node* head = nullptr;

 public:
  LinkedList();

  void insert(Node* prev_node, Node* new_node);
  void remove(Node* prev_node, Node* delete_node);
  bool empty() { return head == nullptr; }
  void push(Node* node);
  Node* pop() {
    Node* tmp = head;
    remove(nullptr, head);
    tmp->next = nullptr;  // Set the next pointer of the removed node to nullptr
    return tmp;
  };
};

template <typename T>
inline LinkedList<T>::LinkedList() {}

template <typename T>
inline void LinkedList<T>::insert(Node* prev_node, Node* new_node) {
  if (prev_node == nullptr) {
    if (head != nullptr) {
      new_node->next = head;
    } else {
      new_node->next = nullptr;
    }
    head = new_node;
  } else {
    if (prev_node->next == nullptr) {
      prev_node->next = new_node;
      new_node->next = nullptr;
    } else {
      new_node->next = prev_node->next;
      prev_node->next = new_node;
    }
  }
}

template <typename T>
inline void LinkedList<T>::remove(Node* prev_node, Node* delete_node) {
  if (prev_node == nullptr) {
    if (delete_node->next == nullptr) {
      head = nullptr;
    } else {
      head = delete_node->next;
    }
  } else {
    prev_node->next = delete_node->next;
  }
}

template <typename T>
inline void LinkedList<T>::push(Node* node) {
  insert(nullptr, node);
}
