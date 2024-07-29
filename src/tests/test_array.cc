#include <gtest/gtest.h>

#include <array>

#include "../s21_containersplus.h"

TEST(test_array, constructors_1) {
  s21::array<int, 3> arr{};
  std::array<int, 3> arr2{};
  ASSERT_EQ(arr.size(), arr2.size());
}

TEST(test_array, constructors_2) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr2 = {2, 1, 3};
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arr[i], arr2[i]);
  }
}

TEST(test_array, constructors_copy_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  s21::array<int, 3> arr2(arr);
  for (size_t i = 0; i < arr.size(); ++i) {
    ASSERT_EQ(arr[i], arr2[i]);
  }
}

TEST(test_array, constructors_move_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  s21::array<int, 3> arr2(std::move(arr));
  ASSERT_EQ(arr2[0], 2);
  ASSERT_EQ(arr2[1], 1);
  ASSERT_EQ(arr2[2], 3);
}

TEST(test_array, modifiers_move_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  s21::array<int, 3> arr2 = {3, 2, 2};
  arr = std::move(arr2);
  ASSERT_EQ(arr[0], 3);
  ASSERT_EQ(arr[1], 2);
  ASSERT_EQ(arr[2], 2);
}
TEST(test_array, modifiers_front_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr2 = {2, 1, 3};
  int num = arr.front();
  int num2 = arr2.front();
  ASSERT_EQ(num, num2);
}

TEST(test_array, modifiers_back_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr2 = {2, 1, 3};
  int num = arr.back();
  int num2 = arr2.back();
  ASSERT_EQ(num, num2);
}

TEST(test_array, modifiers_data_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr2 = {2, 1, 3};
  int *num = arr.data();
  int *num2 = arr2.data();
  ASSERT_EQ(*num, *num2);
}

TEST(test_array, modifiers_data_2) {
  s21::array<int, 5> v = {1, 2, 3, 4, 5};
  int *dataPtr = v.data();
  ASSERT_EQ(*dataPtr, 1);
  *dataPtr = 10;
  ASSERT_EQ(v[0], 10);
}

TEST(test_array, modifiers_begin_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr2 = {2, 1, 3};
  s21::array<int, 3>::iterator it;
  std::array<int, 3>::iterator it2;
  it = arr.begin();
  it2 = arr2.begin();
  ASSERT_EQ(*it, *it2);
}

TEST(test_array, modifiers_end_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr2 = {2, 1, 3};
  s21::array<int, 3>::iterator it;
  std::array<int, 3>::iterator it2;
  it = arr.end() - 1;
  it2 = arr2.end() - 1;
  ASSERT_EQ(*it, *it2);
}

TEST(test_array, modifiers_empty_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr_orig = {2, 1, 3};
  ASSERT_FALSE(arr.empty());
  ASSERT_FALSE(arr_orig.empty());
  s21::array<int, 0> arr2;
  std::array<int, 0> arr2_orig;
  ASSERT_TRUE(arr2_orig.empty());
  ASSERT_TRUE(arr2.empty());
}

TEST(test_array, modifiers_max_size_1) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr_orig = {2, 1, 3};
  ASSERT_EQ(arr.max_size(), arr_orig.max_size());
}

TEST(test_array, modifiers_swap_1) {
  s21::array<int, 3> arr = {3, 2, 2};
  s21::array<int, 3> arr1 = {2, 1, 3};
  std::array<int, 3> arr_orig = {3, 2, 2};
  std::array<int, 3> arr1_orig = {2, 1, 3};
  arr.swap(arr1);
  arr_orig.swap(arr1_orig);
  for (size_t i = 0; i < arr.size(); i++) {
    ASSERT_EQ(arr[i], arr_orig[i]);
  }
  ASSERT_EQ(arr.size(), arr_orig.size());
}

TEST(test_array, fill) {
  s21::array<int, 3> arr = {3, 2, 2};
  std::array<int, 3> arr_orig = {3, 2, 2};
  arr.fill(1);
  arr_orig.fill(1);
  for (size_t i = 0; i < arr.size(); i++) {
    ASSERT_EQ(arr[i], arr_orig[i]);
  }
}

