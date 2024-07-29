#include <gtest/gtest.h>

#include <unordered_set>

#include "../s21_containersplus.h"

TEST(multiset, multiset_constructor_1) {
  s21::multiset<int> s;
  std::multiset<int> s2;

  s21::multiset<double> d;
  std::multiset<double> d2;

  s21::multiset<std::string> st;
  std::multiset<std::string> st2;

  EXPECT_EQ(s.empty(), s2.empty());
  EXPECT_EQ(d.empty(), d2.empty());
  EXPECT_EQ(st.empty(), st2.empty());
}

TEST(multiset, multiset_constructor_2) {
  s21::multiset<int> s{1, 2, 3, 4, 5};
  std::multiset<int> s2{1, 2, 3, 4, 5};

  s21::multiset<double> d{1.1, 2.2, 3.3, 4.4, 5.5};
  std::multiset<double> d2{1.1, 2.2, 3.3, 4.4, 5.5};

  s21::multiset<std::string> st{"1", "2", "3", "4", "5"};
  std::multiset<std::string> st2{"1", "2", "3", "4", "5"};

  EXPECT_EQ(s.size(), s2.size());
  EXPECT_EQ(d.size(), d2.size());
  EXPECT_EQ(st.size(), st2.size());
}

TEST(multiset, multiset_copy) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2(s1);
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(multiset, multiset_move) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2(std::move(s1));
  ASSERT_TRUE(s1.empty());
  ASSERT_EQ(s2.size(), 3);
  ASSERT_TRUE(s2.find(1) != s2.end());
  ASSERT_TRUE(s2.find(2) != s2.end());
  ASSERT_TRUE(s2.find(3) != s2.end());
}

TEST(multiset, multiset_destructor) {
  s21::multiset<int> *s = new s21::multiset<int>{1, 2, 3};
  ASSERT_EQ(s->size(), 3);
  delete s;
}

TEST(multiset, multiset_operator_r) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2 = s1;

  ASSERT_EQ(s1.size(), s2.size());
}

TEST(multiset, multiset_operator_r_2) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2{s1};

  ASSERT_EQ(s1.size(), s2.size());
}

TEST(multiset, multiset_begin_1) {
  s21::multiset<int> s1{1, 2, 3};
  ASSERT_EQ(*s1.begin(), 1);
}

TEST(multiset, multiset_begin_2) {
  s21::multiset<int> s1;
  s1.insert(4);
  ASSERT_EQ(*s1.begin(), 4);
}

TEST(multiset, multiset_begin_3) {
  s21::multiset<int> s1;
  EXPECT_EQ(s1.begin(), s1.end());
}

TEST(multiset, multiset_begin_4) {
  s21::multiset<int> s1 = {3, 2, 1};
  EXPECT_EQ(*s1.begin(), 1);
}

TEST(multiset, multiset_cbegin_1) {
  const s21::multiset<int> s1{1, 2, 3};
  ASSERT_EQ(*s1.begin(), 1);
}

TEST(multiset, multiset_cbegin_2) {
  const s21::multiset<int> s1;
  EXPECT_EQ(s1.begin(), s1.end());
}

TEST(multiset, multiset_cbegin_3) {
  const s21::multiset<int> s1 = {3, 2, 1};
  EXPECT_EQ(*s1.begin(), 1);
}

TEST(multiset, multiset_size_1) {
  s21::multiset<int> s1{1, 2, 3};
  ASSERT_EQ(s1.size(), 3);
}

TEST(multiset, multiset_size_2) {
  s21::multiset<int> s1;
  ASSERT_EQ(s1.size(), 0);
}

TEST(multiset, multiset_size_3) {
  s21::multiset<int> s1;
  s1.insert(1);
  s1.insert(2);

  ASSERT_EQ(s1.size(), 2);
}

TEST(multiset, multiset_maxsize) {
  s21::multiset<int> s1;
  size_t maxSize = s1.max_size();
  EXPECT_GT(maxSize, 0);
  EXPECT_LE(maxSize, std::numeric_limits<size_t>::max());
}

TEST(multiset, multiset_clear_1) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
  s.clear();
  EXPECT_EQ(s.size(), 0);
}

TEST(multiset, multiset_clear_2) {
  s21::multiset<int> s;
  EXPECT_EQ(s.size(), 0);
  s.clear();
  EXPECT_EQ(s.size(), 0);
}

