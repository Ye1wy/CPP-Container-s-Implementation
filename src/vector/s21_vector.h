#ifndef CPP_S21_CONTAINERS_VECTOR_S21_VECTOR_H
#define CPP_S21_CONTAINERS_VECTOR_S21_VECTOR_H

#include <limits>
#include <sstream>

#include "../helper/helper.h"

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector &operator=(vector &&v);
  vector &operator=(const vector &v);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference front() noexcept;
  reference back() noexcept;
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const;
  size_type size() const;
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

  void capacity_size();

 private:
  T *arr_;
  size_t size_;
  size_t capacity_;
};

template <typename T>
vector<T>::vector() {
  arr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
vector<T>::vector(size_type n) {
  arr_ = new value_type[n]();
  size_ = n;
  capacity_ = n;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  size_ = items.size();
  capacity_ = size_;
  arr_ = new value_type[size_];
  std::copy(items.begin(), items.end(), arr_);
}

template <typename T>
vector<T>::vector(const vector &v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  arr_ = new T[size_];

  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = v.arr_[i];
  }
}

template <typename T>
vector<T>::vector(vector &&v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  arr_ = v.arr_;

  v.size_ = 0;
  v.capacity_ = 0;
  v.arr_ = nullptr;
}

template <typename T>
vector<T>::~vector() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    std::stringstream error_message;
    error_message << "vector::at: pos (whict is " << pos
                  << ") >= size_ (which is " << size_ << ")";
    throw std::out_of_range(error_message.str());
  }

  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    std::stringstream error_message;
    error_message << "vector::at: pos (whict is " << pos
                  << ") >= size_ (which is " << size_ << ")";
    throw std::out_of_range(error_message.str());
  }

  return arr_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return arr_[pos];
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (&v != this) {
    delete[] arr_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    arr_ = v.arr_;

    v.size_ = 0;
    v.capacity_ = 0;
    v.arr_ = nullptr;
  }

  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &v) {
  if (&v != this) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    delete[] arr_;
    arr_ = new T[size_];

    for (size_t i = 0; i < size_; ++i) {
      arr_[i] = v.arr_[i];
    }
  }

  return *this;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > this->max_size()) {
    throw std::length_error(
        "Error: in reserve(size_type size): size > s21::vector::max_size()");
  }

  if (size <= capacity_) {
    return;
  }

  auto arr_new = new value_type[size];

  for (size_t i = 0; i < size_; ++i) {
    arr_new[i] = arr_[i];
  }

  delete[] arr_;
  arr_ = arr_new;
  capacity_ = size;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  auto arr_new = new value_type[size_];

  for (size_t i = 0; i < size_; ++i) {
    arr_new[i] = arr_[i];
  }

  delete[] arr_;
  arr_ = arr_new;
  capacity_ = size_;
}

template <typename T>
bool vector<T>::empty() const {
  return size() == 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return arr_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
  return arr_ + size_;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::length_error(
        "Error: erase(): Accessing an inaccessible area of memory");
  }

  size_type index = pos - begin();
  value_type *arr_new = new value_type[size_ + 1];
  std::copy(begin(), pos, arr_new);
  arr_new[index] = value;
  std::copy(pos, end(), arr_new + index + 1);

  delete[] arr_;
  arr_ = arr_new;
  size_++;

  if (size_ > capacity_) {
    capacity_size();
  }

  return begin() + index;
}

template <typename T>
void vector<T>::capacity_size() {
  if (size_ == 1) {
    capacity_ = 1;

  } else {
    reserve((size_ - 1) * 2);
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return arr_;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos < begin() || pos > end()) {
    throw std::length_error(
        "Error: erase(): Accessing an inaccessible area of memory");
  }

  auto next = pos;
  next++;

  for (; next < end(); ++next, ++pos) {
    std::swap(*next, *pos);
  }

  --size_;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(arr_, other.arr_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    if (capacity_ == 0) {
      reserve(1);

    } else {
      reserve(capacity_ * 2);
    }
  }

  arr_[size_] = value;
  size_ += 1;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::length_error("Error: size == 0, nothing to pop_back");
  }

  size_--;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(size_type);
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}
template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::clear() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
  arr_ = nullptr;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (empty()) {
    throw std::logic_error("Error: Vector is epmty");
  }

  return arr_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (empty()) {
    throw std::logic_error("Error: Vector is epmty");
  }

  return arr_[size_ - 1];
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  std::initializer_list<value_type> items{args...};

  for (auto val : items) {
    push_back(val);
  }
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  std::initializer_list<value_type> items{args...};
  size_t index = pos - begin();
  iterator it = index + begin();
  iterator result;

  for (auto val : items) {
    result = insert(it, val);
    it = result + 1;
  }
  return result;
}

template <typename T>
bool operator<(const vector<T> &lhs, const vector<T> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator>(const vector<T> &lhs, const vector<T> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T>
bool operator>=(const vector<T> &lhs, const vector<T> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
  return s21::is_equal(lhs, rhs);
}

template <typename T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs) {
  return !s21::is_equal(lhs, rhs);
}

}  // namespace s21

#endif
