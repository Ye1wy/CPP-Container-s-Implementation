#ifndef CPP_S21_CONTAINERS_STACK_S21_STACK_H
#define CPP_S21_CONTAINERS_STACK_S21_STACK_H

#include "../helper/helper.h"
#include "../list/s21_list.h"

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Container = s21::list<T>;

  stack() : stack_() {};
  stack(std::initializer_list<value_type> const &items) : stack_{items} {};
  stack(const stack &s) : stack_(s.stack_) {};
  stack(stack &&s) : stack_{std::move(s.stack_)} {};
  ~stack() {};

  stack &operator=(const stack &other) {
    if (this != &other) {
      stack_ = other.stack_;
    }
    return *this;
  }

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      stack_ = std::move(s.stack_);
    }
    return *this;
  }

  const_reference top() const { return stack_.back(); }

  bool empty() const noexcept { return stack_.empty(); }
  size_type size() const noexcept { return stack_.size(); }

  void push(const_reference value) { stack_.push_back(value); }
  void pop() { stack_.pop_back(); }
  void swap(stack &other) { stack_.swap(other.stack_); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    std::initializer_list<T> items{std::forward<Args>(args)...};

    for (const auto &value : items) {
      stack_.push_front(value);
    }
  }

  template <typename U>
  friend bool operator>(const stack<U> &lhs, const stack<U> &rhs);
  template <typename U>
  friend bool operator<(const stack<U> &lhs, const stack<U> &rhs);
  template <typename U>
  friend bool operator<=(const stack<U> &lhs, const stack<U> &rhs);
  template <typename U>
  friend bool operator>=(const stack<U> &lhs, const stack<U> &rhs);
  template <typename U>
  friend bool operator==(const stack<U> &lhs, const stack<U> &rhs);
  template <typename U>
  friend bool operator!=(const stack<U> &lhs, const stack<U> &rhs);

 private:
  Container stack_;
};

template <typename T>
bool operator>(const stack<T> &lhs, const stack<T> &rhs) {
  return lhs.stack_ > rhs.stack_;
}

template <typename T>
bool operator<(const stack<T> &lhs, const stack<T> &rhs) {
  return rhs > lhs;
}

template <typename T>
bool operator<=(const stack<T> &lhs, const stack<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
bool operator>=(const stack<T> &lhs, const stack<T> &rhs) {
  return !(lhs < rhs);
}

template <typename T>
bool operator==(const stack<T> &lhs, const stack<T> &rhs) {
  return lhs.stack_ == rhs.stack_;
}

template <typename T>
bool operator!=(const stack<T> &lhs, const stack<T> &rhs) {
  return !(lhs == rhs);
}

}  // namespace s21

#endif