TEST(multiset, multiset_insert_1) {
  s21::multiset<int> s1;
  s1.insert(42);
  s1.insert(24);
  s1.insert(84);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_TRUE(s1.contains(42));
  EXPECT_TRUE(s1.contains(24));
  EXPECT_TRUE(s1.contains(84));
}

TEST(multiset, multiset_insert_2) {
  s21::multiset<std::string> s;
  s.insert("foo");
  s.insert("bar");
  s.insert("baz");
  EXPECT_TRUE(s.contains("foo"));
  EXPECT_TRUE(s.contains("bar"));
  EXPECT_TRUE(s.contains("baz"));
}

TEST(multiset, multiset_erase_1) {
  s21::multiset<int> s{5, 4, 3, 2, 1};
  auto it = s.find(3);

  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(4u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(multiset, multiset_erase_2) {
  s21::multiset<int> s = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(8u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(multiset, multiset_erase_3) {
  s21::multiset<int> s = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  auto it = s.find(7);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(8u, s.size());
  ASSERT_EQ(s.end(), s.find(7));
}

TEST(multiset, multiset_erase_4) {
  s21::multiset<int> s = {5, 8, 6, 7};
  auto it = s.find(8);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(3u, s.size());
  ASSERT_EQ(s.end(), s.find(8));
}

TEST(multiset, multiset_erase_5) {
  s21::multiset<int> s{3, 2, 1};
  auto it = s.begin();
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2u, s.size());
  ASSERT_EQ(s.end(), s.find(1));
}

TEST(multiset, multiset_erase_6) {
  s21::multiset<int> s{1, 2, 3};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(multiset, multiset_swap) {
  s21::multiset<std::string> s({"t", "v", "p", "s"});
  s21::multiset<std::string> s2({"g"});
  s21::multiset<std::string> s3({"t", "v", "p", "s"});
  s.swap(s2);
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s2.size(), s3.size());
  EXPECT_EQ(*s2.begin(), *s3.begin());
  EXPECT_EQ(*(--s2.end()), *(--s3.end()));
}

TEST(multiset, multiset_merge_1) {
  s21::multiset<std::string> s({"t", "v", "p", "s"});
  s21::multiset<std::string> s2({"g"});
  s.merge(s2);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s2.size(), 0);
}

TEST(multiset, multiset_merge_2) {
  s21::multiset<std::string> s({"t", "v", "p", "s"});
  s21::multiset<std::string> s2;
  s.merge(s2);
  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(s2.size(), 0);
}

TEST(multiset, multiset_merge_3) {
  s21::multiset<std::string> s;
  s21::multiset<std::string> s2({"t", "v", "p", "s"});
  s.merge(s2);
  EXPECT_EQ(s.size(), 4);
  EXPECT_EQ(s2.size(), 0);
}

TEST(multiset, multiset_merge_4) {
  s21::multiset<std::string> s;
  s21::multiset<std::string> s2;
  s.merge(s2);
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s2.size(), 0);
}

TEST(multiset, multiset_count_1) {
  s21::multiset<std::string> s({"t", "v", "p", "s"});
  EXPECT_EQ(s.count("v"), 1);
}

TEST(multiset, mulriset_count_2) {
  s21::multiset<std::string> s({"t", "v", "r", "s", "r", "a", "r"});
  EXPECT_EQ(s.count("r"), 3);
}

TEST(multiset, multiset_count_3) {
  s21::multiset<std::string> s({"t", "v", "p", "s", "a", "a", "a"});
  EXPECT_EQ(s.count("a"), 3);
}

TEST(multiset, multiset_find_1) {
  s21::multiset<std::string> s({"t", "v", "p", "w"});
  auto i = s.begin();
  EXPECT_EQ(i, s.find("p"));
}

TEST(multiset, multiset_find_2) {
  s21::multiset<std::string> s({"a", "a", "b", "b", "t", "v", "p", "w"});
  auto i = ++s.begin();
  EXPECT_EQ(i, s.find("a"));
}

TEST(multiset, lower_bound_1) {
  s21::multiset<int> s({-1, -19, 1, 1, 3, 5, 5, 8, 55, 100});
  std::multiset<int> s2({-1, -19, 1, 1, 3, 5, 5, 8, 55, 100});
  EXPECT_EQ(*s.lower_bound(100), *s2.lower_bound(100));
}

TEST(multiset, lower_bound_2) {
  s21::multiset<int> s({-1, -19, 1, 1, 3, 5, 5, 8, 55, 102});
  std::multiset<int> s2({-1, -19, 1, 1, 3, 5, 5, 8, 55, 102});
  EXPECT_EQ(*s.lower_bound(100), *s2.lower_bound(100));
}

TEST(multiset, upper_bound) {
  s21::multiset<int> s({-1, -19, 1, 1, 3, 5, 5, 8, 55, 55, 100});
  std::multiset<int> s2({-1, -19, 1, 1, 3, 5, 5, 8, 55, 55, 100});
  EXPECT_EQ(*s.upper_bound(55), *s2.upper_bound(55));
}

TEST(multiset, multiset_equal_range) {
  s21::multiset<std::string> s(
      {"a", "a", "a", "t", "c", "a", "d", "e", "a", "f"});
  std::multiset<std::string> s2(
      {"a", "a", "a", "t", "c", "a", "d", "e", "a", "f"});
  EXPECT_EQ(*s.equal_range("a").first, *s2.equal_range("a").first);
  EXPECT_EQ(*s2.equal_range("a").second, *s.equal_range("a").second);
}

TEST(multiset, multiset_contains_move_1) {
  s21::multiset<int> s1;
  s21::multiset<int> s2;
  s2.insert(1);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_FALSE(s2.contains(1));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_FALSE(s1.contains(1));
}

TEST(multiset, multiset_merge_12) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2 = {2, 4, 6};
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 6);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(multiset, multiset_merge_22) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2;
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(multiset, multiset_merge_33) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2;
  s2.merge(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
}

