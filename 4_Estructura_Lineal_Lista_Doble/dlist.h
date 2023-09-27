#ifndef DLIST_H
#define DLIST_H
#include <sstream>
#include <string>

template <typename T> class DList;
/**
 * @brief Auxiliary class for the class DList to hold data and links to
 * previous and the next pointer
 * @tparam T holds data for any value that can be used with templates
 */
template <typename T> class DNode {
private:
  T value;
  DNode<T> *prev;
  DNode<T> *next;
  DNode(T value);
  friend class DList<T>;
};
template <typename T>
DNode<T>::DNode(T value) : value(value), next(nullptr), prev(nullptr) {}

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
  /**
   * @brief helper function to copy from other DList
   *
   * @param other DList to copy
   */
  void copyFrom(const DList<T> &);
  /**
   * @brief helper function for moving DList
   *
   * @param other DList to move to
   */
  void moveFrom(DList<T> &&other);

public:
  /**
   * @brief Construct a new DList object
   *
   */
  DList();
  /**
   * @brief Copy Construct a new DList object
   *
   */
  DList(const DList<T> &other);
  /**
   * @brief Copy assginment operator
   *
   * @param other DList to copy
   * @return DList& pointr to the newly created DList
   */
  DList<T> &operator=(const DList<T> &other);
  /**
   * @brief Move constructor for DList<T> object
   * 
   * @param other DList
   */
  DList<T>(DList<T> &&other) noexcept { moveFrom(std::move(other)); }
/**
 * @brief Move operator overload for DList<T> object
 * 
 * @param other DList
 * @return DList<T>& pointer to the moved list
 */
  DList<T> &operator=(DList<T> &&other) noexcept {
    if (this != &other) {
      clear();
      moveFrom(std::move(other));
    }
    return *this;
  }
  /**
   * @brief Deletes the doubly linked list and frees the heap
   */
  ~DList();
  /**
   * @brief helper function to delete the DList and free memory
   *
   */
  void clear();
  /**
   * @brief Inserts a value at the end of the list, similar to push_back for
   * std::vector
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
   * @brief Delete a node from the list
   * @param index of the node to remove
   */
  void deleteAt(int index);
  /**
   * @brief Makes a string using sstream in the specified format of the Doubly
   * Linked List
   * @returns string of the linked list between brackets
   */
  std::string toString();
  std::string toStringForward();
  /**
   * @brief Makes a string using sstream in reverse of the Doubly Linked List
   * @returns string of the linked list with reversed output
   */
  std::string toStringBackward();
};

/**
 * @section Method definitions
 */

/**
 * @brief Default constructor with pre-initialization
 */
template <class T>
DList<T>::DList() : head(nullptr), tail(nullptr), elements(0) {}

template <class T> DList<T>::DList(const DList<T> &other) {
  DNode<T> *current = other->head;
  while (current != nullptr) {
    insertion(current->value);
    current = current->next;
  }
}

template <class T> DList<T> &DList<T>::operator=(const DList<T> &other) {
  if (this != &other) {
    clear();
    copyFrom(other);
  }
  return *this;
}

template <class T> void DList<T>::copyFrom(const DList<T> &other) {
  DNode<T> *current = other.head;
  while (current != nullptr) {
    insertion(current->value);
    current = current->next;
  }
}

template <class T> DList<T>::~DList() { clear(); }

template <class T> void DList<T>::clear() {
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

template <typename T> int DList<T>::search(T element) {
  // empty list, lol
  if (elements == 0)
    return -1;

  // counter
  int index = 0;

  // Traverse from the Head node
  DNode<T> *node = head;

  // Traverse until the selected value
  while (node->value != element) {
    index++;
    node = node->next;

    // selected value is not found
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
  return;
}

#endif // DLIST_H
