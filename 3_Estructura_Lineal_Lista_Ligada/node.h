#ifndef NODE_H_
#define NODE_H_

template <typename T> class Node {
public:
  T value;
  Node *next;
  Node(T value) : value(value), next(nullptr) {}
};

#endif // NODE_H_