TEST(multiset, multiset_merge_5) {
  s21::multiset<int> s1 = {1, 3, 5};
  s1.merge(s1);
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(multiset, multiset_find) {
  s21::multiset<std::string> s;
  auto iter = s.find("one");
  EXPECT_EQ(iter, s.end());
}

TEST(multiset, mulriset_move_assignment11) {
  s21::multiset<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s21::multiset<int> s2;
  s2.insert(4);
  s2.insert(5);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_FALSE(s1.contains(1));
  EXPECT_FALSE(s1.contains(2));
  EXPECT_FALSE(s1.contains(3));
}

TEST(multiset, multiset_merge_112) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2 = {2, 4, 6};
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 6);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(multiset, multiset_merge_221) {
  s21::multiset<int> s1 = {1, 3, 5};
  s21::multiset<int> s2;
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(multiset, multiset_find31) {
  s21::multiset<std::string> s;
  auto iter = s.find("one");
  EXPECT_EQ(iter, s.end());
}

TEST(multiset, multiset_insert_many_01) {
  s21::multiset<int> s;
  s21::multiset<int> s2;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.insert(5);
  s.insert(6);
  s2.insert_many(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(s, s2);
}

TEST(multiset, multiset_insert_many_02) {
  s21::multiset<int> s;
  s21::multiset<int> s2;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.insert(5);
  s.insert(6);
  s2.insert_many(1, 2, 3, 4, 5, 6);
  EXPECT_EQ(s.size(), 6);
}

TEST(multiset, multiset_insert_many_03) {
  s21::multiset<int> s;

  auto results = s.insert_many(1, 2, 2, 3, 4, 4, 4, 5, 6, 6, 6, 6);

  EXPECT_EQ(s.size(), 12);

  EXPECT_EQ(results.size(), 12);
  EXPECT_EQ(results[0].second, true);
  EXPECT_EQ(results[1].second, true);
  EXPECT_EQ(results[2].second, true);
  EXPECT_EQ(results[3].second, true);
  EXPECT_EQ(results[4].second, true);
  EXPECT_EQ(results[5].second, true);
  EXPECT_EQ(results[6].second, true);
  EXPECT_EQ(results[7].second, true);
  EXPECT_EQ(results[8].second, true);
  EXPECT_EQ(results[9].second, true);
  EXPECT_EQ(results[10].second, true);
  EXPECT_EQ(results[11].second, true);

  EXPECT_EQ(s.count(1), 1);
  EXPECT_EQ(s.count(2), 2);
  EXPECT_EQ(s.count(3), 1);
  EXPECT_EQ(s.count(4), 3);
  EXPECT_EQ(s.count(5), 1);
  EXPECT_EQ(s.count(6), 4);
  EXPECT_EQ(s.count(7), 0);

  auto it = s.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);
  EXPECT_EQ(*it++, 6);
  EXPECT_EQ(*it++, 6);
  EXPECT_EQ(*it++, 6);

  EXPECT_EQ(s.size(), 12);
}