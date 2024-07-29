#ifndef CPP_S21_CONTAINERS_MAP_S21_MAP_H
#define CPP_S21_CONTAINERS_MAP_S21_MAP_H

#include <initializer_list>

#include "../RBtree/s21_RBtree.h"
#include "../helper/helper.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename K, typename T, class Compare = s21::Compare<K, T>,
          class Extract = s21::KeyExtract<K, T>>
class map {
 public:
  using key_type = K;
  using mapped_value = T;
  using value_type = std::pair<K, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Container = s21::RBTree<K, std::pair<K, T>, Compare, Extract>;
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m) noexcept;
  ~map();

  map &operator=(const map &m);
  map &operator=(map &&m) noexcept;

  T &at(const key_type &k) const;
  T &operator[](const key_type &k);

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;

  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_value &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_value &obj);
  iterator erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const key_type &key) const noexcept;

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  Container map_;
};

template <typename K, typename T, class Compare, class Extract>
map<K, T, Compare, Extract>::map() : map_(){};

template <typename K, typename T, class Compare, class Extract>
map<K, T, Compare, Extract>::map(std::initializer_list<value_type> const &items)
    : map() {
  for (auto it : items) {
    insert(it);
  }
}

template <typename K, typename T, class Compare, class Extract>
map<K, T, Compare, Extract>::map(const map &m) : map_(m.map_) {}

template <typename K, typename T, class Compare, class Extract>
map<K, T, Compare, Extract>::map(map &&m) noexcept : map_(std::move(m.map_)) {}

template <typename K, typename T, class Compare, class Extract>
map<K, T, Compare, Extract>::~map(){};

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::map &
map<K, T, Compare, Extract>::operator=(const map &m) {
  map_ = m.map_;
  return *this;
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::map &
map<K, T, Compare, Extract>::operator=(map &&m) noexcept {
  map_ = std::move(m.map_);
  return *this;
}

template <typename K, typename T, class Compare, class Extract>
T &map<K, T, Compare, Extract>::at(const key_type &k) const {
  iterator finder = map_.search(k);

  if (finder == end()) {
    throw std::out_of_range("That bulshit is not contain in me!");
  }

  return finder->second;
}

template <typename K, typename T, class Compare, class Extract>
T &map<K, T, Compare, Extract>::operator[](const key_type &k) {
  iterator creep = insert({k, mapped_value()}).first;

  return creep->second;
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::iterator
map<K, T, Compare, Extract>::begin() noexcept {
  return map_.begin();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::const_iterator
map<K, T, Compare, Extract>::begin() const noexcept {
  return map_.begin();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::const_iterator
map<K, T, Compare, Extract>::cbegin() const noexcept {
  return map_.cbegin();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::iterator
map<K, T, Compare, Extract>::end() noexcept {
  return map_.end();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::const_iterator
map<K, T, Compare, Extract>::end() const noexcept {
  return map_.end();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::const_iterator
map<K, T, Compare, Extract>::cend() const noexcept {
  return map_.cend();
}

template <typename K, typename T, class Compare, class Extract>
bool map<K, T, Compare, Extract>::empty() const noexcept {
  return map_.empty();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::size_type
map<K, T, Compare, Extract>::size() const noexcept {
  return map_.size();
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::size_type
map<K, T, Compare, Extract>::max_size() const {
  return map_.max_size();
}

template <typename K, typename T, class Compare, class Extract>
void map<K, T, Compare, Extract>::clear() {
  map_.clear();
}
template <typename K, typename T, class Compare, class Extract>
std::pair<typename map<K, T, Compare, Extract>::iterator, bool>
map<K, T, Compare, Extract>::insert(const value_type &value) {
  return map_.insert_unique(value);
}

template <typename K, typename T, class Compare, class Extract>
std::pair<typename map<K, T, Compare, Extract>::iterator, bool>
map<K, T, Compare, Extract>::insert(const key_type &key,
                                    const mapped_value &obj) {
  iterator inserter = map_.search(key);

  if (inserter == end()) {
    return std::pair<iterator, bool>(inserter, false);
  }

  inserter->second = obj;
  return std::pair<iterator, bool>(inserter, true);
}

template <typename K, typename T, class Compare, class Extract>
std::pair<typename map<K, T, Compare, Extract>::iterator, bool>
map<K, T, Compare, Extract>::insert_or_assign(const key_type &key,
                                              const mapped_value &obj) {
  std::pair<iterator, bool> creep = insert({key, obj});

  if (creep.second) {
    return creep;
  }

  creep.first->second = obj;
  creep.second = false;
  return creep;
}

template <typename K, typename T, class Compare, class Extract>
typename map<K, T, Compare, Extract>::iterator
map<K, T, Compare, Extract>::erase(iterator pos) {
  return iterator(map_.erase(pos));
}

template <typename K, typename T, class Compare, class Extract>
void map<K, T, Compare, Extract>::swap(map &other) {
  map_.swap(other.map_);
}

template <typename K, typename T, class Compare, class Extract>
void map<K, T, Compare, Extract>::merge(map &other) {
  map_.merge_unique(other.map_);
}

template <typename K, typename T, class Compare, class Extract>
bool map<K, T, Compare, Extract>::contains(const key_type &key) const noexcept {
  return map_.contains(key);
}

template <typename K, typename T, class Compare, class Extract>
template <typename... Args>
s21::vector<std::pair<typename map<K, T, Compare, Extract>::iterator, bool>>
s21::map<K, T, Compare, Extract>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> res;

  (res.push_back(insert(std::forward<Args>(args))), ...);

  return res;
}

template <typename K, typename T, class Compare, class Extract>
bool operator>(const map<K, T, Compare, Extract> &lhs,
               const map<K, T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename K, typename T, class Compare, class Extract>
bool operator>=(const map<K, T, Compare, Extract> &lhs,
                const map<K, T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename K, typename T, class Compare, class Extract>
bool operator<(const map<K, T, Compare, Extract> &lhs,
               const map<K, T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename K, typename T, class Compare, class Extract>
bool operator<=(const map<K, T, Compare, Extract> &lhs,
                const map<K, T, Compare, Extract> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename K, typename T, class Compare, class Extract>
bool operator==(const map<K, T, Compare, Extract> &lhs,
                const map<K, T, Compare, Extract> &rhs) {
  return s21::is_equal(lhs, rhs);
}

template <typename K, typename T, class Compare, class Extract>
bool operator!=(const map<K, T, Compare, Extract> &lhs,
                const map<K, T, Compare, Extract> &rhs) {
  return !s21::is_equal(lhs, rhs);
}

}  // namespace s21

#endif