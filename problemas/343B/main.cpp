
#include <iostream>
#include <stack>
#include <string>

std::stack<std::pair<char, char>> dll;
std::string input;
bool check_collapsed(const std::stack<std::pair<char, char>> &dll) {
  if (dll.size() == 1 && dll.top().first == dll.top().second)
    return true;
  return false;
}

int main() {
  std::getline(std::cin, input);

  if (input.size() % 2 != 0) {
    std::cout << "No" << std::endl;
  } else {
    if (input.size() == 2) {
      if (input[0] != input[1])
        std::cout << "No" << std::endl;
      else
        std::cout << "Yes" << std::endl;
    } else {
      // copy string to stack
      dll.push(std::make_pair(input[0], input[1]));
      for (int i = 2; i < input.size() - 1; i += 2) {
        std::pair<char, char> check_pair =
            std::make_pair(input[i], input[i + 1]);
        // do not copy identical pair
        if (check_pair.first != check_pair.second) {
          // if last pair second item is equal to new pairs first item
          if (dll.top().second == check_pair.first) {
            // assign the second item of the pair
            dll.top().second = check_pair.second;
            // check if the top has identical items
            if (dll.top().first == dll.top().second) {
              // pop it if it isnt the last element
              if (dll.size() >= 2) {
                dll.pop();
              }
            }
            // new pair is different
          } else {
            dll.push(check_pair);
          }
        }
      }
      if (check_collapsed(dll))
        std::cout << "Yes" << std::endl;
      else
        std::cout << "No" << std::endl;
    }
  }
}