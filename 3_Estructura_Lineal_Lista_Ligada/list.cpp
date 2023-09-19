#include "list.h"
#include <sstream>
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
