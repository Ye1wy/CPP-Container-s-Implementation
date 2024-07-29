#ifndef CPP_S21_CONTAINERS_LIST_S21_LIST_H
#define CPP_S21_CONTAINERS_LIST_S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

#include "../helper/helper.h"

namespace s21 {

template <typename T>
class list {
  struct Node;

 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  class ListIterator {
    friend class list;

   public:
    ListIterator();
    explicit ListIterator(Node *src);
    ListIterator(const ListIterator &src);
    ListIterator(ListIterator &&other);
    ~ListIterator() = default;

    ListIterator &operator=(const ListIterator &other) noexcept;
    ListIterator &operator=(ListIterator &&other) noexcept;

    ListIterator &operator++() noexcept;
    ListIterator operator++(int) noexcept;
    ListIterator &operator--() noexcept;
    ListIterator operator--(int) noexcept;
    inline bool operator==(const ListIterator &other) noexcept;
    inline bool operator!=(const ListIterator &other) noexcept;
    inline value_type &operator*() const noexcept;

   private:
    Node *it_;
  };

  class ListConstIterator {
    friend class list;

   public:
    ListConstIterator();
    explicit ListConstIterator(Node *src);
    ListConstIterator(const ListIterator &src);
    ListConstIterator(const ListConstIterator &src);
    ListConstIterator(ListConstIterator &&src);
    ~ListConstIterator() = default;

    ListConstIterator &operator=(const ListConstIterator &other) noexcept;
    ListConstIterator &operator=(ListConstIterator &&other) noexcept;

    ListConstIterator &operator++() noexcept;
    ListConstIterator operator++(int) noexcept;
    ListConstIterator &operator--() noexcept;
    ListConstIterator operator--(int) noexcept;
    inline bool operator==(const ListConstIterator &other) noexcept;
    inline bool operator!=(const ListConstIterator &other) noexcept;
    inline const value_type &operator*() const noexcept;

   private:
    Node *it_;
  };

  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();

  list &operator=(const list &l);
  list &operator=(list &&l) noexcept;

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  iterator begin() const noexcept;
  iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_back();
  void pop_front();
  void swap(list &other) noexcept;
  void merge(list &other) noexcept;
  void splice(const_iterator pos, list &other) noexcept;
  void reverse() noexcept;
  void unique();
  void sort() noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  struct Node {
    value_type data_ = T();
    Node *next_;
    Node *prev_;
  };

  size_type size_;
  Node *sentenel_;
  void Insert(iterator pos, iterator pos2) noexcept;
  void Insert(const_iterator pos, iterator pos2) noexcept;
  void SwapItPtr(const_iterator pos, const_iterator pos2) noexcept;
  void Spliter(list &left, list &right) noexcept;
  list &SortedMerge(list &left, list &right) noexcept;
};

template <typename T>
list<T>::list() : size_(0) {
  sentenel_ = new Node;
  sentenel_->data_ = T();
  sentenel_->next_ = sentenel_;
  sentenel_->prev_ = sentenel_;
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const auto &value : items) {
    push_back(value);
  }
}

template <typename T>
list<T>::list(const list &l) : list() {
  for (auto it = l.begin(); it != l.end(); ++it) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(list &&l) noexcept : list() {
  *this = std::move(l);
}

template <typename T>
list<T>::~list() {
  clear();
  delete sentenel_;
}

template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this != &l) {
    clear();

    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
  }

  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    size_ = l.size_;
    sentenel_->next_ = l.sentenel_->next_;
    sentenel_->prev_ = l.sentenel_->prev_;
    l.sentenel_->next_->prev_ = sentenel_;
    l.sentenel_->prev_->next_ = sentenel_;

    l.size_ = 0;
    l.sentenel_->next_ = l.sentenel_->prev_ = l.sentenel_;
  }

  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const noexcept {
  return sentenel_->next_->data_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return sentenel_->prev_->data_;
}

template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }

  sentenel_->next_ = sentenel_;
  sentenel_->prev_ = sentenel_;
  size_ = 0;
}

template <typename T>
bool list<T>::empty() const noexcept {
  return begin() == end();
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(Node) / 2;
}

template <typename T>
typename list<T>::iterator list<T>::begin() const noexcept {
  return ListIterator(sentenel_->next_);
}

