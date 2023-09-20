#include "list.h"
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
  node->Next = head;

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
  tail->Next = node;
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
    prev = prev->Next;
  }

  // Create the next node which is
  // the element after previous node
  Node<T> *next = prev->Next;

  // Create a new node
  Node<T> *node = new Node<T>(value);

  // Insert new node between
  // the previous node and the next node
  node->Next = next;
  prev->Next = node;

  // increase list size
  elements++;
}
// push_back method for LinkedLIst
template <typename T> void List<T>::insertion(T value) { insertTail(value); }

template <typename T> int List<T>::search(T element) {
  // Start from the Head
  Node<T> *node = head;

  // Iterate through the linked list elements
  // until it finds the selected index
  for (int i = 0; i < elements; ++i) {
    node = node->Next;
    if (node->Value == element)
      return i;
  }

  // Value wasnt found
  return -1;
}
// !TODO
template <typename T> void List<T>::update(unsigned int index, T value) {
  return;
}
// !TODO
template <typename T> T List<T>::deleteAt(unsigned int index) { return 0; }
