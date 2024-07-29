#include <gtest/gtest.h>

#include <iterator>
#include <list>
#include <string>

#include "../s21_containers.h"

using std::string;

TEST(test_list, defualt_constructor) {
  s21::list<int> opa;

  EXPECT_EQ(opa.size(), 0);
  EXPECT_TRUE(opa.empty());
}

TEST(test_list, param_constructor_1) {
  s21::list<int> opa(5);

  for (s21::list<int>::ListIterator it = opa.begin(); it != opa.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(test_list, param_constructor_2) {
  s21::list<int> opa(0);

  for (s21::list<int>::ListIterator it = opa.begin(); it != opa.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(test_list, param_constructor_3) {
  s21::list<int> opa(999);

  for (s21::list<int>::ListIterator it = opa.begin(); it != opa.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(test_list, param_constructor_4) {
  s21::list<char> opa(999);

  for (s21::list<char>::ListIterator it = opa.begin(); it != opa.end(); ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(test_list, param_constructor_5) {
  s21::list<double> opa(999);

  for (s21::list<double>::ListIterator it = opa.begin(); it != opa.end();
       ++it) {
    EXPECT_EQ(*it, 0);
  }
}

TEST(test_list, param_constructor_6) {
  s21::list<std::string> opa(5);

  for (s21::list<std::string>::ListIterator it = opa.begin(); it != opa.end();
       ++it) {
    EXPECT_EQ(*it, "");
  }
}

TEST(test_list, copy_constructor_1) {
  s21::list<int> opa;
  s21::list<int> opa2(opa);

  EXPECT_EQ(opa.size(), 0);
  EXPECT_EQ(opa2.size(), 0);
  EXPECT_EQ(opa.size(), opa2.size());
}

TEST(test_list, copy_constructor_2) {
  s21::list<int> opa({1, 2, 3});
  s21::list<int> opa2(opa);

  EXPECT_EQ(opa.size(), opa2.size());
  s21::list<int>::iterator it = opa.begin();
  s21::list<int>::iterator it2 = opa2.begin();

  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, copy_constructor_3) {
  s21::list<std::string> opa({"aboba", "boba", "kola", "wubaluba"});
  s21::list<std::string> opa2(opa);

  EXPECT_EQ(opa.size(), opa2.size());
  s21::list<std::string>::iterator it = opa.begin();
  s21::list<std::string>::iterator it2 = opa2.begin();

  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, move_constructor_1) {
  s21::list<int> opa({1, 2, 3, 4});
  s21::list<int> opa2(std::move(opa));
  s21::list<int>::iterator it = opa.begin();

  std::list<int> aboba({1, 2, 3, 4});
  std::list<int>::iterator it2 = aboba.begin();

  bool eq = opa.begin() == opa.end();

  EXPECT_EQ(opa.size(), 0);
  EXPECT_EQ(eq, 1);
  EXPECT_EQ(*it, 0);

  for (it = opa2.begin(); it != opa2.end() && it2 != aboba.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, move_constructor_2) {
  s21::list<int> opa;
  s21::list<int> opa2(std::move(opa));
  s21::list<int>::ListIterator it = opa.begin();
  s21::list<int>::ListIterator it2 = opa2.begin();

  EXPECT_EQ(opa.size(), 0);
  EXPECT_EQ(opa.empty(), 1);
  EXPECT_EQ(opa2.size(), 0);
  EXPECT_EQ(opa2.empty(), 1);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*it2, 0);
}

TEST(test_list, move_constructor_3) {
  s21::list<int> opa;
  s21::list<int> opa2(std::move(opa));
  s21::list<int>::ListIterator it = opa.begin();
  s21::list<int>::ListIterator it2 = opa2.begin();

  EXPECT_EQ(opa.size(), 0);
  EXPECT_EQ(opa.empty(), 1);
  EXPECT_EQ(opa2.size(), 0);
  EXPECT_EQ(opa2.empty(), 1);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(*it2, 0);
}

TEST(test_list, move_constructor_4) {
  s21::list<string> opa;
  s21::list<string> opa2(std::move(opa));
  s21::list<string>::ListIterator it = opa.begin();
  s21::list<string>::ListIterator it2 = opa2.begin();

  EXPECT_EQ(opa.size(), 0);
  EXPECT_EQ(opa.empty(), 1);
  EXPECT_EQ(opa2.size(), 0);
  EXPECT_EQ(opa2.empty(), 1);
  EXPECT_EQ(*it, "");
  EXPECT_EQ(*it2, "");
}

TEST(test_list, operator_assign_1) {
  s21::list<int> opa({1, 2, 3});
  s21::list<int> opa2({1, 1, 1});

  const int size = opa.size();
  int arr[3] = {1, 1, 1};

  opa = opa2;
  s21::list<int>::ListIterator it = opa.begin();
  s21::list<int>::ListIterator it2 = opa2.begin();

  for (int i = 0; i < size && it != opa.end(); ++it, ++it2, ++i) {
    EXPECT_EQ(*it, arr[i]);
    EXPECT_EQ(*it2, arr[i]);
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, operator_assign_2) {
  s21::list<char> opa({'a', 'b', 'c'});
  s21::list<char> opa2({'g', 'o', 'd'});

  const int size = opa.size();
  char arr[3] = {'g', 'o', 'd'};

  opa = opa2;
  s21::list<char>::ListIterator it = opa.begin();
  s21::list<char>::ListIterator it2 = opa2.begin();

  for (int i = 0; i < size && it != opa.end(); ++it, ++it2, ++i) {
    EXPECT_EQ(*it, arr[i]);
    EXPECT_EQ(*it2, arr[i]);
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, operator_assign_3) {
  s21::list<int> opa;
  s21::list<int> opa2({1, 2, 3});

  opa2 = opa;

  EXPECT_EQ(opa.size(), 0);
  EXPECT_EQ(opa2.size(), 0);

  bool check_mem = opa.empty();
  bool check_mem2 = opa2.empty();

  EXPECT_EQ(check_mem, 1);
  EXPECT_EQ(check_mem2, 1);
}

TEST(test_list, operator_assign_4) {
  s21::list<int> opa({1, 2, 3});
  s21::list<int> opa2({8, 8, 8, 8});
  std::list<int> check({8, 8, 8, 8});

  opa = std::move(opa2);

  s21::list<int>::iterator it = opa.begin();
  std::list<int>::iterator oit = check.begin();

  for (; it != opa.end() && oit != check.end(); ++it, ++oit) {
    EXPECT_EQ(*it, *oit);
  }

  EXPECT_TRUE(opa2.empty());
}

TEST(test_list, operator_assign_5) {
  s21::list<string> opa({"Aboba", "woba"});
  s21::list<string> opa2({"wuba", "luba"});
  std::list<string> check({"wuba", "luba"});

  opa = std::move(opa2);

  s21::list<string>::ListIterator it = opa.begin();
  std::list<string>::iterator oit = check.begin();

  for (; it != opa.end() && oit != check.end(); ++it, ++oit) {
    EXPECT_EQ(*it, *oit);
  }

  bool isEmpty = opa2.empty();
  EXPECT_TRUE(isEmpty);
}

TEST(test_list, front_1) {
  s21::list<int> opa({1, 2, 3, 4});
  EXPECT_EQ(opa.front(), 1);
}

TEST(test_list, front_2) {
  s21::list<double> opa({1.5, 2, 3, 4});
  EXPECT_DOUBLE_EQ(opa.front(), 1.5);
}

TEST(test_list, front_3) {
  s21::list<char> opa({'a', 'b', 'c', 'd'});
  EXPECT_EQ(opa.front(), 'a');
}

TEST(test_list, back_1) {
  s21::list<int> opa({1, 2, 3, 4});
  EXPECT_EQ(opa.back(), 4);
}

TEST(test_list, back_2) {
  s21::list<double> opa({1, 2, 3, 4.413});
  EXPECT_EQ(opa.back(), 4.413);
}

TEST(test_list, back_3) {
  s21::list<double> opa({4.413});
  EXPECT_EQ(opa.back(), 4.413);
}

TEST(test_list, back_4) {
  s21::list<char> opa(5);
  EXPECT_EQ(opa.back(), 0);
}

TEST(test_list, empty_1) {
  s21::list<int> opa(5);
  EXPECT_FALSE(opa.empty());
}

TEST(test_list, empty_2) {
  s21::list<int> opa;
  EXPECT_TRUE(opa.empty());
}

TEST(test_list, size_1) {
  s21::list<int> opa;
  EXPECT_EQ(opa.size(), 0);
}

TEST(test_list, size_2) {
  s21::list<int> opa(5);
  EXPECT_EQ(opa.size(), 5);
}

TEST(test_list, max_size) {
  s21::list<int> opa(5);
  std::list<int> opa2(5);

  EXPECT_EQ(opa.max_size(), opa2.max_size());
}

TEST(test_list, begin_1) {
  s21::list<int> opa({1, 2, 3, 4});
  std::list<int> opa2({1, 2, 3, 4});

  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();

  EXPECT_EQ(*it, *it2);
}

TEST(test_list, begin_2) {
  s21::list<int> opa;
  std::list<int> opa2;

  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();

  EXPECT_EQ(*it, *it2);
}

TEST(test_list, end_1) {
  s21::list<int> opa({1, 2, 3, 4});
  std::list<int> aboba({1, 2, 3, 4});

  s21::list<int>::ListIterator it = opa.end();
  std::list<int>::iterator it2 = aboba.end();

  EXPECT_EQ(*(--it), *(--it2));
}

TEST(test_list, end_2) {
  s21::list<int> opa;

  bool eq = opa.end() == opa.begin();

  EXPECT_TRUE(eq);
}

TEST(test_list, cbegin_1) {
  s21::list<int> opa({1, 2, 3, 4});
  std::list<int> opa2({1, 2, 3, 4});

  s21::list<int>::ListConstIterator it = opa.cbegin();
  std::list<int>::const_iterator it2 = opa2.cbegin();

  EXPECT_EQ(*it, *it2);
}

TEST(test_list, cbegin_2) {
  s21::list<int> opa;
  std::list<int> opa2;

  s21::list<int>::ListConstIterator it = opa.cbegin();
  std::list<int>::const_iterator it2 = opa2.cbegin();

  EXPECT_EQ(*it, *it2);
}

TEST(test_list, cend_1) {
  s21::list<int> opa({1, 2, 3, 4});
  std::list<int> aboba({1, 2, 3, 4});

  s21::list<int>::ListConstIterator it = opa.cend();
  std::list<int>::const_iterator it2 = aboba.cend();

  EXPECT_EQ(*(--it), *(--it2));
}

TEST(test_list, cend_2) {
  s21::list<int> opa;

  bool eq = opa.cend() == opa.cbegin();

  EXPECT_TRUE(eq);
}

TEST(test_list, clear_1) {
  s21::list<int> opa({1, 2, 3, 4});
  opa.clear();
  std::list<int> opa2({1, 2, 3, 4});
  opa2.clear();

  EXPECT_TRUE(opa.empty() == opa2.empty());
  EXPECT_EQ(opa.size(), opa2.size());
}

TEST(test_list, clear_2) {
  s21::list<int> opa;
  opa.clear();

  std::list<int> opa2;
  opa2.clear();

  EXPECT_TRUE(opa.empty() == opa2.empty());
  EXPECT_EQ(opa.size(), opa2.size());
}

TEST(test_list, insert_1) {
  s21::list<int> opa({1, 2, 3, 4});
  std::list<int> opa2({1, 2, 3, 4});

  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();

  ++it;
  ++it2;

  const int wuba = 5;

  opa.insert(it, wuba);
  opa2.insert(it2, wuba);

  for (it = opa.begin(), it2 = opa2.begin();
       it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, insert_2) {
  s21::list<int> opa;
  s21::list<int>::ListIterator it = opa.begin();

  std::list<int> opa2;
  std::list<int>::iterator it2 = opa2.begin();

  const int wuba = 5;

  opa.insert(it, wuba);
  opa2.insert(it2, wuba);

  EXPECT_EQ(opa.front(), opa2.front());
}

TEST(test_list, insert_3) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int>::ListIterator it = opa.begin();

  std::list<int> opa2({1, 2, 3, 4, 5});
  std::list<int>::iterator it2 = opa2.begin();

  const int wuba = 5;

  opa.insert(it, wuba);
  opa2.insert(it2, wuba);

  EXPECT_EQ(opa.front(), opa2.front());
}

TEST(test_list, insert_4) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int>::ListIterator it = opa.end();

  std::list<int> opa2({1, 2, 3, 4, 5});
  std::list<int>::iterator it2 = opa2.end();

  const int wuba = 5;

  opa.insert(it, wuba);
  opa2.insert(it2, wuba);

  EXPECT_EQ(opa.back(), opa2.back());
}

TEST(test_list, erase_1) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int>::ListIterator it = opa.begin();

  std::list<int> opa2({1, 2, 3, 4, 5});
  std::list<int>::iterator it2 = opa2.begin();

  opa.erase(it);
  opa2.erase(it2);

  for (it = opa.begin(), it2 = opa2.begin();
       it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_EQ(opa.size(), opa2.size());
}

TEST(test_list, erase_2) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int>::ListIterator it = opa.end();

  std::list<int> opa2({1, 2, 3, 4, 5});
  std::list<int>::iterator it2 = opa2.end();

  opa.erase(--it);
  opa2.erase(--it2);

  for (it = opa.begin(), it2 = opa2.begin();
       it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_EQ(opa.size(), opa2.size());
}

TEST(test_list, erase_3) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int>::ListIterator it = opa.end();

  std::list<int> opa2({1, 2, 3, 4, 5});
  std::list<int>::iterator it2 = opa2.end();

  for (int i = 0; i < 4; ++i, ++it, ++it2);

  opa.erase(--it);
  opa2.erase(--it2);

  for (it = opa.begin(), it2 = opa2.begin();
       it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_EQ(opa.size(), opa2.size());
}

TEST(test_list, push_back_1) {
  s21::list<int> opa;
  std::list<int> opa2;

  const int value = 10;

  opa.push_back(value);
  opa2.push_back(value);

  EXPECT_EQ(opa.front(), opa2.front());
  EXPECT_EQ(opa.back(), opa2.back());
}

TEST(test_list, push_back_2) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  std::list<int> opa2({1, 2, 3, 4, 5});

  const int value = 10;

  opa.push_back(value);
  opa2.push_back(value);

  EXPECT_EQ(opa.back(), opa2.back());
}

TEST(test_list, push_front_1) {
  s21::list<int> opa;
  std::list<int> opa2;

  const int value = 10;

  opa.push_front(value);
  opa2.push_front(value);

  EXPECT_EQ(opa.front(), opa2.front());
}

TEST(test_list, push_front_2) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  std::list<int> opa2({1, 2, 3, 4, 5});

  const int value = 10;

  opa.push_front(value);
  opa2.push_front(value);

  EXPECT_EQ(opa.front(), opa2.front());
}

TEST(test_list, pop_back) {
  s21::list<int> opa({1, 2});
  std::list<int> opa2({1, 2});

  opa.pop_back();
  opa2.pop_back();

  EXPECT_EQ(opa.back(), opa2.back());
}

TEST(test_list, pop_front) {
  s21::list<int> opa({1, 2, 3});
  std::list<int> opa2({1, 2, 3});

  opa.pop_front();
  opa2.pop_front();

  EXPECT_EQ(opa.front(), opa2.front());
}

TEST(test_list, swap_1) {
  s21::list<int> opa({1, 2, 3});
  s21::list<int> opa2({8, 8, 8});
  std::list<int> opas({1, 2, 3});
  std::list<int> opas2({8, 8, 8});

  opa.swap(opa2);
  opas.swap(opas2);

  s21::list<int>::ListIterator it = opa.begin();
  s21::list<int>::ListIterator it2 = opa2.begin();

  std::list<int>::iterator its = opas.begin();
  std::list<int>::iterator its2 = opas2.begin();

  for (; (it != opa.end() || it2 != opa2.end()) &&
         (its != opas.end() || its2 != opas.end());
       ++it, ++it2, ++its, ++its2) {
    if (it != opa.end() && its != opas.end()) {
      EXPECT_EQ(*it, *its);
    }

    if (it2 != opa2.end() && its2 != opas2.end()) {
      EXPECT_EQ(*it2, *its2);
    }
  }
}

TEST(test_list, swap_2) {
  s21::list<int> opa;
  s21::list<int> opa2({8, 8, 8});
  std::list<int> opas;
  std::list<int> opas2({8, 8, 8});

  opa.swap(opa2);
  opas.swap(opas2);

  s21::list<int>::ListIterator it = opa.begin();
  s21::list<int>::ListIterator it2 = opa2.begin();

  std::list<int>::iterator its = opas.begin();
  std::list<int>::iterator its2 = opas2.begin();

  for (; (it != opa.end() || it2 != opa2.end()) &&
         (its != opas.end() || its2 != opas.end());
       ++it, ++it2, ++its, ++its2) {
    if (it != opa.end() && its != opas.end()) {
      EXPECT_EQ(*it, *its);
    }

    if (it2 != opa2.end() && its2 != opas2.end()) {
      EXPECT_EQ(*it2, *its2);
    }
  }

  EXPECT_TRUE(opa2.empty());
}

TEST(test_list, swap_3) {
  s21::list<int> opa;
  s21::list<int> opa2;

  opa.swap(opa2);

  EXPECT_TRUE(opa.empty());
  EXPECT_TRUE(opa2.empty());
}

TEST(test_list, merge_1) {
  s21::list<int> opa({1, 2, 3, 4});
  s21::list<int> opa2({1, 2, 3});

  std::list<int> opas({1, 2, 3, 4});
  std::list<int> opas2({1, 2, 3});

  opa.merge(opa2);
  opas.merge(opas2);

  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opas.begin();

  for (; it != opa.end() && it2 != opas.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_TRUE(opa2.empty());
  EXPECT_TRUE(opas2.empty());
}

TEST(test_list, merge_2) {
  s21::list<string> opa({"Hello", "World"});
  s21::list<string> opa2({",", "suka"});

  std::list<string> opas({"Hello", "World"});
  std::list<string> opas2({",", "suka"});

  opa.merge(opa2);
  opas.merge(opas2);

  s21::list<string>::ListIterator it = opa.begin();
  std::list<string>::iterator it2 = opas.begin();

  for (; it != opa.end() && it2 != opas.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_TRUE(opa2.empty());
  EXPECT_TRUE(opas2.empty());
}

TEST(test_list, merge_3) {
  s21::list<int> opa;
  s21::list<int> opa2({1, 2, 3});
  std::list<int> opas;
  std::list<int> opas2({1, 2, 3});

  opa.merge(opa2);
  opas.merge(opas2);
  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opas.begin();

  for (; it != opa.end() && it2 != opas.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }

  EXPECT_EQ(opa2.empty(), opas2.empty());
}

TEST(test_list, merge_4) {
  s21::list<int> opa;
  s21::list<int> opa2;
  std::list<int> opas;
  std::list<int> opas2;

  opa.merge(opa2);
  opas.merge(opas2);

  EXPECT_EQ(opa.empty(), opas.empty());
  EXPECT_EQ(opas.empty(), opas2.empty());
}

TEST(test_list, splice_1) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int> opa2({5, 5, 5});

  std::list<int> wuba({1, 2, 3, 4, 5});
  std::list<int> luba({5, 5, 5});

  s21::list<int>::ListConstIterator it = opa.cbegin();
  std::list<int>::const_iterator it2 = wuba.cbegin();

  opa.splice(it, opa2);
  wuba.splice(it2, luba);

  for (it = opa.cbegin(), it2 = wuba.cbegin();
       it != opa.end() && it2 != wuba.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, splice_2) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int> opa2({5, 5, 5});

  std::list<int> wuba({1, 2, 3, 4, 5});
  std::list<int> luba({5, 5, 5});

  s21::list<int>::ListConstIterator it = opa.cbegin();
  std::list<int>::const_iterator it2 = wuba.cbegin();

  ++it;
  ++it2;

  opa.splice(it, opa2);
  wuba.splice(it2, luba);

  for (it = opa.cbegin(), it2 = wuba.cbegin();
       it != opa.end() && it2 != wuba.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, splice_3) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int> opa2({5, 5, 5});

  std::list<int> wuba({1, 2, 3, 4, 5});
  std::list<int> luba({5, 5, 5});

  s21::list<int>::ListConstIterator it = opa.cend();
  std::list<int>::const_iterator it2 = wuba.cend();

  opa.splice(it, opa2);
  wuba.splice(it2, luba);

  for (it = opa.cbegin(), it2 = wuba.cbegin();
       it != opa.end() && it2 != wuba.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, splice_4) {
  s21::list<int> opa({1, 2, 3, 4, 5});
  s21::list<int> opa2;

  std::list<int> wuba({1, 2, 3, 4, 5});
  std::list<int> luba;

  s21::list<int>::ListConstIterator it = opa.cend();
  std::list<int>::const_iterator it2 = wuba.cend();

  opa.splice(it, opa2);
  wuba.splice(it2, luba);

  for (it = opa.cbegin(), it2 = wuba.cbegin();
       it != opa.end() && it2 != wuba.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, splice_5) {
  s21::list<int> opa;
  s21::list<int> opa2({5, 5, 5});

  std::list<int> wuba;
  std::list<int> luba({5, 5, 5});

  s21::list<int>::ListConstIterator it = opa.cbegin();
  std::list<int>::const_iterator it2 = wuba.cbegin();

  opa.splice(it, opa2);
  wuba.splice(it2, luba);

  for (it = opa.cbegin(), it2 = wuba.cbegin();
       it != opa.end() && it2 != wuba.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, reverse_1) {
  s21::list<int> opa({1, 2, 3, 4});
  std::list<int> opa2({1, 2, 3, 4});

  opa.reverse();
  opa2.reverse();
  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();
  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, reverse_2) {
  s21::list<int> opa({4, 3, 2, 1});
  std::list<int> opa2({4, 3, 2, 1});

  opa.reverse();
  opa2.reverse();
  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();
  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, reverse_3) {
  s21::list<string> opa({"!", "world", " ", "Hello"});
  std::list<string> opa2({"!", "world", " ", "Hello"});

  opa.reverse();
  opa2.reverse();
  s21::list<string>::ListIterator it = opa.begin();
  std::list<string>::iterator it2 = opa2.begin();
  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, unique_1) {
  s21::list<int> opa({1, 2, 2, 3, 4, 4, 2, 2});
  std::list<int> opa2({1, 2, 2, 3, 4, 4, 2, 2});

  opa.unique();
  opa2.unique();

  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();

  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, unique_2) {
  s21::list<int> opa;
  std::list<int> opa2;

  opa.unique();
  opa2.unique();

  EXPECT_EQ(opa.empty(), opa2.empty());
}

TEST(test_list, unique_3) {
  s21::list<string> opa({"Hello", "Hello", "world", "!", "!"});
  std::list<string> opa2({"Hello", "Hello", "world", "!", "!"});

  opa.unique();
  opa2.unique();

  s21::list<string>::ListIterator it = opa.begin();
  std::list<string>::iterator it2 = opa2.begin();

  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, sort_1) {
  s21::list<int> opa({3, 2, 3, 1, 5, 4, 10, 100, 99, 999, 10000});
  std::list<int> opa2({3, 2, 3, 1, 5, 4, 10, 100, 99, 999, 10000});

  opa.sort();
  opa2.sort();

  s21::list<int>::ListIterator it = opa.begin();
  std::list<int>::iterator it2 = opa2.begin();

  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, sort_2) {
  s21::list<string> opa({"Wuba", "Luba", "luba", "aboab", "biba", "boba"});
  std::list<string> opa2({"Wuba", "Luba", "luba", "aboab", "biba", "boba"});

  opa.sort();
  opa2.sort();

  s21::list<string>::ListIterator it = opa.begin();
  std::list<string>::iterator it2 = opa2.begin();

  for (; it != opa.end() && it2 != opa2.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(test_list, sort_3) {
  s21::list<string> opa;
  std::list<string> opa2;

  opa.sort();
  opa2.sort();

  EXPECT_EQ(opa.empty(), opa2.empty());
}

TEST(test_list, insert_many) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(test_list, insert_many_back) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(test_list, insert_many_front) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(test_list, contain_list_1) {
  s21::list<int> contained{1, 2, 3, 4};
  s21::list<s21::list<int>> container{contained};

  ASSERT_FALSE(contained.empty());
  ASSERT_EQ(contained.size(), 4);

  ASSERT_FALSE(container.empty());
  ASSERT_EQ(container.size(), 1);
  ASSERT_EQ(*((*container.begin()).begin()), 1);
}

TEST(test_list, contain_list_2) {
  s21::list<int> contained{1, 2, 3, 4};
  s21::list<int> contained_2{-1, -2, -3, -4};

  s21::list<s21::list<int>> container{contained};
  s21::list<s21::list<int>> container_2{contained_2};

  container.merge(container_2);

  ASSERT_FALSE(container.empty());
  ASSERT_TRUE(container_2.empty());
  ASSERT_EQ(container.size(), 2);

  s21::list<s21::list<int>>::iterator it = container.begin();

  ASSERT_EQ(*(*it).begin(), -1);
  ++it;
  ASSERT_EQ(*(*it).begin(), 1);
}

TEST(test_list, contain_list_3) {
  s21::list<int> contained{1, 2, 3, 4};
  s21::list<int> contained_2{-1, -2, -3, -4};

  s21::list<s21::list<int>> container{contained};
  s21::list<s21::list<int>> container_2{contained_2};

  container.merge(container_2);

  ASSERT_FALSE(container.empty());
  ASSERT_TRUE(container_2.empty());
  ASSERT_EQ(container.size(), 2);

  s21::list<s21::list<int>>::iterator it = container.begin();

  ASSERT_EQ(*(*it).begin(), -1);
  ++it;
  ASSERT_EQ(*(*it).begin(), 1);
}

TEST(test_list, contain_list_4) {
  s21::list<int> contained{1, 2, 3, 4};
  s21::list<int> contained_2{-1, -2, -3, -4};
  s21::list<int> contained_3{5, 6, 7, 8};
  s21::list<int> contained_4{9, 10, 11, 12};
  s21::list<int> contained_5{1, 2, 3, 4};

  s21::list<s21::list<int>> container{contained, contained_4, contained_3,
                                      contained_2, contained_5};

  container.sort();

  s21::list<s21::list<int>>::iterator it = container.begin();

  ASSERT_EQ(*(*it).begin(), -1);
  ++it;
  ASSERT_EQ(*(*it).begin(), 1);
  ++it;
  ASSERT_EQ(*(*it).begin(), 1);
  it = container.end();
  --it;
  ASSERT_EQ(*(*it).begin(), 9);
}