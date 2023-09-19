#ifndef NODE_H_
#define NODE_H_

template <typename T> class Node {
public:
  T Value;
  Node *Next;
  Node(T value) : Value(value), Next(nullptr) {}
};

#endif // NODE_H_