TEST(test_array, fill_2) {
  s21::array<int, 3> arr;
  std::array<int, 3> arr_orig;
  arr.fill(1);
  arr_orig.fill(1);
  for (size_t i = 0; i < arr.size(); i++) {
    ASSERT_EQ(arr[i], arr_orig[i]);
  }
}

TEST(test_array, at) {
  s21::array<int, 3> arr = {2, 1, 3};
  std::array<int, 3> arr_orig = {2, 1, 3};
  int r1 = arr.at(2);
  int r2 = arr_orig.at(2);
  ASSERT_EQ(r1, r2);
}

TEST(test_array, operator_access) {
  s21::array<int, 3> arr = {2, 1, 3};
  ASSERT_EQ(arr[0], 2);
}

TEST(test_array, constructor_test_01) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
}

TEST(test_array, constructor_test_02) {
  s21::array<double, 3> arr{1.01, 2.02, 3.03};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.at(1), 2.02);
}

TEST(test_array, constructor_test_03) {
  s21::array<double, 3> arr{1.01, 2.02, 3.03};
  s21::array<double, 3> arr1(arr);
  EXPECT_EQ(arr1.size(), 3);
  s21::array<double, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2.size(), 3);
  s21::array<double, 3> arr3;
  arr3 = std::move(arr2);
  EXPECT_EQ(arr3.size(), 3);
}

TEST(test_array, front_back_oper_test_01) {
  s21::array<int, 3> arr;
  EXPECT_EQ(arr.end() - arr.begin(), 3);
}

TEST(test_array, front_back_oper_test_02) {
  s21::array<double, 3> arr{1.01, 2.02, 3.03};
  EXPECT_EQ(arr.front(), 1.01);
  EXPECT_EQ(arr.back(), 3.03);
}

TEST(test_array, bool_empty_case_test_01) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
  s21::array<int, 1> arr1;
  EXPECT_FALSE(arr1.empty());
}

TEST(test_array, max_size_test_01) {
  s21::array<int, 0> arr;
  EXPECT_EQ(arr.max_size(), 0);
  s21::array<int, 1> arr1;
  EXPECT_EQ(arr1.max_size(), 1);
}

TEST(test_array, at_test_01) {
  s21::array<double, 5> arr{1.01, 1.02, 1.03, 1.04, 1.05};
  EXPECT_EQ(arr.at(1), 1.02);
  EXPECT_EQ(arr[4], 1.05);
  // EXPECT_THROW(arr.at(7), std::out_of_range);  //  leaks
}

TEST(test_array, swap_test_01) {
  s21::array<double, 5> arr{1.01, 1.02, 1.03, 1.04, 1.05};
  s21::array<double, 5> arr1{5.05, 4.04, 3.03, 2.02, 1.01};
  arr.swap(arr1);
  EXPECT_EQ(arr.at(1), 4.04);
  EXPECT_EQ(arr1.at(1), 1.02);
}

TEST(test_array, fill_test_01) {
  s21::array<double, 5> arr{1.01, 1.02, 1.03, 1.04, 1.05};
  arr.fill(111.11);
  for (auto i : arr) {
    EXPECT_EQ(i, 111.11);
  }
}

TEST(test_array, fill_test_02) {
  s21::array<double, 5> arr{1.01, 1.02, 1.03, 1.04, 1.05};
  s21::array<double, 5> arr_result{1, 3, 5, 1.04, 1.05};
  arr.fill({1, 3, 5});
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], arr_result[i]);
  }
}

TEST(test_array, data_test_01) {
  s21::array<double, 5> arr{1.01, 1.02, 1.03, 1.04, 1.05};
  EXPECT_EQ(arr.data(), arr.begin());
}

TEST(test_array, data_test_02) {
  s21::array<double, 5> arr{1.01, 2.02, 3.03, 4.04, 5.05};
  EXPECT_EQ(arr.data()[3], arr.at(3));
}