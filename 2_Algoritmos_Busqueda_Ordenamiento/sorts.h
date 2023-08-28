/*
 * sorts.h
 *
 *  Created on: 09/08/2023
 *      Author: felix-rojas
 */

#ifndef SORTS_H_
#define SORTS_H_
#include <iostream>
#include <vector>

template <typename T> class Sorts {
private:
  void merge(T values[], int leftFirst, int leftLast, int rightFirst,
             int rightLast) {
    T tempArray[100];
    int index = leftFirst;
    int saveFirst = leftFirst;
    while ((leftFirst <= leftLast) && (rightFirst <= rightLast)) {
      if (values[leftFirst] < values[rightFirst]) {
        tempArray[index] = values[leftFirst];
        leftFirst++;
      } else {
        tempArray[index] = values[rightFirst];
        rightFirst++;
      }
      index++;
    }
    while (leftFirst <= leftLast) {
      tempArray[index] = values[leftFirst];
      leftFirst++;
      index++;
    }
    while (rightFirst <= rightLast) {
      tempArray[index] = values[rightFirst];
      rightFirst++;
      index++;
    }
    for (index = saveFirst; index <= rightLast; index++)
      values[index] = tempArray[index];
  }

  void mergeSort(T values[], int first, int last) {
    if (first < last) {
      int middle = (first + last) / 2;
      mergeSort(values, first, middle);
      mergeSort(values, middle + 1, last);
      merge(values, first, middle, middle + 1, last);
    }
  }

public:
  void ordenaSeleccion(std::vector<T> &vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
      // search for the smallest element "min"
      int min = i;
      // iterate only the places we haven't visited
      // index "i" are all the already sorted minimum elements
      for (int j = i + 1; j < vec.size(); j++) {
        if (vec.at(j) < vec.at(min))
          min = j;
      }
      // swap the next smallest element next to the smaller prev element
      std::swap(vec.at(i), vec.at(min));
    }
  }

  void ordenaBurbuja(std::vector<T> &vec) {
    // iterate through the entire vector
    for (int j = 0; j < vec.size(); j++) {
      // iterate each element
      for (int i = 0; i < vec.size() - (j + 1); i++) {
        if (vec.at(i) > vec.at(i + 1)) {
          // swap for the bigger number
          std::swap(vec.at(i), vec.at(i + 1));
        }
      }
    }
  }

  void ordenaMerge(std::vector<int> &vec) {
    const int last = vec.size() - 1;
    int arr[100]; // arbitrary array size
    // copy to arr
    for (int i = 0; i <= last; i++) {
      arr[i] = vec.at(i);
    }
    mergeSort(arr, 0, last);
    for (int i = 0; i <= last; i++) {
      vec.at(i) = arr[i];
    }
  }

  // for every item in the vec, look until you find the item
  int busqSecuencial(const std::vector<int> &vec, int item) {
    for (size_t i = 0; i < vec.size(); i++) {
      if (item == vec.at(i))
        return i;
    }
    return -1;
  }

  /* Adapted from Walter Savitch's absolute cpp pg 601-602*/
  int busqBinaria(const std::vector<int> &vec, int item) {
    int first = 0;
    int last = vec.size();
    int mid;

    while ((first <= last)) {
      // find the middle point
      mid = (first + last) / 2;
      // stop condition
      if (item == vec.at(mid))
        return mid;
      // reallocate middle point to the number that is closer
      else if (item < vec.at(mid)) {
        last = mid - 1;
      } else if (item > vec.at(mid)) {
        first = mid + 1;
      }
    }
    // else not found
    return -1;
  }
};

#endif /* SORTS_H_ */
