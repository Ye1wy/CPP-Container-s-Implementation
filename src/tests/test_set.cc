#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"

TEST(set, constructors_1) {
  s21::set<int> s21_set_int;
  s21::set<double> s21_set_double;
  s21::set<std::string> s21_set_string;

  EXPECT_EQ(s21_set_int.size(), 0U);
  EXPECT_EQ(s21_set_double.size(), 0U);
  EXPECT_EQ(s21_set_string.size(), 0U);
}

TEST(set, constructors_2) {
  s21::set<int> s21_set_int{1, 2, 3, 4, 5};
  s21::set<double> s21_set_double{1.30359, 2847.4925, 923.39281};
  s21::set<std::string> s21_set_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_set_int.size(), 5U);
  EXPECT_EQ(s21_set_double.size(), 3U);
  EXPECT_EQ(s21_set_string.size(), 4U);
}

TEST(set, constructors_3) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int;
  s21_set_res_int = s21_set_ref_int;

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double{s21_set_ref_double};
  s21_set_res_double = s21_set_ref_double;

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string;
  s21_set_res_string = s21_set_ref_string;

  EXPECT_EQ(s21_set_ref_int.size(), s21_set_res_int.size());
  EXPECT_EQ(s21_set_ref_double.size(), s21_set_res_double.size());
  EXPECT_EQ(s21_set_ref_string.size(), s21_set_res_string.size());
}

TEST(set, constructors_4) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set, constructors_5) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int;
  s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double;
  s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string;
  s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}
TEST(set, modifiers_insert_1) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set, modifiers_insert_2) {
  s21::set<double> s21_set;

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = s21_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = s21_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = s21_set.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = s21_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set, modifiers_insert_3) {
  s21::set<std::string> s21_set;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      s21_set.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      s21_set.insert("hola");
  EXPECT_EQ(*insert4.first, "hola");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      s21_set.insert("hello");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set, modifiers_insert_4) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, false);
  EXPECT_EQ(insert3.second, false);

  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set, modifiers_insert_5) {
  s21::set<double> s21_set = {21};

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set, modifiers_insert_6) {
  s21::set<std::string> s21_set = {"hello"};

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert1.first, "hi");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set, iterators_begin_1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*s21_set.begin(), 2);
}

TEST(set, iterators_begin_2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*s21_set.begin(), 2.77);
}

TEST(set, iterators_begin_3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hi-hi", "hola",
                                   "hello, there"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set, iterators_begin_4) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*s21_set.begin(), 1.4);
}

TEST(set, iterators_begin_5) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set, iterators_end_1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*(--s21_set.end()), 23);
}

TEST(set, iterators_end_2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 11.400000001, 3.9};

  EXPECT_EQ(*(--s21_set.end()), 11.400000001);
}

TEST(set, iterators_end_3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
}

TEST(set, iterators_end_4) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*(--s21_set.end()), 1.4);
}

TEST(set, iterators_end_5) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*(--s21_set.end()), "hello");
}

TEST(set, modifiers_balance_1) {
  s21::set<int> s21_set = {1, 15, 5};

  EXPECT_EQ(*(--s21_set.end()), 15);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set, modifiers_balance_2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*(--s21_set.end()), 11.4);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set, modifiers_balance_3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set, modifiers_balance_4) {
  s21::set<int> s21_set = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*(--s21_set.end()), 1543);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set, modifiers_balance_5) {
  s21::set<int> s21_set = {30, 5, 43, 1, 20, 40, 60, 35, 32};

  EXPECT_EQ(*(--s21_set.end()), 60);
  EXPECT_EQ(*s21_set.begin(), 1);
  EXPECT_EQ(s21_set.size(), 9U);
}
TEST(set, modifiers_empty_1) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.empty(), 0);
}

TEST(set, modifiers_empty_2) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.empty(), 1);
}

