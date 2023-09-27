#ifndef DLIST_H
#define DLIST_H
#include <sstream>
#include <string>

template <typename T> class DNode {
public:
  T value;
  DNode<T> *prev;
  DNode<T> *next;
  DNode(T value) : value(value), next(nullptr), prev(nullptr) {}
};

template <typename T> class DList {
private:
  int elements;
  DNode<T> *head;
  DNode<T> *tail;
  /**
   * @brief Auxiliary method that deletes the first value of the list
   * @return value of the deleted node
   * @see deleteAt(unsigned int index)
   */
  void deleteHead();
  /**
   * @brief Auxiliary method that deletes the last value of the list
   * @return value of the deleted node
   * @see deleteAt(unsigned int index)
   */
  void deleteTail();

public:
  DList();
  DList(const DList<T> &);
  ~DList();
  /**
   * @brief Inserts a value at the end of the list, similar to append or
   * push_back
   * @param value is any value to be inserted
   * @return void
   */
  void insertion(T value);
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
  void update(int index, T value);
  /**
   * @brief Delete a node from the list and return its value
   * @param index of the node to remove
   * @return value of the deleted node
   */
  void deleteAt(int index);
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
template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr), elements(0) {}

template <class T> DList<T>::~DList() {
  DNode<T> *p, *q;

  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  elements = 0;
}

template <class T> std::string DList<T>::toString() {
  return toStringForward();
}

template <class T> std::string DList<T>::toStringForward() {
  std::stringstream aux;
  DNode<T> *p;

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

template <class T> std::string DList<T>::toStringBackward() {
  std::stringstream aux;
  DNode<T> *p;

  p = tail;
  aux << "[";
  while (p != nullptr) {
    aux << p->value;
    if (p->prev != nullptr)
      aux << ", ";
    p = p->prev;
  }
  aux << "]";
  return aux.str();
}

template <typename T> void DList<T>::insertion(T value) {
  DNode<T> *newNode = new DNode<T>(value);
  if (!head) {
    head = newNode;
    tail = newNode;
    elements++;
  } else {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    elements++;
  }
}
// push_back method for LinkedList

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

template <typename T> void DList<T>::update(int index, T value) {
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
template <typename T> void DList<T>::deleteHead() {
  // Do nothing if empty
  if (elements == 0)
    throw;

  // Save head to node
  DNode<T> *node = head;

  // Point the Head Pointer
  // to the element next to the current Head
  head = head->next;

  // Now it's safe to remove
  // the first element
  delete node;

  // prev pointer of head now points to null
  if (head != nullptr)
    head->prev = nullptr;

  // One element is removed
  elements--;
  return;
}

template <typename T> void DList<T>::deleteTail() {
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

  // Now it's safe to remove
  // the last element
  delete node;

  // One element is removed
  elements--;
  return;
}

template <typename T> void DList<T>::deleteAt(int index) {
  // cant delete with no elements
  if (elements == 0)
    throw;

  // index is out of bound
  if (index < 0 || index >= elements)
    throw;

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

  // It's now safe to remove
  // the selected index element
  delete node;

  // One element is removed
  elements--;
  return ;
}

#endif // DLIST_H
