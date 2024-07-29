#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

TEST(queue, constructors_1) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  EXPECT_EQ(std_queue.empty(), s21_queue.empty());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, constructors_2) {
  s21::queue<unsigned int> my_queue1{1, 2, 3};
  ASSERT_EQ(my_queue1.size(), 3u);
  ASSERT_EQ(my_queue1.front(), 1u);
  ASSERT_EQ(my_queue1.back(), 3u);
  s21::queue<std::string> my_queue2{"hello", "world"};
  ASSERT_EQ(my_queue2.size(), 2u);
  ASSERT_EQ(my_queue2.front(), "hello");
  ASSERT_EQ(my_queue2.back(), "world");
}

TEST(queue, constructors_3) {
  s21::queue<int> q;
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
}

TEST(queue, constructors_initializer_list_1) {
  s21::queue<std::pair<std::string, int>> my_queue1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> my_queue2;
  my_queue2.push({"one", 1});
  my_queue2.push({"two", 2});
  my_queue2.push({"three", 3});
  EXPECT_EQ(my_queue1.empty(), my_queue2.empty());
  EXPECT_EQ(my_queue1.size(), my_queue2.size());
  while (!my_queue2.empty()) {
    EXPECT_EQ(my_queue1.front().first, my_queue2.front().first);
    EXPECT_EQ(my_queue1.front().second, my_queue2.front().second);
    my_queue1.pop();
    my_queue2.pop();
  }
}

TEST(queue, constructors_initializer_list_2) {
  s21::queue<unsigned int> q{};
  ASSERT_EQ(q.size(), 0);
  ASSERT_TRUE(q.empty());
}

TEST(queue, constructors_initializer_list_3) {
  s21::queue<int> q{1, 2, 3};
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(3, q.size());
  ASSERT_EQ(1, q.front());
  ASSERT_EQ(3, q.back());
}

TEST(queue, constructors_copy_1) {
  s21::queue<unsigned int> my_queue1{1, 2, 3};
  s21::queue<unsigned int> my_queue2{my_queue1};
  ASSERT_EQ(my_queue1.size(), my_queue2.size());
  ASSERT_EQ(my_queue1.front(), my_queue2.front());
  ASSERT_EQ(my_queue1.back(), my_queue2.back());
}

TEST(queue, constructors_copy_2) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, constructors_copy_3) {
  s21::queue<std::pair<std::string, int>> my_queue1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> my_queue2(my_queue1);
  EXPECT_EQ(my_queue1.empty(), my_queue2.empty());
  EXPECT_EQ(my_queue1.size(), my_queue2.size());
  while (my_queue1.size()) {
    EXPECT_EQ(my_queue1.front().first, my_queue2.front().first);
    EXPECT_EQ(my_queue1.front().second, my_queue2.front().second);
    my_queue1.pop();
    my_queue2.pop();
  }
}

TEST(queue, constuctors_copy_4) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, constuctors_copy_5) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2(q1);
  ASSERT_EQ(q1.size(), q2.size());
  ASSERT_EQ(q1.front(), q2.front());
  ASSERT_EQ(q1.back(), q2.back());
}

TEST(queue, constructors_move_1) {
  s21::queue<unsigned int> my_queue1{1, 2, 3};
  s21::queue<unsigned int> my_queue2{std::move(my_queue1)};
  ASSERT_EQ(my_queue1.size(), 0u);
  ASSERT_EQ(my_queue2.size(), 3u);
  ASSERT_EQ(my_queue2.front(), 1u);
  ASSERT_EQ(my_queue2.back(), 3u);
}

TEST(queue, constructors_move_2) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2(std::move(q1));
  ASSERT_EQ(3, q2.size());
  ASSERT_EQ(1, q2.front());
  ASSERT_EQ(3, q2.back());
  ASSERT_TRUE(q1.empty());
}

TEST(queue, modifiers_insert_many_back_1) {
  s21::queue<int> my_queue;
  my_queue.insert_many_back(10);
  my_queue.insert_many_back(20);
  my_queue.insert_many_back(30);

  ASSERT_EQ(my_queue.front(), 10);
  my_queue.pop();
  ASSERT_EQ(my_queue.front(), 20);
  my_queue.pop();
  ASSERT_EQ(my_queue.front(), 30);
}

