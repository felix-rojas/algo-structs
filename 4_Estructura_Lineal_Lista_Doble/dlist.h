#ifndef DLIST_H
#define DLIST_H
#include <sstream>
#include <string>

template <typename T> class DNode {
public:
  T value;
  DNode<T> *prev;
  DNode<T> *next;
  DNode(T value);
};

template <typename T> class DList {
private:
  int elements;
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
  DNode<T> *head;
  DNode<T> *tail;

public:
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
  std::string toStringForward();
  std::string toStringBackward();
};

/**
 * @section Method definitions
 */

template <class T> std::string DList<T>::toString() {
  std::stringstream aux;
  DNode<T> *p;

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

template <class T> std::string DList<T>::toStringForward() {
  std::stringstream aux;
  DNode<T> *p;

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

template <class T> std::string DList<T>::toStringBackward() {
  std::stringstream aux;
  DNode<T> *p;

  p = tail;
  aux << "[";
  while (p != 0) {
    aux << p->value;
    if (p->prev != 0) {
      aux << ", ";
    }
    p = p->prev;
  }
  aux << "]";
  return aux.str();
}

template <typename T> void DList<T>::insertHead(T value) {
  // Create a temp Node
  DNode<T> *node = new DNode<T>(value);

  // New node points at head
  node->next = head;
  // if head exists, update prev pointer
  if (head != nullptr)
    head->prev = node;
  // The new Node is the Head now
  head = node;

  // If the linked list is empty
  // The Tail is also the Head
  if (elements == 0)
    tail = head;

  // One element is added
  elements++;
}

template <typename T> void DList<T>::insertTail(T value) {
  // if empty, invoke insertHead()
  if (elements == 0) {
    insertHead(value);
    return;
  }

  // Create a new Node
  DNode<T> *node = new DNode<T>(value);
  // same as insertHead, this node becomes tail
  tail->next = node;
  // prev pointer of new node points to tail
  node->prev = tail;
  tail = node;
  elements++;
}

template <typename T> void DList<T>::insertion(unsigned int index, T value) {
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
  DNode<T> *prev = head;

  // Traverse elements until index
  for (int i = 0; i < index - 1; ++i) {
    prev = prev->next;
  }

  // Create the next node which is
  // the element after previous node
  DNode<T> *next = prev->next;

  // Create a new node
  DNode<T> *node = new DNode<T>(value);

  // Insert new node between
  // the previous node and the next node
  node->next = next;
  // update prev pointer as well
  node->prev = prev;
  prev->next = node;
  // update prev of next to node
  next->prev = node;

  // increase list size
  elements++;
}
// push_back method for LinkedList
template <typename T> void DList<T>::insertion(T value) {
  if (elements == 0) {
    insertHead(value);
    return;
  }
  insertTail(value);
  return;
}

template <typename T> int DList<T>::search(T element) {
  // empty list, lol
  if (elements == 0)
    return -1;

  // counter
  int index = 0;

  // Traverse from the Head node
  DNode<T> *node = head;

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

template <typename T> void DList<T>::update(unsigned int index, T value) {
  if (index > elements || index < 0) {
    throw;
  }
  DNode<T> *node = head;
  int count = 0;

  while (count < index && node->next != nullptr) {
    node = node->next;
    count++;
  }
  node->value = value;
  return;
}

// deletes the first element
template <typename T> T DList<T>::deleteHead() {
  // Do nothing if empty
  if (elements == 0)
    return -1;

  // Save head to node
  DNode<T> *node = head;

  // Point the Head Pointer
  // to the element next to the current Head
  head = head->next;
  T value_copy = head->value;

  // Now it's safe to remove
  // the first element
  delete node;

  // prev pointer of head now points to null
  if (head != nullptr)
    head->prev = nullptr;

  // One element is removed
  elements--;
  return value_copy;
}

template <typename T> T DList<T>::deleteTail() {
  // one element? remove head
  if (elements == 1) {
    return deleteHead();
  }

  // Start from tail
  DNode<T> *node = tail;

  // now that we are dlinked, we can just remove tail and update
  // store the info that gets deleted
  tail = tail->prev;
  tail->next = nullptr;

  T value_copy = tail->value;
  // Now it's safe to remove
  // the last element
  delete node;

  // One element is removed
  elements--;
  return value_copy;
}

template <typename T> T DList<T>::deleteAt(unsigned int index) {
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
  DNode<T> *prev = head;

  // Find the element before
  // disjointed from the first element (head)
  for (int i = 1; i < index; i++) {
    prev = prev->next;
  }

  // The removed element is after
  DNode<T> *node = prev->next;

  // next node to insert
  DNode<T> *next = node->next;

  // link prev to next
  prev->next = next;
  // update the second link
  next->prev = prev;

  T value_copy = node->value;
  // It's now safe to remove
  // the selected index element
  delete node;

  // One element is removed
  elements--;
  return value_copy;
}

#endif // DLIST_H
