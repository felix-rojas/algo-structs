#include <cstddef>
#include <iostream>
#include <ostream>

typedef unsigned long long ull;
typedef unsigned int ui;

const ui MAX_ARRAY_SIZE = 100000;

class snowflake_node {
public:
  // ull snowflake[6];
  ui snowflake_arr[6];
  snowflake_node *next_similar;
  void print_snoflake() {
    std::cout << "[";
    for (ui i = 0; i < 6; i++) {
      std::cout << this->snowflake_arr[i] << " ";
    }
    std::cout << "]" << std::endl;
  }
};

bool read_right(const ui node1[], const ui node2[], ui start) {
  int offset = 0;
  for (; offset < 6; offset++) {
    if (node1[offset] != node2[(start + offset) % 6])
      return false;
  }
  return true;
}

bool read_left(const ui node1[], const ui node2[], ui start) {
  int offset = 0;
  for (; offset < 6; offset++) {
    int index = start - offset;
    // loop around
    if (index < 0)
      index += 6;
    if (node1[offset] != node2[index])
      return false;
  }
  return true;
}

bool is_twin( snowflake_node &this_node,  snowflake_node &other) {
  ui start = 0;
  for (; start < 6; start++) {
    if (read_left(this_node.snowflake_arr, other.snowflake_arr, start)) {
      return true;
    }
    if (read_right(this_node.snowflake_arr, other.snowflake_arr, start)) {
      return true;
    }
  }
  return false;
}

void solve(snowflake_node *array_of_snowflakes[]) {
  snowflake_node *ptr1, *ptr2;
  for (ui i = 0; i < MAX_ARRAY_SIZE; i++) {
    ptr1 = array_of_snowflakes[i];
    while (ptr1 != NULL) {
      ptr2 = ptr1->next_similar;
      while (ptr2 != NULL) {
        if (is_twin(*ptr1, *ptr2)) {
          std::cout << "Twin snowflakes found." << std::endl;
          return;
        }
        ptr2 = ptr2->next_similar;
      }
      ptr1 = ptr1->next_similar;
    }
  }
  std::cout << "No two snowflakes are alike." << std::endl;
}

int main() {
  static snowflake_node *snowflakes_collection[MAX_ARRAY_SIZE] = {NULL};
  snowflake_node *snow_ptr;
  ui input_size, snowflake_hash, count, snow_shape, accum;
  std::cin >> input_size;

  //std::cout << "Solving " << input_size << " entries" << std::endl;

  for (int i = 0; i < input_size; i++) {
    snow_ptr = new snowflake_node;
    //std::cout << "New snowflake created" << std::endl;
    count = 0;
    accum = 0;
    while (count < 6) {
      std::cin >> snow_shape;
      snow_ptr->snowflake_arr[count] = snow_shape;
      accum += snow_shape;
      count++;
    }
    // caclulate hash
    snowflake_hash = accum % MAX_ARRAY_SIZE;
    //snow_ptr->print_snoflake();
    // store
    snow_ptr->next_similar = snowflakes_collection[snowflake_hash];
    snowflakes_collection[snowflake_hash] = snow_ptr;
  }
  solve(snowflakes_collection);
}