#ifndef CPP_S21_CONTAINERS_MULTISET_S21_MULTISET_H
#define CPP_S21_CONTAINERS_MULTISET_S21_MULTISET_H

#include <initializer_list>

#include "../RBtree/s21_RBtree.h"
#include "../helper/helper.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename T, class Extract = s21::KeyExtract<T, T>,
          class Compare = s21::Compare<T, T>>
class multiset {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Container = RBTree<T, T, Compare, Extract>;

  multiset() : multiset_() {};
  multiset(std::initializer_list<value_type> const &items) {
    for (const auto &i : items) insert(i);
  };
  multiset(const multiset &ms) : multiset_(ms.multiset_) {};
  multiset(multiset &&ms) : multiset_{std::move(ms.multiset_)} {};
  ~multiset() {};

  multiset &operator=(multiset &&ms) {
    if (this != &ms) {
      multiset_ = std::move(ms.multiset_);
    }
    return *this;
  }

  multiset &operator=(const multiset &ms) {
    if (this != &ms) {
      multiset_ = ms.multiset_;
    }
    return *this;
  }
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  iterator begin() { return iterator(multiset_.begin()); }
  const_iterator begin() const noexcept {
    return const_iterator(multiset_.begin());
  }
  iterator end() { return iterator(multiset_.end()); }
  const_iterator end() const noexcept {
    return const_iterator(multiset_.end());
  }

  const_iterator cbegin() { return const_iterator(multiset_.cbegin()); }
  const_iterator cend() { return const_iterator(multiset_.cend()); }

  bool empty() { return multiset_.empty(); }
  size_type size() { return multiset_.size(); }
  size_type max_size() { return multiset_.max_size(); }

  void clear() { multiset_.clear(); }

  iterator insert(const value_type &value) {
    return multiset_.insert_equal(value);
  }

  void erase(iterator pos) { multiset_.erase(pos); }
  void swap(multiset &other) { multiset_.swap(other.multiset_); }
  void merge(multiset &other) { multiset_.merge_unique(other.multiset_); }

  size_type count(const T &key) {
    return multiset_.count(key);
  };  // количество определенных ключей
  iterator find(const T &key) {
    return multiset_.search(key);
  };  // находит элемент с определенным ключом
  bool contains(const T &key) {
    return multiset_.contains(key);
  };  // проверяет, содержит ли контейнер элемент с определенным ключом
  std::pair<iterator, iterator> equal_range(const T &key) {
    return multiset_.equal_range(key);
  };  // возвращает диапазон элементов, соответствующих определенному ключу
  iterator lower_bound(const T &key) {
    return multiset_.lower_bound(key);
  };  // возвращает итератор к первому элементу не меньше заданного ключа
  iterator upper_bound(const T &key) {
    return multiset_.upper_bound(key);
  };  // возвращает итератор к первому элементу, большему, чем заданный ключ

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    (..., (results.push_back(
              std::make_pair(insert(std::forward<Args>(args)), true))));
    return results;
  }

 private:
  Container multiset_;
};

template <typename T, class Compare, class Extract>
bool operator>(const multiset<T, Compare, Extract> &lhs,
               const multiset<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, class Compare, class Extract>
bool operator>=(const multiset<T, Compare, Extract> &lhs,
                const multiset<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T, class Compare, class Extract>
bool operator<(const multiset<T, Compare, Extract> &lhs,
               const multiset<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, class Compare, class Extract>
bool operator<=(const multiset<T, Compare, Extract> &lhs,
                const multiset<T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, class Compare, class Extract>
bool operator==(const multiset<T, Compare, Extract> &lhs,
                const multiset<T, Compare, Extract> &rhs) {
  return s21::is_equal(lhs, rhs);
}

template <typename T, class Compare, class Extract>
bool operator!=(const multiset<T, Compare, Extract> &lhs,
                const multiset<T, Compare, Extract> &rhs) {
  return !s21::is_equal(lhs, rhs);
}

}  // namespace s21

#endif