TEST(set, modifiers_max_size_1) {
  s21::set<double> s21_set;
  std::set<double> std_set;

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set, modifiers_max_size_2) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  std::set<double> std_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set, modifiers_swap_1) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set, modifiers_swap_2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set, modifiers_swap_3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set, modifiers_swap_4) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_res.size(), 0U);
}
TEST(set, modifiers_contains_1) {
  s21::set<double> s21_set = {22.2, 44.48};

  EXPECT_EQ(s21_set.contains(22.2), true);
  EXPECT_EQ(s21_set.contains(44.48), true);
}

TEST(set, modifiers_contains_2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_ref.contains(22.2), false);
  EXPECT_EQ(s21_set_ref.contains(44.48), false);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(s21_set_res.contains(22.2), true);
  EXPECT_EQ(s21_set_res.contains(44.48), true);
}

TEST(set, modifiers_contains_3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(s21_set_ref.contains(12.4457), true);
  EXPECT_EQ(s21_set_ref.contains(1.44), true);
  EXPECT_EQ(s21_set_ref.contains(22.2), true);

  EXPECT_EQ(s21_set_res.size(), 0U);
  EXPECT_EQ(s21_set_res.contains(12.4457), false);
  EXPECT_EQ(s21_set_res.contains(1.44), false);
  EXPECT_EQ(s21_set_res.contains(22.2), false);
}

TEST(set, modifiers_contains_4) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.size(), 0U);
  EXPECT_EQ(s21_set.contains(12.4457), false);
}

TEST(set, find_1) {
  s21::set<std::string> set({"t", "v", "p", "w"});
  auto i = set.begin();
  EXPECT_EQ(i, set.find("p"));
}

TEST(set, constructor_default) {
  s21::set<std::string> set;
  std::set<std::string> set2;
  EXPECT_EQ(set.size(), set2.size());
  EXPECT_EQ(set.empty(), set2.empty());
  EXPECT_EQ(set.begin(), --(set.end()));
}

TEST(set, constructor_initializer_list) {
  s21::set<std::string> set(
      {"hello", "world", "test", "vasia", "petia", "staff"});
  std::set<std::string> set2(
      {"hello", "world", "test", "vasia", "petia", "staff"});
  EXPECT_EQ(set.size(), set2.size());
  auto it1 = set.begin();
  auto it2 = set2.begin();
  EXPECT_EQ(*it1, *it2);
  it1 = --set.end();
  it2 = --set2.end();
  EXPECT_EQ(*it1, *it2);
}

TEST(set, constructor_initializer_list_with_doubles) {
  s21::set<std::string> set(
      {"a", "b", "c", "d", "e", "f", "f", "e", "d", "c", "b", "a"});
  std::set<std::string> set2(
      {"a", "b", "c", "d", "e", "f", "f", "e", "d", "c", "b", "a"});
  EXPECT_EQ(set.size(), set2.size());
  auto it1 = set.begin();
  auto it2 = set2.begin();
  EXPECT_EQ(*it1, *it2);
  it1 = --set.end();
  it2 = --set2.end();
  EXPECT_EQ(*it1, *it2);
}

TEST(set, constructor_copy) {
  s21::set<double> set({5.11, -0.67, 88.11, -14.01});
  s21::set<double> set2(set);
  EXPECT_EQ(set.size(), set2.size());
  EXPECT_EQ(*set.begin(), *set2.begin());
  EXPECT_EQ(*(--set.end()), *(--set2.end()));
}

TEST(set, constructor_move) {
  s21::set<int> set({18, 0, -812, 332, -11});
  s21::set<int> set2(std::move(set));
  s21::set<int> set3({18, 0, -812, 332, -11});
  EXPECT_EQ(set3.size(), set2.size());
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(*set3.begin(), *set2.begin());
  EXPECT_EQ(*(--set3.end()), *(--set2.end()));
}

TEST(set, operator_equal) {
  s21::set<int> set({18, 0, -812, 332, -11});
  s21::set<int> set2;
  set2 = std::move(set);
  s21::set<int> set3({18, 0, -812, 332, -11});
  EXPECT_EQ(set3.size(), set2.size());
  EXPECT_TRUE(set.empty());
  EXPECT_EQ(*set3.begin(), *set2.begin());
  EXPECT_EQ(*(--set3.end()), *(--set2.end()));
}

