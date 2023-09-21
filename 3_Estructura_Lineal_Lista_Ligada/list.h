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

template <class T>
class List;

/**
 * @brief Node with templates for a single linked list
 */
template <class T>
class Node {
 private:
  T value;
  Node *next;
  /**
   * @brief Create a node tha points to nullptr by default with a value
   * @param value Any data value that can be used in a template
   */
  Node(T);
  Node(T, Node<T> *);
  Node(const Node<T> &);
  Node &operator=(const Node &other);

  friend class List<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), next(nullptr) {}

template <class T>
Node<T>::Node(T val, Node *nxt) : value(val), next(nxt) {}

template <class T>
Node<T>::Node(const Node<T> &src) : value(src.value), next(src.next) {}

template <class T>
Node<T> &Node<T>::operator=(const Node &other) {
  if (this != &other) {
    // Copy the value
    value = other.value;
    // Copy the next pointer
    next = other.next;
  }
  return *this;
}

/**
 * @brief Single Linked List data structure with a head and tail
 */
template <class T>
class List {
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

template <class T>
List<T>::List() : head(nullptr), elements(0) {}

template <typename T>
List<T>::List(const List<T> &other) {
  // Initialize head and elements
  head = nullptr;
  elements = 0;

  // Iterate through the nodes of 'other' and copy each node
  Node<T> *otherCurrent = other.head;
  Node<T> *prev = nullptr;

  while (otherCurrent != nullptr) {
    // Create a new node and copy the value
    Node<T> *newNode = new Node<T>(otherCurrent->value);

    // If it's the first node, set it as the head
    if (prev == nullptr) {
      head = newNode;
    } else {
      // Otherwise, link it to the previous node
      prev->next = newNode;
    }

    // Update 'prev' and move to the next node in 'other'
    prev = newNode;
    otherCurrent = otherCurrent->next;

    // Increase the element count
    elements++;
  }
}

template <class T>
List<T>::~List() {
  Node<T> *current = head;
  while (current != nullptr) {
    Node<T> *temp = current;
    current = current->next;
    delete temp;
  }
  head = nullptr;  // Set head to nullptr to indicate an empty list
  elements = 0;    // Reset the number of elements to zero
}

template <class T>
std::string List<T>::toString() {
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


template <typename T>
void List<T>::insertion(T value) {
  // Create a new node with the value
  Node<T> *newNode = new Node<T>(value);
  // If the list is empty, set the new node as the head
  if (elements == 0) {
    head = newNode;
  } else {
    // Otherwise, traverse the list to find the last node
    Node<T> *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    // Attach the new node to the last node
    current->next = newNode;
  }
  // Increment the list size
  elements++;
}

template <typename T>
int List<T>::search(T element) {
  // empty list, lol
  if (elements == 0) return -1;

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

template <typename T>
void List<T>::update(unsigned int index, T value) {
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
template <typename T>
T List<T>::deleteHead() {
  // Do nothing if empty
  if (elements == 0) return -1;

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

template <typename T>
T List<T>::deleteAt(unsigned int index) {
  // cant delete with no elements
  if (elements == 0) return -1;

  // index is out of bound
  if (index < 0 || index >= elements) return -1;

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

#endif  // LIST_H
