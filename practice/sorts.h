/*
 * sorts.h
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>

template <class T> class Sorts {
private:
  void swap(std::vector<T> &, int, int);
  void copyArray(std::vector<T> &, int, int);
  void mergeArray(std::vector<T> &, int, int, int);
  void mergeSplit(std::vector<T> &, int, int);

public:
  std::vector<T> bubbleSort(const std::vector<T> &);
  std::vector<T> insertionSort(const std::vector<T> &);
  std::vector<T> shellSort(const std::vector<T> &);
  std::vector<T> mergeSort(const std::vector<T> &);
  std::vector<T> bucketSort(const std::vector<T> &);
  std::vector<T> selectionSort(const std::vector<T> &);
};

template <class T> void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
  T aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

template <class T> void Sorts<T>::copyArray(std::vector<T> &v, int i, int j) {
  // stub
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &v, int i, int j, int k) {
  // stub
}

template <class T> void Sorts<T>::mergeSplit(std::vector<T> &v, int i, int j) {
  // stub
}

template <class T>
std::vector<T> Sorts<T>::bubbleSort(const std::vector<T> &source) {
  std::vector<T> v(source);
  for (int i = v.size() - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      swap(v, j, j + 1);
    }
  }
}
template <class T>
std::vector<T> Sorts<T>::insertionSort(const std::vector<T> &source) {
  std::vector<T> v(source);
  int n = v.size();
  int count = 0;
  // compare the 2 first elements
  // swap them if the first one is larger
  // increase subarray size
  for (int i = 0; i < n - 1; i++) {
    T curr = v[i];
    T next = v[i + 1];
    if (curr > next) {
      swap(v, v[i], v[i + 1]);
    }
    count++;
    for (int j = count; j > 0; j--) {
      if (v[j] > v[j - 1]) {
        swap(v, v[j], v[j - 1]);
      }
    }
  }
  return v;
}

template <class T>
std::vector<T> Sorts<T>::mergeSort(const std::vector<T> &source) {}

template <class T>
std::vector<T> Sorts<T>::shellSort(const std::vector<T> &source) {}

template <class T>
std::vector<T> Sorts<T>::selectionSort(const std::vector<T> &source) {}

template <class T>
std::vector<T> Sorts<T>::bucketSort(const std::vector<T> &source) {}

#endif // SORTS_H_