TEST(queue, modifiers_push_pop_1) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  while (!std_queue.empty()) {
    EXPECT_EQ(std_queue.front(), s21_queue.front());
    EXPECT_EQ(std_queue.back(), s21_queue.back());
    std_queue.pop();
    s21_queue.pop();
  }
}

TEST(queue, modifiers_push_pop_2) {
  s21::queue<std::pair<std::string, int>> q;
  std::queue<std::pair<std::string, int>> my_queue2;
  q.push({"one", 1});
  my_queue2.push({"one", 1});
  q.push({"two", 2});
  my_queue2.push({"two", 2});
  q.push({"three", 3});
  my_queue2.push({"three", 3});
  EXPECT_EQ(q.empty(), my_queue2.empty());
  EXPECT_EQ(q.size(), my_queue2.size());
  while (!my_queue2.empty()) {
    EXPECT_EQ(q.front().first, my_queue2.front().first);
    EXPECT_EQ(q.front().second, my_queue2.front().second);
    q.pop();
    my_queue2.pop();
  }
}

TEST(queue, modifiers_front_1) {
  s21::queue<std::pair<std::string, int>> q{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> my_queue2;
  my_queue2.push({"one", 1});
  my_queue2.push({"two", 2});
  my_queue2.push({"three", 3});
  EXPECT_EQ(q.front().first, my_queue2.front().first);
  EXPECT_EQ(q.front().second, my_queue2.front().second);
}

TEST(queue, modifiers_back_1) {
  s21::queue<std::pair<std::string, int>> q{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> my_queue2;
  my_queue2.push({"one", 1});
  my_queue2.push({"two", 2});
  my_queue2.push({"three", 3});
  EXPECT_EQ(q.back().first, my_queue2.back().first);
  EXPECT_EQ(q.back().second, my_queue2.back().second);
}

TEST(queue, modifiers_size_1) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, modifiers_copy_1) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
}

TEST(queue, modifiers_copy_2) {
  s21::queue<std::pair<std::string, int>> my_queue1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> my_queue2;
  std::queue<std::pair<std::string, int>> my_queue3;
  my_queue2 = my_queue1;
  EXPECT_EQ(my_queue1.empty(), my_queue2.empty());
  EXPECT_EQ(my_queue1.size(), my_queue2.size());
  while (my_queue1.size()) {
    EXPECT_EQ(my_queue1.front().first, my_queue2.front().first);
    EXPECT_EQ(my_queue1.front().second, my_queue2.front().second);
    my_queue1.pop();
    my_queue2.pop();
  }
}

TEST(queue, modifiers_copy_3) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (std_copy.size()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, modifiers_copy_4) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, modifiers_size_2) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(queue, modifiers_move_1) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_move;
  s21::queue<int> s21_move;
  std_move = std::move(std_queue);
  s21_move = std::move(s21_queue);
  while (!std_move.empty()) {
    EXPECT_EQ(std_move.front(), s21_move.front());
    std_move.pop();
    s21_move.pop();
  }
}

TEST(queue, modifiers_move_2) {
  s21::queue<std::pair<std::string, int>> my_queue1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> my_queue2;
  std::queue<std::pair<std::string, int>> my_queue3;
  my_queue2 = std::move(my_queue1);
  my_queue3.push({"one", 1});
  my_queue3.push({"two", 2});
  my_queue3.push({"three", 3});
  EXPECT_TRUE(my_queue1.empty());
  EXPECT_EQ(my_queue2.size(), my_queue3.size());
  while (my_queue2.size()) {
    EXPECT_EQ(my_queue2.front().first, my_queue3.front().first);
    EXPECT_EQ(my_queue2.front().second, my_queue3.front().second);
    my_queue2.pop();
    my_queue3.pop();
  }
}

TEST(queue, constructor_default) {
  s21::queue<double> queue;
  EXPECT_EQ(queue.size(), 0);
}