TEST(set, clear) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  set.clear();
  EXPECT_EQ(set.size(), 0);
}

TEST(set, clear_empty) {
  s21::set<std::string> set;
  set.clear();
  EXPECT_EQ(set.size(), 0);
  EXPECT_TRUE(set.empty());
}

TEST(set, erase_no_children) {
  s21::set<float> set({5.11, -0.67, 88.11, -14.01});
  auto t = set.begin();
  ++t;
  set.erase(set.begin());
  EXPECT_EQ(*set.begin(), *t);
}

TEST(set, erase_one_child) {
  s21::set<std::string> s({"t", "h"});
  s.erase(s.begin());
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(*s.begin(), "t");
}

TEST(set, erase_two_children) {
  s21::set<int> s({2, 1, 3});
  auto i = ++s.begin();
  s.erase(i);
  EXPECT_EQ(s.size(), 2);
}

TEST(set, erase_end) {
  s21::set<int> s({1, 2, 3});
  auto i = --s.end();
  s.erase(i);
  EXPECT_EQ(s.size(), 2);
}

TEST(set, erase_01) {
  s21::set<int> s({2, 1, 3, 4});
  auto i = --s.end();
  --i;
  s.erase(i);
  EXPECT_EQ(s.size(), 3);
}

TEST(set, erase_02) {
  s21::set<int> s({2, 1, 3, 4, -2, -4, 0, -1});
  auto i = ++s.begin();
  s.erase(i);
  EXPECT_EQ(s.size(), 7);
}

TEST(set, insert_to_empty_true) {
  s21::set<float> set;
  const float g = 5.11;
  auto t = set.insert(g);
  auto i = set.begin();
  EXPECT_TRUE(t.second);
  EXPECT_EQ(set.size(), 1);
  EXPECT_EQ(*i, g);
}

TEST(set, insert_true) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  const std::string g = "h";
  auto t = set.insert(g);
  auto i = set.begin();
  EXPECT_TRUE(t.second);
  EXPECT_EQ(set.size(), 5);
  EXPECT_EQ(*i, g);
}

TEST(set, insert_false) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  const std::string g = "t";
  auto t = set.insert(g);
  EXPECT_FALSE(t.second);
  EXPECT_EQ(set.size(), 4);
}

TEST(set, begin) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  std::set<std::string> set2({"t", "v", "p", "s"});
  EXPECT_EQ(*set.begin(), *set2.begin());
}

TEST(set, begin_post_increment) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  std::set<std::string> set2({"t", "v", "p", "s"});
  auto it = set.begin();
  auto it2 = set2.begin();
  ++it;
  ++it2;
  EXPECT_EQ(*it, *it2);
}

TEST(set, begin_pre_increment) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  std::set<std::string> set2({"t", "v", "p", "s"});
  auto it = set.begin();
  auto it2 = set2.begin();
  ++it;
  ++it2;
  --it;
  --it2;
  EXPECT_EQ(*it, *it2);
}

TEST(set, increment_01) {
  s21::set<int> s({0,   50,  -50, 25,  75,  -25, -75, 10,  40, 60, 90,
                   -10, -40, -60, -90, 5,   15,  35,  45,  55, 65, 85,
                   95,  -5,  -15, -35, -45, -55, -65, -85, -95});
  for (auto i = s.begin(); i != s.end();) {
    ++i;
  }
}

TEST(set, decrement) {
  s21::set<int> s({0,   50,  -50, 25,  75,  -25, -75, 10,  40, 60, 90,
                   -10, -40, -60, -90, 5,   15,  35,  45,  55, 65, 85,
                   95,  -5,  -15, -35, -45, -55, -65, -85, -95});
  auto i = s.end();
  for (int t = 0; t < 31; ++t) {
    --i;
  }
}

TEST(set, end) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  std::set<std::string> set2({"t", "v", "p", "s"});
  EXPECT_EQ(*(--set.end()), *(--set2.end()));
}

