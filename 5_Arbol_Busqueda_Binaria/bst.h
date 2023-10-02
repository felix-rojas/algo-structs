/*
 * bst.h
 *
 *  Created on: 30/10/2015
 *      Author: clase
 */

#ifndef BST_H_
#define BST_H_

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

template <class T> class BST;

template <class T> class TreeNode {
private:
  T value;
  TreeNode *left, *right;

  TreeNode<T> *succesor();

public:
  TreeNode(T);
  TreeNode(T, TreeNode<T> *, TreeNode<T> *);
  void add(T);
  bool find(T) const;
  int findLevel(T, int) const;
  int find_height();
  void remove(T);
  void removeChildren();
  void inorder(std::stringstream &) const;
  void preorder(std::stringstream &) const;
  void postorder(std::stringstream &) const;
  void weirdorder(std::stringstream &) const;

  friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri)
    : value(val), left(le), right(ri) {}

template <class T> void TreeNode<T>::add(T val) {
  if (val < value) {
    if (left != nullptr) {
      left->add(val);
    } else {
      left = new TreeNode<T>(val);
    }
  } else {
    if (right != nullptr) {
      right->add(val);
    } else {
      right = new TreeNode<T>(val);
    }
  }
}

template <class T> int TreeNode<T>::find_height() {

  // Base case: If empty (root is nullptr), the height 0.
  if (this == nullptr) {
    return 0;
  }
  // Recursive case: Height of the tree is 1 + maximum of the heights of left
  // and right subtrees.
  int leftHeight = left->find_height();
  int rightHeight = right->find_height();

  return 1 + std::max(leftHeight, rightHeight);
}
template <class T> bool TreeNode<T>::find(T val) const {
  if (val < value) {
    if (left != nullptr) {
      return left->find(val);
    } else
      return false;
  } else if (val > value) {
    if (right != nullptr) {
      return right->find(val);
    } else
      return false;
  }
  return true;
}

template <class T> int TreeNode<T>::findLevel(T val, int level) const {
  if (val < value) {
    if (left != nullptr) {
      left->findLevel(val, level + 1);
    } else
      return -1;
  } else if (val > value) {
    if (right != nullptr) {
      right->findLevel(val, level + 1);
    } else
      return -1;
  } else if (val == value) {
    return level;
  }
  return -1;
}

template <class T> TreeNode<T> *TreeNode<T>::succesor() {
  TreeNode<T> *le, *ri;

  le = left;
  ri = right;

  // check right if left is null
  // no parent
  if (left == nullptr) {
    // if there is a right subtree
    if (right != nullptr) {
      // stop and return ri
      right = nullptr;
    }
    return ri;
  }
  // if the left doesn't have a right subtree
  // no child
  if (left->right == nullptr) {
    // move to the left
    left = left->left;
    le->left = nullptr;
    return le;
  }

  TreeNode<T> *parent, *child;
  parent = left;
  child = left->right;
  while (child->right != nullptr) {
    parent = child;
    child = child->right;
  }
  parent->right = child->left;
  child->left = nullptr;
  return child;
}

template <class T> void TreeNode<T>::remove(T val) {
  TreeNode<T> *chosen_one, *old;
  // value is bigger
  if (value > val) {
    // there is a left subtree
    if (left != nullptr) {
      // value coincides
      if (left->value == val) {
        // save value
        old = left;
        // find succesor
        chosen_one = left->succesor();
        // thre is a succesor
        if (chosen_one != nullptr) {
          chosen_one->left = old->left;
          chosen_one->right = old->right;
        }
        left = chosen_one;
        delete old;
      } else {
        // continue searching
        left->remove(val);
      }
    }
    // value is smaller than  val
  } else if (value < val) {
    // there is a right subtree
    if (right != nullptr) {
      // value coincides in the right subtree
      if (right->value == val) {
        old = right;
        chosen_one = right->succesor();
        // there is a succesor, add its children
        if (chosen_one != nullptr) {
          chosen_one->left = old->left;
          chosen_one->right = old->right;
        }
        right = chosen_one;
        delete old;
      } else {
        // continue to search
        right->remove(val);
      }
    }
  }
}

template <class T> void TreeNode<T>::removeChildren() {
  if (left != nullptr) {
    left->removeChildren();
    delete left;
    left = nullptr;
  }
  if (right != nullptr) {
    right->removeChildren();
    delete right;
    right = nullptr;
  }
}

template <class T> void TreeNode<T>::inorder(std::stringstream &aux) const {
  if (left != nullptr) {
    left->inorder(aux);
  }
  if (aux.tellp() != 1) {
    aux << " ";
  }
  aux << value;
  if (right != nullptr) {
    right->inorder(aux);
  }
}

