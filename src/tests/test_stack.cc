#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

TEST(stack, constructors_1) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack, constructors_initializer_list_1) {
  s21::stack<int> s21_stack{1, 2, 4};
  EXPECT_EQ(s21_stack.size(), 3);
  EXPECT_EQ(s21_stack.top(), 4);
}

TEST(stack, constructors_initializer_list_2) {
  s21::stack<unsigned int> s1{1, 2, 3, 4};
  ASSERT_EQ(s1.size(), 4u);
  ASSERT_EQ(s1.top(), 4u);
  s21::stack<std::string> s2{"morning", "village", "people"};
  ASSERT_EQ(s2.size(), 3u);
  ASSERT_EQ(s2.top(), "people");
}

TEST(stack, constructors_initializer_list_3) {
  s21::stack<std::pair<std::string, int>> s21_s1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::stack<std::pair<std::string, int>> std_s2;
  std_s2.push({"one", 1});
  std_s2.push({"two", 2});
  std_s2.push({"three", 3});
  EXPECT_EQ(s21_s1.empty(), std_s2.empty());
  EXPECT_EQ(s21_s1.size(), std_s2.size());
  while (!s21_s1.empty()) {
    EXPECT_EQ(s21_s1.top(), std_s2.top());
    s21_s1.pop();
    std_s2.pop();
  }
}

TEST(stack, constructors_initializer_list_4) {
  std::initializer_list<int> b;
  s21::stack<int> s21_stack{b};
  std::stack<int> std_stack{b};
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(stack, constructors_2) {
  s21::stack<std::pair<std::string, int>> s21_s;
  std::stack<std::pair<std::string, int>> std_s;
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
  s21_s.push({"one", 1});
  std_s.push({"one", 1});
  EXPECT_FALSE(s21_s.empty());
  EXPECT_FALSE(std_s.empty());
  s21_s.pop();
  std_s.pop();
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
}

TEST(stack, constructor_copy_1) {
  std::initializer_list<int> test = {1, 2, 3};

  s21::stack<int> s21_stack{test};
  s21::stack<int> s21_stack_copy{s21_stack};
  std::stack<int> std_stack{test};
  std::stack<int> std_stack_copy{std_stack};
  EXPECT_EQ(s21_stack_copy.size(), std_stack_copy.size());
  EXPECT_EQ(s21_stack_copy.top(), std_stack_copy.top());
}

TEST(stack, constructor_move_1) {
  std::initializer_list<int> test = {1, 2, 3};

  s21::stack<int> s21_stack{test};
  s21::stack<int> s21_stack_move{s21_stack};
  std::stack<int> std_stack{test};
  std::stack<int> std_stack_move{std_stack};
  EXPECT_EQ(s21_stack_move.size(), std_stack_move.size());
  EXPECT_EQ(s21_stack_move.top(), std_stack_move.top());
}

TEST(stack, opertator_move_1) {
  std::initializer_list<int> test_1 = {4, 5, 6, 7};
  std::initializer_list<int> test_2 = {1, 2, 3};

  s21::stack<int> s21_stack{test_1};
  s21::stack<int> s21_stack_move{test_2};
  s21_stack = std::move(s21_stack_move);

  std::stack<int> std_stack{test_1};
  std::stack<int> std_stack_move{test_2};
  std_stack = std::move(std_stack_move);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack, top_1) {
  std::initializer_list<int> test = {4, 5, 6, 7};

  s21::stack<int> s21_stack{test};

  std::stack<int> std_stack{test};

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(stack, top_2) {
  s21::stack<std::string> stack{"hi", "bye", "25"};
  EXPECT_EQ(stack.top(), "25");
}

TEST(stack, swap_1) {
  std::initializer_list<int> test = {1, 2, 3};
  std::initializer_list<int> test_2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{test};
  s21::stack<int> s21_stack_swap{test_2};
  std::stack<int> std_stack{test};
  std::stack<int> std_stack_swap{test_2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}

TEST(stackTest, swap_2) {
  std::initializer_list<int> test = {4, 5, 6, 7};
  std::initializer_list<int> test_2 = {4, 5, 6, 7};

  s21::stack<int> s21_stack{test};
  s21::stack<int> s21_stack_swap{test_2};
  std::stack<int> std_stack{test};
  std::stack<int> std_stack_swap{test_2};
  s21_stack.swap(s21_stack_swap);
  std_stack.swap(std_stack_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());

  EXPECT_EQ(s21_stack_swap.size(), std_stack_swap.size());
  EXPECT_EQ(s21_stack_swap.top(), std_stack_swap.top());
}
TEST(stack, empty) {
  s21::stack<float> stack;
  EXPECT_EQ(stack.size(), 0);
}

TEST(stack, not_empty) {
  s21::stack<float> stack({1, 2, 3, 4, 8});
  EXPECT_EQ(stack.size(), 5);
}

TEST(stack, size) {
  s21::stack<int> stack({1, 2, 3, 4, 8});
  EXPECT_EQ(stack.size(), 5);
}

TEST(stack, push) {
  s21::stack<std::string> stack({"hi", "hello"});
  EXPECT_EQ(stack.top(), "hello");
  stack.push("school");
  EXPECT_EQ(stack.top(), "school");
}

TEST(stack, pop) {
  s21::stack<int> stack({1, 2, 3, 4, 8});
  EXPECT_EQ(stack.top(), 8);
  stack.pop();
  EXPECT_EQ(stack.top(), 4);
}

TEST(stack, insert_many_back) {
  s21::stack<int> stack;
  stack.insert_many_front(1, 2, 3);
  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(stack.size(), 3);
}