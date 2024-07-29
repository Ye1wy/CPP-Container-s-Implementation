#ifndef CPP_S21_CONTAINERS_ARRAY_S21_ARRAY_H
#define CPP_S21_CONTAINERS_ARRAY_S21_ARRAY_H

#include <initializer_list>
#include <limits>
#include <sstream>

#include "../helper/helper.h"

namespace s21 {
template <class T, std::size_t N>
struct array {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  array() = default;
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array() = default;

  array &operator=(array &&a) noexcept;
  array &operator=(const array &a);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const noexcept;
  const_reference back() const noexcept;

  size_type size();
  size_type size() const;
  size_type max_size();
  bool empty() const;

  const_iterator data() const noexcept;
  iterator data() noexcept;
  const_iterator begin() const noexcept;
  iterator begin() noexcept;
  const_iterator end() const noexcept;
  iterator end() noexcept;

  void swap(array &other) noexcept;
  void fill(const_reference value);
  void fill(std::initializer_list<value_type> values);

  value_type Data[N];
};

template <class T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), Data);
}

template <class T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.begin(), a.end(), Data);
}

template <class T, std::size_t N>
array<T, N>::array(array &&a) {
  std::move(a.begin(), a.end(), Data);
}

template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(const array &a) {
  if (this != &a) {
    std::copy(a.begin(), a.end(), Data);
  }
  return *this;
}

template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) noexcept {
  if (this != &a) {
    std::copy(a.begin(), a.end(), Data);
  }
  return *this;
}

template <class T, std::size_t N>
void array<T, N>::swap(array &other) noexcept {
  std::swap_ranges(begin(), end(), other.begin());
}

template <class T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(begin(), end(), value);
}

template <class T, std::size_t N>
void array<T, N>::fill(std::initializer_list<T> values) {
  auto it = begin();
  for (const auto &value : values) {
    if (it == end()) break;
    *it++ = value;
  }
}

template <class T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return Data;
}
template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return Data;
}

template <class T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return Data + N;
}

template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return Data + N;
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return Data[pos];
}

template <class T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return Data[pos];
}

template <class T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    std::stringstream error_message;
    error_message << "array::at: pos (whict is " << pos << ") >= N (which is "
                  << N << ")";
    throw std::out_of_range(error_message.str());
  }
  return Data[pos];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    std::stringstream error_message;
    error_message << "array::at: pos (whict is " << pos << ") >= N (which is "
                  << N << ")";
    throw std::out_of_range(error_message.str());
  }
  return Data[pos];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const noexcept {
  return Data[0];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const noexcept {
  return Data[N - 1];
}

template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return Data;
}

template <class T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return Data;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return N;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <class T, std::size_t N>
bool array<T, N>::empty() const {
  return size() == 0;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

template <typename T, std::size_t N>
bool operator<(const array<T, N> &lhs, const array<T, N> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, std::size_t N>
bool operator<=(const array<T, N> &lhs, const array<T, N> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, std::size_t N>
bool operator>(const array<T, N> &lhs, const array<T, N> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, std::size_t N>
bool operator>=(const array<T, N> &lhs, const array<T, N> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, std::size_t N>
bool operator==(const array<T, N> &lhs, const array<T, N> &rhs) {
  return s21::is_equal(lhs, rhs);
}

template <typename T, std::size_t N>
bool operator!=(const array<T, N> &lhs, const array<T, N> &rhs) {
  return !s21::is_equal(lhs, rhs);
}
}  // namespace s21

#endif