TEST(set, end_increment) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  std::set<std::string> set2({"t", "v", "p", "s"});
  auto it = --set.end();
  auto it2 = --set2.end();
  ++it;
  ++it2;
  EXPECT_EQ(*(--set.end()), *(--set2.end()));
}

TEST(set, size) {
  s21::set<int> set({6, 18, -22, 0, 77, 812, -888, 153, 933, -704});
  std::set<int> set2({6, 18, -22, 0, 77, 812, -888, 153, 933, -704});
  EXPECT_EQ(set.size(), set2.size());
}

TEST(set, size_empty) {
  s21::set<int> set;
  std::set<int> set2;
  EXPECT_EQ(set.size(), set2.size());
}

TEST(set, max_size) {
  s21::set<double> s({5.11, -0.67, 88.11, -14.01});
  std::set<double> s2({5.11, -0.67, 88.11, -14.01});
  EXPECT_EQ(s.max_size(), s2.max_size());
}

TEST(set, swap) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  s21::set<std::string> set2({"g"});
  s21::set<std::string> set3({"t", "v", "p", "s"});
  set.swap(set2);
  EXPECT_EQ(set.size(), 1);
  EXPECT_EQ(set2.size(), set3.size());
  EXPECT_EQ(*set2.begin(), *set3.begin());
  EXPECT_EQ(*(--set2.end()), *(--set3.end()));
}

TEST(set, merge) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  s21::set<std::string> set2({"g"});
  set.merge(set2);
  EXPECT_EQ(set.size(), 5);
  EXPECT_EQ(set2.size(), 0);
}

TEST(set, merge_2) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  s21::set<std::string> set2;
  set.merge(set2);
  EXPECT_EQ(set.size(), 4);
  EXPECT_EQ(set2.size(), 0);
}

TEST(set, merge_3) {
  s21::set<std::string> set;
  s21::set<std::string> set2({"t", "v", "p", "s"});
  set.merge(set2);
  EXPECT_EQ(set.size(), 4);
  EXPECT_EQ(set2.size(), 0);
}

TEST(set, merge_4) {
  s21::set<std::string> set;
  s21::set<std::string> set2;
  set.merge(set2);
  EXPECT_EQ(set.size(), 0);
  EXPECT_EQ(set2.size(), 0);
}

TEST(set, find) {
  std::set<std::string> set({"t", "v", "p", "w"});
  auto i = set.begin();
  EXPECT_EQ(i, set.find("p"));
}

TEST(set, contains) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  EXPECT_TRUE(set.contains("v"));
}

TEST(set, contains_2) {
  s21::set<std::string> set({"t", "v", "p", "s"});
  EXPECT_FALSE(set.contains("n"));
}

TEST(set, set_insert_many_01) {
  s21::set<int> s;
  s21::set<int> s2;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.insert(5);
  s.insert(6);
  s2.insert_many(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(s, s2);
}

TEST(set, set_insert_many_02) {
  s21::set<int> s;
  s21::set<int> s2;
  s.insert(1);
  s.insert(2);
  s.insert(4);
  s.insert(4);
  s.insert(5);
  s.insert(6);
  s2.insert_many(1, 2, 4, 4, 5, 6);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s, s2);
  EXPECT_EQ(s2.size(), 5);
}

TEST(set, set_insert_many_03) {
  s21::set<int> s;
  auto results = s.insert_many(1, 2, 2, 3, 4, 4, 5, 6, 6, 6);

  EXPECT_EQ(s.size(), 6);
  EXPECT_EQ(results.size(), 10);
  EXPECT_EQ(results[0].second, true);
  EXPECT_EQ(results[1].second, true);
  EXPECT_EQ(results[2].second, false);
  EXPECT_EQ(results[3].second, true);
  EXPECT_EQ(results[4].second, true);
  EXPECT_EQ(results[5].second, false);
  EXPECT_EQ(results[6].second, true);
  EXPECT_EQ(results[7].second, true);
  EXPECT_EQ(results[8].second, false);
  EXPECT_EQ(results[9].second, false);

  auto it = s.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);

  EXPECT_EQ(s.size(), 6);
}