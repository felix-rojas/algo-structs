/**
 * @file list.h
 * @date November 2, 2023
 *
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

template <class T> class List;

template <class T> class Link {
private:
  Link(T);
  Link(T, Link<T> *);
  Link(const Link<T> &);

  T value;
  Link<T> *next;

  friend class List<T>;
};

template <class T> Link<T>::Link(T val) {
  this->value = val;
  this->next = nullptr;
}

template <class T> Link<T>::Link(T val, Link *next_node) {
  this->value = val;
  this->next = next_node;
}

template <class T> Link<T>::Link(const Link<T> &source) {
  this->value = source.value;
  this->next = source.next;
}

template <class T> class List {
public:
  List();
  List(const List<T> &);
  ~List();
  /* Requested methods*/
  void insertion(T);
  void update(unsigned int, T);
  void deleteAt(unsigned int);
  T search(T) const;

  void removeFirst();
  int length() const;
  bool empty() const;
  void clear();
  std::string toString() const;
  void operator=(const List &);

  T remove(int);

private:
  Link<T> *head;
  size_t size;
};

template <class T> List<T>::List() : head(nullptr), size(0) {}

template <class T> List<T>::~List() { clear(); }

template <class T> bool List<T>::empty() const { return size == 0; }

template <class T> int List<T>::length() const { return size; }

template <class T> void List<T>::removeFirst() {
  if (head) {
    Link<T> *temp = head;
    head = head->next;
    delete temp;
    size--;
  }
}

template <class T> T List<T>::search(T looked_value) const {
  Link<T> *p;
  p = head;
  size_t count = 0;
  while (p != 0 && count < size) {
    if (p->value == looked_value)
      return count;
    p = p->next;
    count++;
  }
  return -1;
}

template <class T> void List<T>::update(unsigned int index, T newValue) {
  if (index >= size || size == 0) {
    throw; // Index out of bounds
  }

  Link<T> *current = head;
  size_t currentIndex = 0;

  while (current && currentIndex < index) {
    current = current->next;
    currentIndex++;
  }

  current->value = newValue;
}

template <class T> void List<T>::clear() {
  while (!empty()) {
    removeFirst();
  }
}

template <class T> std::string List<T>::toString() const {
  std::stringstream aux;
  Link<T> *p;

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

template <class T> List<T>::List(const List<T> &source) {
  Link<T> *current = source.head;
  while (current) {
    insertion(current->value);
    current = current->next;
  }
}

template <class T> void List<T>::insertion(const T insert_value) {
  Link<T> *new_node = new Link<T>(insert_value);
  if (!head) {
    head = new_node;
  } else {
    Link<T> *current = head;
    while (current->next) {
      current = current->next;
    }
    current->next = new_node;
  }
  size++;
}
template <class T> void List<T>::operator=(const List<T> &source) {
  Link<T> *current = source.head;
  while (current) {
    insertion(current->value);
    current = current->next;
  }
}

template <class T> void List<T>::deleteAt(unsigned int index) {
  if (index >= size || size == 0) {
    throw; // Index out of bounds
  }

  Link<T> *current = head;
  Link<T> *prev = nullptr;
  size_t currentIndex = 0;

  while (current && currentIndex < index) {
    prev = current;
    current = current->next;
    currentIndex++;
  }

  if (prev) {
    prev->next = current->next;
  } else {
    head = current->next;
  }

  delete current;
  size--;
}

#endif /* LINKEDLIST_H_ */