template <class T> void TreeNode<T>::preorder(std::stringstream &aux) const {
  aux << value;
  if (left != nullptr) {
    aux << " ";
    left->preorder(aux);
  }
  if (right != nullptr) {
    aux << " ";
    right->preorder(aux);
  }
}

template <class T> void TreeNode<T>::postorder(std::stringstream &aux) const {
  aux << value;
  if (left != nullptr) {
    aux << " ";
    left->preorder(aux);
  }
  if (right != nullptr) {
    aux << " ";
    right->postorder(aux);
  }
}

template <class T> void TreeNode<T>::weirdorder(std::stringstream &aux) const {
  aux << value;
  if (right != nullptr) {
    aux << " ";
    right->weirdorder(aux);
  }
  if (left != nullptr) {
    aux << " ";
    left->preorder(aux);
  }
}

template <class T> class BST {
private:
  TreeNode<T> *root;

public:
  int tree_height = 0;
  BST();
  ~BST();
  bool empty() const;
  void add(T);
  bool find(T) const;
  void remove(T);
  void removeAll();
  std::string inorder() const;
  std::string preorder() const;
  std::string postorder() const;
  std::string weirdorder() const;

  // !TODO
  std::string visit();
  int height();
  int whatlevelamI(T);
  std::string ancestors(int);
};

template <class T> BST<T>::BST() : root(nullptr), tree_height(1) {}

template <class T> BST<T>::~BST() { removeAll(); }

template <class T> bool BST<T>::empty() const { return (root == nullptr); }

template <class T> void BST<T>::add(T val) {
  // check if root is null
  if (root != nullptr) {
    // if value not at the root
    if (!root->find(val)) {
      root->add(val);
    }
  } else {
    // if root , add TreeNode to root
    root = new TreeNode<T>(val);
  }
}

template <class T> void BST<T>::remove(T val) {
  // there is a root
  if (root != nullptr) {
    // value is at the root
    if (val == root->value) {
      TreeNode<T> *chosen_one = root->succesor();
      if (chosen_one != nullptr) {
        chosen_one->left = root->left;
        chosen_one->right = root->right;
      }
      delete root;
      root = chosen_one;
    } else {
      // search for the value on each TreeNode
      root->remove(val);
    }
  }
}

template <class T> void BST<T>::removeAll() {
  // the root has children
  if (root != nullptr) {
    root->removeChildren();
  }
  // delete and initializr to nullptr
  delete root;
  root = nullptr;
}

template <class T> bool BST<T>::find(T val) const {
  if (val == root->value) {
    return true;
  } else {
    if (root->value > val) {
      return (root->left->find(val) && root->left != nullptr);
    }
    if (root->value < val) {
      return (root->right->find(val) && root->right != nullptr);
    }
  }
  return false;
}

template <class T> std::string BST<T>::inorder() const {
  std::stringstream aux;

  aux << "[";
  if (!empty()) {
    root->inorder(aux);
  }
  aux << "]";
  return aux.str();
}

template <class T> std::string BST<T>::preorder() const {
  std::stringstream aux;

  aux << "[";
  if (!empty()) {
    root->preorder(aux);
  }
  aux << "]";
  return aux.str();
}

// !TODO
template <class T> std::string BST<T>::weirdorder() const {
  std::stringstream aux;
  if (!empty()) {
    root->weirdorder(aux);
  }
  std::vector<std::string> tmp;
  std::string set;
  std::string invertedStr;
  while (aux >> set)
    tmp.push_back(set);
  std::reverse(tmp.begin(), tmp.end());
  for (const std::string &reversedSet : tmp) {
    invertedStr += reversedSet + " ";
  }
  invertedStr.pop_back();
  return "[" + invertedStr + "]";
}

template <class T> std::string BST<T>::postorder() const {
  std::stringstream aux;

  aux << "[";
  if (!empty()) {
    root->postorder(aux);
  }
  aux << "]";
  return aux.str();
}

// !TODO
template <class T> std::string BST<T>::visit() {
  std::string temp =
      preorder() + "\n" + inorder() + "\n" + weirdorder() + "\n" + postorder();
  return temp;
}
// !TODO
template <class T> int BST<T>::height() { return root->find_height(); }

// !TODO
template <class T> int BST<T>::whatlevelamI(T val) {
  return root->findLevel(val, 1);
}
// !TODO
template <class T> std::string BST<T>::ancestors(int val) { return "[]"; }
// !TODO}
#endif /* BST_H_ */
