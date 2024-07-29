#ifndef CPP_S21_CONTAINERS_SET_S21_SET_H
#define CPP_S21_CONTAINERS_SET_S21_SET_H

#include "../RBtree/s21_RBtree.h"
#include "../helper/helper.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename T, class Extract = s21::KeyExtract<T, T>,
          class Compare = s21::Compare<T, T>>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Container = RBTree<T, T, Compare, Extract>;

  set() : set_() {};
  set(std::initializer_list<value_type> const &items) {
    for (const auto &i : items) insert(i);
  };
  set(const set &s) : set_(s.set_) {};
  set(set &&s) : set_{std::move(s.set_)} {};
  ~set() {};

  set &operator=(const set &other) {
    if (this != &other) {
      set_ = other.set_;
    }
    return *this;
  }
  set &operator=(set &&s) {
    if (this != &s) {
      set_ = std::move(s.set_);
    }
    return *this;
  }

  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  iterator begin() { return iterator(set_.begin()); }
  const_iterator begin() const noexcept { return const_iterator(set_.begin()); }
  iterator end() { return iterator(set_.end()); }
  const_iterator end() const noexcept { return const_iterator(set_.end()); }

  const_iterator cbegin() { return const_iterator(set_.cbegin()); }
  const_iterator cend() { return const_iterator(set_.cend()); }

  bool empty() { return set_.empty(); }
  size_type size() { return set_.size(); }
  size_type max_size() { return set_.max_size(); }

  void clear() { set_.clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    return set_.insert_unique(value);
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

  void erase(iterator pos) { set_.erase(pos); }
  void swap(set &other) { set_.swap(other.set_); }
  void merge(set &other) { set_.merge_unique(other.set_); }

  iterator find(const T &key) { return set_.search(key); }
  bool contains(const T &key) { return set_.contains(key); }

 private:
  Container set_;
};

template <typename T, class Compare, class Extract>
bool operator>(const set<T, Compare, Extract> &lhs,
               const set<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, class Compare, class Extract>
bool operator>=(const set<T, Compare, Extract> &lhs,
                const set<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, class Compare, class Extract>
bool operator<(const set<T, Compare, Extract> &lhs,
               const set<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, class Compare, class Extract>
bool operator<=(const set<T, Compare, Extract> &lhs,
                const set<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, class Compare, class Extract>
bool operator==(const set<T, Compare, Extract> &lhs,
                const set<T, Compare, Extract> &rhs) {
  return s21::is_equal(lhs, rhs);
}

template <typename T, class Compare, class Extract>
bool operator!=(const set<T, Compare, Extract> &lhs,
                const set<T, Compare, Extract> &rhs) {
  return !s21::is_equal(lhs, rhs);
}

}  // namespace s21

#endif