/*
 * hash.h
 *
 *  Created on: 20/10/2015
 *      Author: clase
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <iostream>
#include <sstream>
#include <string>

template <class Key, class Value> class Quadratic {
private:
  unsigned int (*func)(const Key);
  unsigned int size;
  unsigned int count;

  Key *keys;
  Key initialValue;
  Value *values;

  long indexOf(const Key) const;

public:
  Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
  ~Quadratic();
  bool full() const;
  bool put(Key, Value);
  bool contains(const Key) const;
  long search_key(const Key);
  Value get(const Key);
  void clear();
  std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init,
                                 unsigned int (*f)(const Key)) {
  size = sze;
  initialValue = init;
  func = f;
  keys = new Key[size];
  values = new Value[size];

  // pre-initialize to "empty" key value
  for (int i = 0; i < size; i++) {
    keys[i] = init;
  }
  count = 0;
}

template <class Key, class Value> Quadratic<Key, Value>::~Quadratic() {
  clear();
}

template <class Key, class Value> bool Quadratic<Key, Value>::full() const {
  return count == size;
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
  return func(k) % size;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
  // check if it isn't full
  if (!full()) {
    bool already_exists = contains(k);
    if (already_exists) {
      // update value
      values[indexOf(k)] = v;
    } else {
      if (keys[indexOf(k)] == initialValue) {
        keys[indexOf(k)] = k;
        values[indexOf(k)] = v;
        count++;
      } else {
        unsigned long i = 1;
        unsigned long new_index;
        while (keys[(func(k) + (i * i)) % size] != initialValue) {
          i++;
        }
        new_index = (func(k) + (i * i)) % size;
        keys[new_index] = k;
        values[new_index] = v;
        count++;
      }
    }
  } else {
    std::cerr << "Hash is full" << std::endl;
    return false;
  }
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
  for (unsigned long i = 0; i < size; i++) {
    if (keys[(func(k) + (i * i)) % size] == k)
      return true;
    if (keys[(func(k) + (i * i)) % size] == initialValue)
      return false;
  }
  return false;
}

template <class Key, class Value>
long Quadratic<Key, Value>::search_key(const Key k) {
  if (k == keys[indexOf(k)]) {
    return indexOf(k);
  } else {
    unsigned long i = 0;
    for (; i < size; i++) {
      if (keys[(func(k) + (i * i)) % size] == k)
        return (func(k) + (i * i)) % size;
      if (keys[(func(k) + (i * i)) % size] == initialValue)
        return -1;
    }
    return -1;
  }
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
  long index = search_key(k);
  if (index == -1) {
    std::cerr << "Key doesn't exist" << std::endl;
  } else {
    return values[index];
  }
}

template <class Key, class Value> void Quadratic<Key, Value>::clear() {
  delete[] keys;
  delete[] values;
  count = 0;
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
  std::stringstream aux;

  for (unsigned int i = 0; i < size; i++) {
    if (keys[i] != initialValue) {
      aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
    }
  }
  return aux.str();
}
#endif /* QUADRATIC_H_ */
