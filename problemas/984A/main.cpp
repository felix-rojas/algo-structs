#include <iostream>
#include <vector>

std::vector<unsigned int> numbers;

int partition(std::vector<unsigned int> &arr, int start, int end) {
  int pivot = arr[start];
  int count = 0;
  for (int i = start + 1; i <= end; i++) {
    if (arr[i] <= pivot)
      count++;
  }
  int p = start + count;
  std::swap(arr[p], arr[start]);

  int start_idx = start, end_idx = end;
  while (start_idx < p && end_idx > p) {
    while (arr[start_idx] <= pivot)
      start_idx++;
    while (arr[end_idx] > pivot)
      end_idx--;

    if (start_idx < p && end_idx > p) {
      std::swap(arr[start_idx], arr[end_idx]);
      start_idx++;
      end_idx--;
    }
  }

  return p;
}

void qs(std::vector<unsigned int> &arr, int start, int end) {
  if (start >= end)
    return;
  int pivot = partition(arr, start, end);
  qs(arr, start, pivot - 1);
  qs(arr, pivot + 1, end);
}

int main() {
  int n, m;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> m;
    numbers.push_back(m);
  }

  qs(numbers,0,n-1);

  if (n % 2 != 0)
    std::cout << numbers[n / 2] << std::endl;
  else
    std::cout << numbers[(n / 2) - 1] << std::endl;
  return 0;
}