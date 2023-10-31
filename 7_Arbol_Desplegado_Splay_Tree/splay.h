/*
 * splay.h
 *
 *  Created on: 30/10/2015
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
    T key;
    Node *parent;
    Node *left;
    Node *right;

    Node(T key, Node *parent = nullptr)
        : key(key), parent(parent), left(nullptr), right(nullptr) {}
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

  Node *searchNode(T key) {
    if (root == nullptr) {
      return nullptr;
    }

    Node *current = root;
    while (current != nullptr) {
      if (key < current->key) {
        current = current->left;
      } else if (key > current->key) {
        current = current->right;
      } else {
        return current;
      }
    }

    return nullptr; // Key not found
  }

  Node *findMax(Node *node) {
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

public:
  SplayTree() : root(nullptr) {}

  // Insert a key into the splay tree
  void add(T key) {
    if (root == nullptr) {
      root = new Node(key);
      return;
    }

    Node *current = root;
    Node *parent = nullptr;

    while (current != nullptr) {
      parent = current;
      if (key < current->key) {
        current = current->left;
      } else if (key > current->key) {
        current = current->right;
      } else {
        return;
      }
    }

    Node *newNode = new Node(key, parent);

    if (key < parent->key) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    splay(newNode);
  }

  // Search for a key in the splay tree
  bool find(T key) {
    if (root == nullptr) {
      return false;
    }

    Node *current = root;
    while (current != nullptr) {
      if (key < current->key) {
        current = current->left;
      } else if (key > current->key) {
        current = current->right;
      } else {
        splay(current);
        return true;
      }
    }

    return false;
  }

  // Remove a key from the splay tree
  void remove(int key) {
    if (root == nullptr) {
      return;
    }

    Node *toRemove = searchNode(key);

    if (toRemove == nullptr) {
      return; // Key not found
    }

    splay(toRemove);

    if (toRemove->left == nullptr) {
      root = toRemove->right;
      if (toRemove->right != nullptr) {
        toRemove->right->parent = nullptr;
      }
    } else {
      Node *maxLeft = findMax(toRemove->left);
      maxLeft->right = toRemove->right;
      if (toRemove->right != nullptr) {
        toRemove->right->parent = maxLeft;
      }
      root = toRemove->left;
      toRemove->left->parent = nullptr;
    }

    delete toRemove;
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
      aux << node->key << " ";
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
      aux << node->key << " ";
      preorder(node->left, aux);
      preorder(node->right, aux);
    }
  }
};

#endif /* Splay_H_ */
