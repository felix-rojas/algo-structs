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
  /**
   * @brief Create a node tha points to nullptr by default with a value
   * @param value Any data value that can be used in a template
   */
public:
  T value;
  Node<T> *next;
  Node(T new_value) : value(new_value) {}
};

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

  /**
   * @brief Auxiliary method that deletes the first value of the list
   * @return value of the deleted node
   * @see deleteAt(unsigned int index)
   */
  T deleteHead();

public:
  /**
   * @brief Creates an empty list
   */
  List();
  List(const List<T> &);
  ~List();
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
  /**
   * @brief Clears all content from the Linked List
   */
  void clear();
};

/**
 * @section Method definitions
 */

template <class T> List<T>::List() : head(nullptr), elements(0) {}

template <class T> List<T>::~List() {
  while (head != nullptr) {
    Node<T> *temp = head;
    head = head->next;
    delete temp;
  }
  elements = 0; // Reset the number of elements to zero
}

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

template <typename T> void List<T>::insertion(T value) {
  if (elements == 0) {
    Node<T> *node = new Node<T>(value);
    node->next = head;
    head = node;
    elements++;
  } else {
    Node<T> *prev = head;
    for (int i = 0; i < elements - 1; ++i) {
      prev = prev->next;
    }
    Node<T> *nextNode = prev->next;
    Node<T> *node = new Node<T>(value);
    node->next = nextNode;
    prev->next = node;
    elements++;
  }
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
  // Now it's safe to remove
  // the first element

  // One element is removed
  elements--;
  return head->value;
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
  } else {
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
}

#endif // LIST_H
