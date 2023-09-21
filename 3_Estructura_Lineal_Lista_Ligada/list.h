#ifndef LIST_H
#define LIST_H
/**
 * @file list.h
 * @date September 19 2023
 * @author: felix-rojas
 */

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>

template <class T> class List;

/**
 * @brief Node with templates for a single linked list
 */
template <class T> class Node {
private:
  T value;
  Node *next;
  /**
   * @brief Create a node tha points to nullptr by default with a value
   * @param value Any data value that can be used in a template
   */
  Node(T);
  Node(T, Node<T>*);
  Node(const Node<T>&);
  friend class List<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), next(nullptr) {}

template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt) {}

template <class T>
Node<T>::Node(const Node<T> &src) : value(src.value), next(src.next) {}

/**
 * @brief Single Linked List data structure with a head and tail
 */
template <class T> class List {
private:
  /**
   * number of nodes in the list
   */
  int elements;
  /**
   * head is the first node in the list, while tail is the last node
   */
  Node<T> *head;
  Node<T> *tail;
  /**
   * @brief Auxiliary method that inserts a value at the beginning of the list
   * @param value is any value to be inserted
   * @see insertion(T value)
   * @return void
   */
  void insertHead(T value);
  /**
   * @brief Auxiliary method that inserts a value at the end of the list
   * @param value is any value to be inserted
   * @see insertion(T value)
   * @return void
   */
  void insertTail(T value);
  /**
   * @brief Auxiliary method that deletes the first value of the list
   * @return value of the deleted node
   * @see deleteAt(unsigned int index)
   */
  T deleteHead();
  /**
   * @brief Auxiliary method that deletes the last value of the list
   * @return value of the deleted node
   * @see deleteAt(unsigned int index)
   */
  T deleteTail();

public:
List();

  /**
   * @brief Inserts a value at the end of the list, similar to append or
   * push_back
   * @param value is any value to be inserted
   * @return void
   */
  void insertion(T value);
  /**
   * @brief Inserts a T value at a specified index, starting from 0
   * @param value is any value to be inserted
   * @param index is the position to place the value
   * @return void
   */
  void insertion(unsigned int index, T value);
  /**
   * @brief Search for value in the list, return index or -1 if not found
   * @param value to look for
   * @return index of the first found element
   * @return -1 when element is not found
   */
  int search(T value);
  /**
   * @brief Change the value of the node at the specified index
   * @param index position to update said value
   * @param value to change
   */
  void update(unsigned int index, T value);
  /**
   * @brief Delete a node from the list and return its value
   * @param index of the node to remove
   * @return value of the deleted node
   */
  T deleteAt(unsigned int index);
  /**
   * @brief Makes a string using sstream in the specified format of the Single
   * Linked List
   * @returns string of the linked list between brackets
   */
  std::string toString();
};

/**
 * @section Method definitions
 */

template <class T> 
List<T>::List() : head(nullptr), elements(0) {}

template <class T> 
List<T>::List() : head(nullptr), elements(0) {}

template <class T> std::string List<T>::toString() {
  std::stringstream aux;
  Node<T> *p;

  p = head;
  aux << "[";
  while (p != nullptr) {
    aux << p->value;
    if (p->next != nullptr) {
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
  if (elements == 0) {
    insertHead(value);
    return;
  }
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

template <typename T> void List<T>::update(unsigned int index, T value) {
  if (index > elements || index < 0) {
    throw;
  }
  Node<T> *node = head;
  int count = 0;

  while (count < index && node->next != nullptr) {
    node = node->next;
    count++;
  }
  node->value = value;
  return;
}

// deletes the first element
template <typename T> T List<T>::deleteHead() {
  // Do nothing if empty
  if (elements == 0)
    return -1;

  // Save head to node
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

  // prev becomes tail
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
  // disjointed from the first element (head)
  for (int i = 1; i < index; i++) {
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

#endif // LIST_H
