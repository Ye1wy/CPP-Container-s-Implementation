#ifndef CPP_S21_CONTAINERS_QUEUE_S21_QUEUE_H
#define CPP_S21_CONTAINERS_QUEUE_S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using Container = s21::list<T>;

  queue() : queue_() {}
  queue(std::initializer_list<value_type> const &items) : queue_{items} {}
  queue(const queue &q) : queue_(q.queue_) {}
  queue(queue &&q) noexcept : queue_{std::move(q.queue_)} {}
  ~queue() = default;

  queue &operator=(const queue &other) {
    if (this != &other) {
      queue_ = other.queue_;
    }
    return *this;
  }

  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      queue_ = std::move(q.queue_);
    }
    return *this;
  }

  const_reference front() const { return queue_.front(); }
  const_reference back() const { return queue_.back(); }

  bool empty() const noexcept { return queue_.empty(); }
  size_type size() const noexcept { return queue_.size(); }

  void push(const_reference value) { queue_.push_back(value); }
  void pop() { queue_.pop_front(); }
  void swap(queue &other) noexcept { queue_.swap(other.queue_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (queue_.push_back(std::forward<Args>(args)), ...);
  }

  template <typename U>
  friend bool operator>(const queue<U> &lhs, const queue<U> &rhs);
  template <typename U>
  friend bool operator<(const queue<U> &lhs, const queue<U> &rhs);
  template <typename U>
  friend bool operator<=(const queue<U> &lhs, const queue<U> &rhs);
  template <typename U>
  friend bool operator>=(const queue<U> &lhs, const queue<U> &rhs);
  template <typename U>
  friend bool operator==(const queue<U> &lhs, const queue<U> &rhs);
  template <typename U>
  friend bool operator!=(const queue<U> &lhs, const queue<U> &rhs);

 private:
  Container queue_;
};

template <typename T>
bool operator>(const queue<T> &lhs, const queue<T> &rhs) {
  return lhs.queue_ > rhs.queue_;
}

template <typename T>
bool operator<(const queue<T> &lhs, const queue<T> &rhs) {
  return rhs > lhs;
}

template <typename T>
bool operator<=(const queue<T> &lhs, const queue<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
bool operator>=(const queue<T> &lhs, const queue<T> &rhs) {
  return !(lhs < rhs);
}

template <typename T>
bool operator==(const queue<T> &lhs, const queue<T> &rhs) {
  return lhs.queue_ == rhs.queue_;
}

template <typename T>
bool operator!=(const queue<T> &lhs, const queue<T> &rhs) {
  return !(lhs == rhs);
}

}  // namespace s21

#endif  // CPP_S21_CONTAINERS_SRC_S21_QUEUE_H
