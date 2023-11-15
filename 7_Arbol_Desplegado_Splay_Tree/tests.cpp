/*
 * tests.cpp
 *
 *  Created on: 9/11/2023
 *      Author: felix-rojas
 */

#include "splay.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  string in_ans = "", pre_ans = "";

  int test_times = 1;
  bool found = 0;
  cout << ("------------------------") << endl;
  cout << ("--- Empty tree tests ---") << endl;
  cout << ("------------------------") << endl;
  // empty tree tests removal
  for (int i = 0; i < test_times; i++) {
    SplayTree<int> my_splay_test;

    cout << ("Testing for non existing value removal: ") << endl;
    cout << ("Removed value ") << i << endl;
    my_splay_test.remove(i);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");
    cout << ("Testing for non existing value removal: ") << endl;
    cout << ("Removed value ") << i << endl;
    my_splay_test.remove(i);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing for empty tree non existing value search: ") << endl;
    cout << ("Value to find ") << i << endl;
    my_splay_test.find(i + 1);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");
    cout << ("Testing for empty tree non existing value search: ") << endl;
    cout << ("Value to find ") << i << endl;
    my_splay_test.find(i + 1);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");
  }

  cout << endl;

  for (int i = 0; i < test_times; i++) {
    SplayTree<int> my_splay_test;
    int test_value = 15;
    cout << ("-----------------------------") << endl;
    cout << ("--- Single node tree test ---") << endl;
    cout << ("-----------------------------") << endl;
    cout << ("Adding a single node with value: ") << test_value << endl;
    my_splay_test.add(test_value);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing for non existing value: ") << 139 << endl;
    found = my_splay_test.find(139);
    cout << (!found ? "success\n" : "fail\n");
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing for single existing value: ") << test_value << endl;
    found = my_splay_test.find(test_value);
    cout << (found ? "success\n" : "fail\n");
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing for single existing value removal: ") << endl;
    my_splay_test.remove(test_value);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing find for value removal: ") << endl;
    found = my_splay_test.find(test_value);
    cout << (!found ? "success\n" : "fail\n");
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing find for deleted value: ") << test_value << endl;
    found = my_splay_test.find(test_value);
    cout << (!found ? "success\n" : "fail\n");
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Testing find for non-existent value: ") << 12983 << endl;
    found = my_splay_test.find(12983);
    cout << (!found ? "success\n" : "fail\n");
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Re-Adding a single node with value: ") << test_value << endl;
    my_splay_test.add(test_value);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");

    cout << ("Re-Finding a single node with value: ") << test_value << endl;
    found = my_splay_test.find(test_value);
    cout << (found ? "success\n" : "fail\n");
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("Testing value removal: ") << endl;
    my_splay_test.remove(test_value);
    cout << ("Tree status: \n");
    my_splay_test.print();
    cout << ("------------ \n");
  }

  for (int i = 0; i < test_times; i++) {
    SplayTree<int> my_splay_insertions;
    cout << ("-------------------------------") << endl;
    cout << ("--- Insertions test on tree ---") << endl;
    cout << ("-------------------------------") << endl;

    int test_array[] = {10, 17, 7, 13, 16};
    cout << "Testing array: " << endl;
    cout << "[ ";
    for (int i = 0; i < 5; i++) {
      cout << test_array[i] << " ";
    }
    cout << "]" << endl;

    for (int i = 0; i < 5; i++) {
      my_splay_insertions.add(test_array[i]);
      cout << "Insertion of: [ " << test_array[i] << " ] Tree status " << endl;
      my_splay_insertions.print();
      cout << ("------------ \n");
    }
    cout << endl;

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Deletions test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    cout << ("Status before deletion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");

    for (int i = 0; i < 5; i++) {
      my_splay_insertions.remove(test_array[i]);
      cout << "Deletion of: [ " << test_array[i] << " ] Tree status " << endl;
      my_splay_insertions.print();
      cout << ("------------ \n");
    }
    cout << ("Status after deletion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");

    cout << endl;

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Insertion - deletion test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    for (int i = 0; i < 5; i++) {
      cout << "Insertion of: [ " << test_array[i] << " ] Tree status " << endl;
      my_splay_insertions.add(test_array[i]);
      my_splay_insertions.print();
      cout << ("------------ \n");

      cout << "Deletion of: [ " << test_array[i] << " ] Tree status " << endl;
      my_splay_insertions.remove(test_array[i]);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("Status after insertion - deletion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Sequential insertion test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Insertion of: [ " << i << " ] Tree status " << endl;
      my_splay_insertions.add(i);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("Status after sequential insertion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Sequential deletion test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Deletion of: [ " << i << " ] Tree status " << endl;
      my_splay_insertions.remove(i);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("Status after sequential deletion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("------------------------------------------------") << endl;
    cout << ("--- Sequential insertion - find test on tree ---") << endl;
    cout << ("------------------------------------------------") << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Insertion of: [ " << i << " ] Tree status " << endl;
      my_splay_insertions.add(i);
      cout << ("------------ \n");
    }

    cout << ("Status before sequential insertion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");
    cout << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Find: [ " << i << " ] Tree status " << endl;
      my_splay_insertions.find(i);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    for (int i = 9; i >= 0; i--) {
      cout << "Deletion of: [ " << i << " ] Tree status " << endl;
      my_splay_insertions.remove(i);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("Status after sequential inverse deletion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Repeated insertion test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Insertion of: [ " << 1 << " ] Tree status " << endl;
      my_splay_insertions.add(1);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("Status after repeated insertion: ") << endl;
    my_splay_insertions.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Repeated find test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Insertion of: [ " << 1 << " ] Tree status " << endl;
      my_splay_insertions.find(1);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Sequential deletion test on tree ---") << endl;
    cout << ("-----------------------------------------") << endl;

    for (int i = 0; i < 10; i++) {
      cout << "Deletion of: [ " << 1 << " ] Tree status " << endl;
      my_splay_insertions.remove(1);
      my_splay_insertions.print();
      cout << ("------------ \n");
    }

    cout << ("-----------------------------------------") << endl;
    cout << ("--- Class test ---") << endl;
    cout << ("-----------------------------------------") << endl;

    SplayTree<int> class_splay;
    bool class_found;
    class_splay.add(15);

    cout << ("Status after single add: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;

    class_splay.add(10);
    class_splay.add(17);
    class_splay.add(7);
    class_splay.add(13);
    class_splay.add(16);

    cout << ("Status after list add: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;

    class_found = class_splay.find(15);
    class_found ? cout << "Found value 15" << endl
                : cout << "Value 15 NOT found" << endl;
    cout << ("Status after find 15: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;

    class_found = class_splay.find(17);
    class_found ? cout << "Found value 17" << endl
                : cout << "Value 17 NOT found" << endl;
    cout << ("Status after find 17: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;

    cout << ("Status before remove 13: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;

    class_splay.remove(13);
    cout << ("Status after remove 13: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;

    class_splay.remove(16);
    cout << ("Status after remove 16: ") << endl;
    class_splay.print();
    cout << ("------------ \n");
    cout << endl;
  }
}
