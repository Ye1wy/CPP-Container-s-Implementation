#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <unordered_set>

// #include "array/s21_array.h"
// #include "list/s21_list.h"
#include "map/s21_map.h"
// #include "multiset/s21_multiset.h"
// #include "queue/s21_queue.h"
// #include "set/s21_set.h"
// #include "stack/s21_stack.h"
// #include "vector/s21_vector.h"

using std::cout;
using std::endl;

int main() {
  s21::map<int, int> glober{{1, 1},  {2, 3},    {-4, 5},
                            {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<int, int> glober_1{{1, 1},  {2, 3},    {-4, 5},
                              {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<int, int> glober_2{{1, 1},  {2, 3},    {-4, 5},
                              {-7, 9}, {100, 32}, {-500, 100}};
  s21::map<s21::map<int, int>, std::string> aboba{
      {glober, "aboba"}, {glober_1, "joka"}, {glober_2, "goga"}};

  auto it = aboba.begin();
  cout << it->second << endl;
  ++it;
  cout << it->second << endl;
  ++it;
  cout << it->second << endl;
}