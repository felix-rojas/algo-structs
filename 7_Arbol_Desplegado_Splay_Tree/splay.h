/*
 * splay.h
 *
 *      Author: clase
 */

#ifndef Splay_H_
#define Splay_H_
#include <iostream>
#include <sstream>
#include <string>

template <class T> class SplayTree {
private:
  struct Node {
    T value;
    Node *parent;
    Node *left;
    Node *right;

    Node(T value, Node *parent = nullptr)
        : value(value), parent(parent), left(nullptr), right(nullptr) {}
  };

  Node *root;

  void splay(Node *node) {
    while (node->parent != nullptr) {
      Node *parent = node->parent;
      Node *grandparent = parent->parent;

      if (grandparent == nullptr) {
        if (node == parent->left) {
          rotateRight(parent);
        } else {
          rotateLeft(parent);
        }
      } else {
        if (node == parent->left && parent == grandparent->left) {
          rotateRight(grandparent);
          rotateRight(parent);
        } else if (node == parent->right && parent == grandparent->right) {
          rotateLeft(grandparent);
          rotateLeft(parent);
        } else if (node == parent->left && parent == grandparent->right) {
          rotateRight(parent);
          rotateLeft(grandparent);
        } else {
          rotateLeft(parent);
          rotateRight(grandparent);
        }
      }
    }
    root = node;
  }

  // Perform a right rotation on the given node
  void rotateRight(Node *node) {
    Node *leftChild = node->left;
    if (leftChild != nullptr) {
      node->left = leftChild->right;
      if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
      }
      leftChild->parent = node->parent;
      if (node->parent == nullptr) {
        root = leftChild;
      } else if (node == node->parent->left) {
        node->parent->left = leftChild;
      } else {
        node->parent->right = leftChild;
      }
      leftChild->right = node;
      node->parent = leftChild;
    }
  }

  // Perform a left rotation on the given node
  void rotateLeft(Node *node) {
    Node *rightChild = node->right;
    if (rightChild != nullptr) {
      node->right = rightChild->left;
      if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
      }
      rightChild->parent = node->parent;
      if (node->parent == nullptr) {
        root = rightChild;
      } else if (node == node->parent->left) {
        node->parent->left = rightChild;
      } else {
        node->parent->right = rightChild;
      }
      rightChild->left = node;
      node->parent = rightChild;
    }
  }

  Node *searchNode(T value) {
    if (root == nullptr) {
      return nullptr;
    }
    Node *current = root;
    while (current != nullptr) {
      if (value < current->value) {
        current = current->left;
      } else if (value > current->value) {
        current = current->right;
      } else {
        return current;
      }
    }
    return nullptr; // value not found
  }

  Node *findMax(Node *node) {
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

  // Join two subtrees
  // maximum node of left subtree is less
  // than min node of right subtree
  Node *join(Node *leftSubtree, Node *rightSubtree) {
    if (leftSubtree == nullptr) {
      return rightSubtree;
    }
    if (rightSubtree == nullptr) {
      return leftSubtree;
    }

    Node *maxLeft = findMax(leftSubtree);
    splay(maxLeft);
    maxLeft->right = rightSubtree;
    rightSubtree->parent = maxLeft;

    return maxLeft;
  }

public:
  SplayTree() : root(nullptr) {}

  // debug function to print tree
  void print() { print(root, 0); }

  void print(Node *node, int indent) {
    if (node == nullptr) {
      return;
    }

    print(node->right, indent + 4);

    for (int i = 0; i < indent; i++) {
      std::cout << " ";
    }

    std::cout << node->value << std::endl;

    print(node->left, indent + 4);
  }

  // Insert a value into the splay tree
  void add(T value) {
    if (root == nullptr) {
      root = new Node(value);
      return;
    }

    Node *current = root;
    Node *parent = nullptr;

    while (current != nullptr) {
      parent = current;
      if (value < current->value) {
        current = current->left;
      } else if (value > current->value) {
        current = current->right;
      } else {
        return;
      }
    }

    Node *newNode = new Node(value, parent);

    if (value < parent->value) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    splay(newNode);
  }

  // Search for a value in the splay tree
  bool find(T value) {
    if (root == nullptr) {
      return false;
    }

    Node *current = root;
    while (current != nullptr) {
      if (value < current->value) {
        current = current->left;
      } else if (value > current->value) {
        current = current->right;
      } else {
        // value found, splay tree
        splay(current);
        return true;
      }
    }
    return false;
  }

  // Remove a value from the splay tree
  void remove(T value) {
    // cant splay an empty tree
    if (root == nullptr) {
      return;
    }

    Node *toRemove = searchNode(value);

    if (toRemove == nullptr) {
      return; // value not found
    }

    // splay tree, toRemove is the new root
    splay(toRemove);

    // remove the root
    Node *leftSubtree = root->left;
    Node *rightSubtree = root->right;
    delete root;

    // left and right subtrees as new root
    if (leftSubtree != nullptr) {
      leftSubtree->parent = nullptr;
    }
    if (rightSubtree != nullptr) {
      rightSubtree->parent = nullptr;
    }

    root = join(leftSubtree, rightSubtree);
  }

  std::string inorder() {
    std::stringstream aux;
    inorder(root, aux);
    std::string res = aux.str();
    res.pop_back();
    return "[" + res + "]";
  }

  void inorder(Node *node, std::stringstream &aux) {
    if (node != nullptr) {
      inorder(node->left, aux);
      aux << node->value << " ";
      inorder(node->right, aux);
    }
  }

  std::string preorder() {
    std::stringstream aux;
    preorder(root, aux);
    std::string res = aux.str();
    res.pop_back();
    return "[" + res + "]";
  }

  void preorder(Node *node, std::stringstream &aux) {
    if (node != nullptr) {
      aux << node->value << " ";
      preorder(node->left, aux);
      preorder(node->right, aux);
    }
  }
};

#endif /* Splay_H_ */
