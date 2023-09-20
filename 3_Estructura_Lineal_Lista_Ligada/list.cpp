#include "list.h"
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>

template <class T> std::string List<T>::toString() {
  std::stringstream aux;
  Node<T> *p;

  p = head;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->next != 0) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}

template <typename T> void List<T>::insertHead(T value) {
  // Create a temp Node
  Node<T> *node = new Node<T>(value);

  // New node points at head
  node->next = head;

  // The new Node is the Head now
  head = node;

  // If the linked list is empty
  // The Tail is also the Head
  if (elements == 0)
    tail = head;

  // One element is added
  elements++;
}

template <typename T> void List<T>::insertTail(T value) {
  // if empty, invoke insertHead()
  if (elements == 0) {
    insertHead(value);
    return;
  }

  // Create a new Node
  Node<T> *node = new Node<T>(value);
  // same as insertHead, this node becomes tail
  tail->next = node;
  tail = node;
  elements++;
}

template <typename T> void List<T>::insertion(unsigned int index, T value) {
  // Check if the index is out of bound
  if (index < 0 || index > elements)
    return;

  // list has zero elements
  if (index == 0) {
    insertHead(value);
    return;
  }
  // list has index elements
  else if (index == elements) {
    insertTail(value);
    return;
  }

  // Start to find previous node
  // from the Head
  Node<T> *prev = head;

  // Traverse elements until index
  for (int i = 0; i < index - 1; ++i) {
    prev = prev->next;
  }

  // Create the next node which is
  // the element after previous node
  Node<T> *next = prev->next;

  // Create a new node
  Node<T> *node = new Node<T>(value);

  // Insert new node between
  // the previous node and the next node
  node->next = next;
  prev->next = node;

  // increase list size
  elements++;
}
// push_back method for LinkedList
template <typename T> void List<T>::insertion(T value) {
  insertTail(value);
  return;
}

template <typename T> int List<T>::search(T element) {
  // empty list, lol
  if (elements == 0)
    return -1;

  // counter
  int index = 0;

  // Traverse from the Head node
  Node<T> *node = head;

  // Traverse until the selected value
  // is matched with the value
  // of the current position,
  while (node->value != element) {
    index++;
    node = node->next;

    // This will happen
    // if the selected value
    // is not found
    if (node == nullptr) {
      return -1;
    }
  }

  return index;
}
// !TODO
template <typename T> void List<T>::update(unsigned int index, T value) {
  return;
}

template <typename T> T List<T>::deleteHead() {
  // Do nothing if empty
  if (elements == 0)
    return -1;

  // Save the current Head
  // to a new node
  Node<T> *node = head;

  // Point the Head Pointer
  // to the element next to the current Head
  head = head->next;
  T value_copy = head->value;
  // Now it's safe to remove
  // the first element
  delete node;

  // One element is removed
  elements--;
  return value_copy;
}
template <typename T> T List<T>::deleteTail() {
  // one element? remove head
  if (elements == 1) {
    return deleteHead();
  }

  // Start from the Head
  Node<T> *prev = head;

  // were we store the info that gets deleted
  Node<T> *node = head->next;

  // Traverse the elements until
  // the last element
  while (node->next != nullptr) {
    prev = prev->next;
    node = node->next;
  }

  // the prevNode now becomes the Tail
  // so the Next pointer of the prevNode
  // point to NULL
  prev->next = nullptr;
  tail = prev;

  T value_copy = node->value;

  // Now it's safe to remove
  // the last element
  delete node;

  // One element is removed
  elements--;
  return value_copy;
}
// !TODO: test
template <typename T> T List<T>::deleteAt(unsigned int index) {
  // cant delete with no elements
  if (elements == 0)
    return -1;

  // index is out of bound
  if (index < 0 || index >= elements)
    return -1;

  // removing first element
  if (index == 0) {
    return deleteHead();
  }
  // removing last element
  else if (index == elements - 1) {
    return deleteTail();
  }

  // traverse list from Head
  Node<T> *prev = head;

  // Find the element before
  for (int i = 0; i < index - 1; ++i) {
    prev = prev->next;
  }

  // The removed element is after
  Node<T> *node = prev->next;

  // next node to insert
  Node<T> *next = node->next;

  // link prev to next
  prev->next = next;

  T value_copy = node->value;
  // It's now safe to remove
  // the selected index element
  delete node;

  // One element is removed
  elements--;
  return value_copy;
}