TEST(queue, constructor_copy) {
  s21::queue<std::string> queue({"hi", "bye", "ok", "good luck", "shool21"});
  s21::queue<std::string> queue2(queue);
  EXPECT_EQ(queue.size(), queue2.size());
  for (std::size_t i = 0; i < queue.size(); ++i) {
    EXPECT_EQ(queue.front(), queue2.front());
    queue.pop();
    queue2.pop();
  }
}

TEST(queue, constructor_move) {
  s21::queue<double> queue2({-0.75, 7.12, 115.0, -18.7, 0.1});
  s21::queue<double> queue1(std::move(queue2));
  s21::queue<double> queue3({-0.75, 7.12, 115.0, -18.7, 0.1});
  EXPECT_EQ(queue1.size(), queue3.size());
  EXPECT_EQ(queue2.size(), 0);
  for (std::size_t i = 0; i < queue1.size(); ++i) {
    EXPECT_EQ(queue1.front(), queue3.front());
    queue1.pop();
    queue3.pop();
  }
}

TEST(queue, operator_equal) {
  s21::queue<double> queue1({-0.75, 7.12, 115.0, -18, 01});
  s21::queue<double> queue2({-0.75, 7.12, 115.0, -18, 01});
  s21::queue<double> queue3;
  queue3 = std::move(queue1);
  EXPECT_EQ(queue3.size(), queue2.size());
  EXPECT_EQ(queue1.size(), 0);
  for (std::size_t i = 0; i < queue3.size(); ++i) {
    EXPECT_EQ(queue3.front(), queue2.front());
    queue3.pop();
    queue2.pop();
  }
}

TEST(queue, front) {
  s21::queue<float> queue({0.22, -9.55, 7.12});
  s21::queue<float>::const_reference ref = 0.22;
  EXPECT_EQ(queue.front(), ref);
}

TEST(queue, back) {
  s21::queue<float> queue({0.22, -9.55, 7.12});
  s21::queue<float>::const_reference ref = 7.12;
  EXPECT_EQ(queue.back(), ref);
}

TEST(queue, push) {
  s21::queue<int> queue({1, 2, 3, 4, 8});
  EXPECT_EQ(queue.back(), 8);
  queue.push(999);
  EXPECT_EQ(queue.back(), 999);
}

TEST(queue, pop) {
  s21::queue<int> queue({1, 2, 3, 4, 8});
  s21::queue<float>::const_reference ref = 1;
  EXPECT_EQ(queue.front(), ref);
  queue.pop();
  s21::queue<float>::const_reference ref2 = 2;
  EXPECT_EQ(queue.front(), ref2);
}

TEST(queue, empty) {
  s21::queue<double> queue;
  EXPECT_EQ(queue.size(), 0);
}

TEST(queue, not_empty) {
  s21::queue<int> queue({1, 2, 3, 4, 8});
  EXPECT_EQ(queue.size(), 5);
}

TEST(queue, size) {
  s21::queue<int> queue({1, 2, 3, 4, 8});
  EXPECT_EQ(queue.size(), 5);
}

TEST(queue, swap_1) {
  s21::queue<double> queue1({-0.75, 7.12, 115.0, -18, 01});
  s21::queue<double> queue2({1, 2});
  s21::queue<double> queue3({-0.75, 7.12, 115.0, -18, 01});
  queue1.swap(queue2);
  EXPECT_EQ(queue2.size(), queue3.size());
  for (std::size_t i = 0; i < queue3.size(); ++i) {
    EXPECT_EQ(queue3.front(), queue2.front());
    queue3.pop();
    queue2.pop();
  }
}

TEST(queue, swap_2) {
  s21::queue<int> q1{1, 2};
  s21::queue<int> q2{3, 4};
  q1.swap(q2);
  ASSERT_EQ(1, q2.front());
  ASSERT_EQ(3, q1.front());
}

TEST(queue, insert_many_back) {
  s21::queue<std::string> queue;
  queue.insert_many_back("You", "are", "awesome");
  EXPECT_EQ(queue.back(), "awesome");
  EXPECT_EQ(queue.front(), "You");
  EXPECT_EQ(queue.size(), 3);
}