template <typename T>
typename list<T>::iterator list<T>::end() const noexcept {
  return ListIterator(sentenel_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const noexcept {
  return ListConstIterator(sentenel_->next_);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const noexcept {
  return ListConstIterator(sentenel_);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *new_node = new Node;
  new_node->data_ = value;

  new_node->prev_ = pos.it_->prev_;
  pos.it_->prev_->next_ = new_node;
  pos.it_->prev_ = new_node;
  new_node->next_ = pos.it_;

  ++size_;
  pos.it_ = new_node;
  return pos;
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node *current = pos.it_;
  pos.it_ = current->prev_;
  pos.it_->next_ = current->next_;
  pos.it_->next_->prev_ = pos.it_;
  delete current;

  --size_;
}

template <typename T>
void list<T>::push_back(const_reference data) {
  insert(end(), data);
}

template <typename T>
void list<T>::push_front(const_reference data) {
  insert(begin(), data);
}

template <typename T>
void list<T>::pop_back() {
  erase(--end());
}

template <typename T>
void list<T>::pop_front() {
  erase(begin());
}

template <typename T>
void list<T>::swap(list &other) noexcept {
  std::swap(sentenel_, other.sentenel_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list<T> &other) noexcept {
  if (begin() == end()) {
    *this = std::move(other);

  } else if (other.begin() != other.end()) {
    iterator it = begin();
    iterator other_it = other.begin();
    iterator save = end();

    while (other_it != other.end() && it != end()) {
      if (*it == *other_it) {
        Insert(it, other_it);
        --other.size_;
        other_it = other.begin();

      } else if (*it >= *other_it) {
        --it;
        Insert(it, other_it);
        --other.size_;
        other_it = other.begin();

      } else {
        ++it;
        other_it = other.begin();
      }
    }

    --it;

    while (other_it != other.end()) {
      Insert(it, other_it);
      other_it = other.begin();
      --other.size_;

      if (it != end()) {
        ++it;
      }
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) noexcept {
  const_iterator umbrella = pos;
  iterator it = other.begin();

  while (it != other.end()) {
    Insert(umbrella, it);
    it = other.begin();
    --other.size_;
  }
}

template <typename T>
void list<T>::reverse() noexcept {
  Node *temp = nullptr;
  Node *next = sentenel_->next_;

  while (next != sentenel_) {
    temp = next->prev_;
    next->prev_ = next->next_;
    next->next_ = temp;
    next = next->prev_;
  }

  if (temp != nullptr) {
    Node *save = sentenel_->next_;
    sentenel_->next_ = sentenel_->prev_;
    sentenel_->prev_ = save;
  }
}

template <typename T>
void list<T>::unique() {
  bool met = false;
  iterator current = begin();
  iterator was;

  while (current != end()) {
    if (!met) {
      was = current;
      met = true;

    } else {
      if (*was == *current) {
        erase(was);
        met = false;

      } else {
        ++was;
      }
    }

    ++current;
  }
}

template <typename T>
void list<T>::sort() noexcept {
  if (begin() == end() || ++begin() == end()) {
    return;
  }

  list left;
  list right;

  Spliter(left, right);

  left.sort();
  right.sort();
  *this = SortedMerge(left, right);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  Node *current = pos.it_;
  iterator it(current);

  (insert(it, std::forward<Args>(args)), ...);

  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  auto it = begin();
  (insert(it, std::forward<Args>(args)), ...);
}

template <typename T>
void list<T>::Insert(iterator pos, iterator pos2) noexcept {
  Node *current = pos.it_;
  Node *other = pos2.it_;

  other->next_->prev_ = other->prev_;
  other->prev_->next_ = other->next_;
  current->next_->prev_ = other;
  other->next_ = current->next_;
  current->next_ = other;
  other->prev_ = current;

  ++size_;
}

template <typename T>
void list<T>::Insert(const_iterator pos, iterator pos2) noexcept {
  iterator it(pos.it_->prev_);
  iterator it_2(pos2.it_);

  Insert(it, it_2);
}

template <typename T>
void list<T>::SwapItPtr(const_iterator pos, const_iterator pos2) noexcept {
  Node save = *pos.it_;

  pos.it_->next_->prev_ = pos2.it_;
  pos.it_->next_ = pos2.it_->next_;
  pos2.it_->next_->prev_ = pos.it_;
  pos2.it_->next_ = save.next_;

  save = *pos2.it_;
  pos2.it_->prev_->next_ = pos.it_;
  pos2.it_->prev_ = pos.it_->prev_;
  pos.it_->prev_->next_ = pos2.it_;
  pos.it_->prev_ = save.prev_;
}

template <typename T>
void list<T>::Spliter(list &left, list &right) noexcept {
  const_iterator it = cbegin();

  if (it != end()) {
    int divide = size() / 2;

    for (int i = 0; it != end(); ++it) {
      if (i < divide) {
        left.push_back(*it);
        ++i;

      } else {
        right.push_back(*it);
      }
    }
  }
}

template <typename T>
typename list<T>::list &list<T>::SortedMerge(list &left, list &right) noexcept {
  if (left.begin() == left.end()) {
    return right;

  } else if (right.begin() == right.end()) {
    return left;
  }

  const_iterator first = left.cbegin();
  const_iterator second = right.cbegin();

  if (*first > *second) {
    SwapItPtr(first, second);
    left.merge(right);

  } else {
    left.merge(right);
  }

  return left;
}

template <typename T>
list<T>::ListIterator::ListIterator() : it_(nullptr) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node *src) : it_(src) {}

template <typename T>
list<T>::ListIterator::ListIterator(const ListIterator &src) : it_(src.it_) {}

template <typename T>
list<T>::ListIterator::ListIterator(ListIterator &&src) : it_(src.it_) {
  src.it_ = nullptr;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator=(
    const ListIterator &other) noexcept {
  it_ = nullptr;
  it_ = other.it_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator=(
    ListIterator &&other) noexcept {
  it_ = other.it_;
  other.it_ = nullptr;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() noexcept {
  it_ = it_->next_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) noexcept {
  list<T>::ListIterator old = *this;
  it_ = it_->next_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator--() noexcept {
  it_ = it_->prev_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) noexcept {
  list<T>::ListIterator old = *this;
  it_ = it_->prev_;
  return *this;
}

template <typename T>
inline bool list<T>::ListIterator::operator==(
    const ListIterator &other) noexcept {
  return it_ == other.it_;
}

template <typename T>
inline bool list<T>::ListIterator::operator!=(
    const ListIterator &other) noexcept {
  return it_ != other.it_;
}

template <typename T>
inline typename list<T>::value_type &list<T>::ListIterator::operator*()
    const noexcept {
  return it_->data_;
}

template <typename T>
list<T>::ListConstIterator::ListConstIterator() : it_(nullptr) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(Node *src) : it_(src) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(const ListConstIterator &src)
    : it_(src.it_) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator &src)
    : ListConstIterator(src.it_){};

template <typename T>
list<T>::ListConstIterator::ListConstIterator(ListConstIterator &&src)
    : it_(src.it_) {
  src.it_ = nullptr;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator=(
    const ListConstIterator &other) noexcept {
  it_ = nullptr;
  it_ = other.it_;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator=(
    ListConstIterator &&other) noexcept {
  it_ = other.it_;
  other.it_ = nullptr;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator &
list<T>::ListConstIterator::operator++() noexcept {
  it_ = it_->next_;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++(
    int) noexcept {
  ListConstIterator tmp(it_);
  it_ = it_->next_;
  return tmp;
}

template <typename T>
typename list<T>::ListConstIterator &
list<T>::ListConstIterator::operator--() noexcept {
  it_ = it_->prev_;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--(
    int) noexcept {
  ListConstIterator tmp(it_);
  it_ = it_->prev_;
  return tmp;
}

template <typename T>
inline bool list<T>::ListConstIterator::operator==(
    const ListConstIterator &other) noexcept {
  return it_ == other.it_;
}

template <typename T>
inline bool list<T>::ListConstIterator::operator!=(
    const ListConstIterator &other) noexcept {
  return it_ != other.it_;
}

template <typename T>
inline const typename list<T>::value_type &
list<T>::ListConstIterator::operator*() const noexcept {
  return it_->data_;
}

template <typename T>
bool operator<(const list<T> &lhs, const list<T> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator<=(const list<T> &lhs, const list<T> &rhs) {
  return s21::lexicog_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator>(const list<T> &lhs, const list<T> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T>
bool operator>=(const list<T> &lhs, const list<T> &rhs) {
  return s21::lexicog_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename T>
bool operator==(const list<T> &lhs, const list<T> &rhs) {
  return s21::is_equal(lhs, rhs);
}

template <typename T>
bool operator!=(const list<T> &lhs, const list<T> &rhs) {
  return !s21::is_equal(lhs, rhs);
}

}  // namespace s21

#endif