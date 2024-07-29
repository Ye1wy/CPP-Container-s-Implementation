#ifndef CPP_S21_CONTAINERS_RBTREE_S21_RB_TREE_H
#define CPP_S21_CONTAINERS_RBTREE_S21_RB_TREE_H

#include <cstddef>
#include <limits>
#include <utility>

namespace s21 {
template <typename K, typename T, class Compare, class Extracter>
class RBTree {
  struct Node;

 public:
  class RBIterator;
  class RBConstIterator;

  using key_type = K;
  using value_type = T;
  using size_type = size_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = RBIterator;
  using const_iterator = RBConstIterator;
  using node_type = Node;

  class RBIterator {
    friend class RBTree;

   public:
    RBIterator() noexcept;
    explicit RBIterator(node_type *src);
    RBIterator(const iterator &src);
    RBIterator(iterator &&other) noexcept;
    ~RBIterator() = default;

    iterator &operator=(const iterator &other);
    iterator &operator=(iterator &&other) noexcept;

    iterator &operator++() noexcept;
    iterator operator++(int) noexcept;
    iterator &operator--() noexcept;
    iterator operator--(int) noexcept;
    reference operator*();
    pointer operator->();
    inline bool operator==(const iterator &other) const noexcept;
    inline bool operator!=(const iterator &other) const noexcept;

   private:
    node_type *it_;

    node_type *GetMax(node_type *enter) noexcept;
    node_type *GetMin(node_type *enter) noexcept;
  };

  class RBConstIterator : public RBIterator {
    friend class RBTree;

   public:
    RBConstIterator() noexcept;
    explicit RBConstIterator(Node *src);
    RBConstIterator(const iterator &other);
    RBConstIterator(const const_iterator &other);
    RBConstIterator(const_iterator &&other);

    reference operator*() const;
    pointer operator->() const;
  };

  RBTree();
  RBTree(const RBTree &other);
  RBTree(RBTree &&other) noexcept;
  ~RBTree();

  RBTree &operator=(const RBTree &other);
  RBTree &operator=(RBTree &&other) noexcept;

  inline iterator begin() noexcept;
  inline const_iterator begin() const noexcept;
  inline const_iterator cbegin() const noexcept;
  inline iterator end() noexcept;
  inline const_iterator end() const noexcept;
  inline const_iterator cend() const noexcept;

  inline bool empty() const noexcept;
  inline size_type size() const noexcept;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert_unique(const value_type &val);
  iterator insert_equal(const value_type &val);
  iterator search(const key_type target) const noexcept;
  iterator erase(iterator pos);
  void swap(RBTree &other);
  void merge_unique(RBTree &other);
  void merge_equal(RBTree &other);

  bool contains(const key_type &Key) const noexcept;
  iterator lower_bound(const key_type &Key) noexcept;
  iterator upper_bound(const key_type &Key) noexcept;
  size_type count(const key_type &k) const;
  std::pair<iterator, iterator> equal_range(const key_type &k);

 private:
  typedef enum { RED, BLACK } color_t;

  struct Node {
    value_type key_;

    Node *left_child_;
    Node *right_child_;
    Node *parent_;

    color_t color_;
  };

  node_type *root_;
  node_type *nil_;
  node_type *head_;
  node_type *tail_;
  node_type *sentinel_;
  size_type tree_size_;
  Compare comp_;
  Extracter extracter_;

  void CopyT(const RBTree &other);
  node_type *CopySubT(node_type *node, node_type *parent,
                      const node_type *other_nil, const node_type *other_sen);
  node_type *CopyN(const node_type *src);

  node_type *SearchHelper(node_type *node, key_type data) const noexcept;

  void Free(node_type *creep);

  void Transplant(node_type *from, node_type *to) noexcept;
  void LeftRotate(node_type *x) noexcept;
  void RightRotate(node_type *y) noexcept;
  void RebalanceInsert(node_type *node) noexcept;
  void RebalanceDelete(node_type *x) noexcept;
  std::pair<node_type *, iterator> EraseHandler(const_iterator pos) noexcept;

  node_type *extract(const_iterator position);

  inline node_type *MRight(const node_type *current) noexcept;
  inline node_type *MLeft(const node_type *current) noexcept;
  std::pair<node_type *, bool> GetInsertUniqPos(const value_type &k);
  node_type *GetInsertEqPos(const value_type &k);
  iterator Insert(node_type *parent, const value_type &arg);
  iterator Insert(node_type *parent, node_type *nh) noexcept;
  iterator InsertHandler(node_type *parent, node_type *nh) noexcept;

  node_type *FindMinNode(node_type *enter) noexcept;
};

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBTree()
    : root_(nullptr),
      nil_(new node_type),
      sentinel_(new node_type),
      tree_size_(0),
      comp_(),
      extracter_() {
  nil_->key_ = value_type();
  nil_->left_child_ = nil_->right_child_ = nil_->parent_ = nullptr;
  nil_->color_ = BLACK;

  sentinel_->key_ = value_type();
  sentinel_->parent_ = nullptr;
  sentinel_->left_child_ = sentinel_->right_child_ = sentinel_;
  sentinel_->color_ = BLACK;

  head_ = tail_ = sentinel_;
};

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBTree(const RBTree &other) : RBTree() {
  CopyT(other);
}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBTree(RBTree &&other) noexcept : RBTree() {
  std::swap(this->root_, other.root_);
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->nil_, other.nil_);
  std::swap(this->sentinel_, other.sentinel_);
  std::swap(this->tree_size_, other.tree_size_);
}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::~RBTree() {
  clear();
  delete nil_;
  delete sentinel_;
}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter> &RBTree<K, T, Compare, Extracter>::operator=(
    const RBTree &other) {
  CopyT(other);
  return *this;
}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter> &RBTree<K, T, Compare, Extracter>::operator=(
    RBTree &&other) noexcept {
  if (this != &other) {
    clear();
    delete nil_;
    delete sentinel_;

    root_ = other.root_;
    nil_ = other.nil_;
    head_ = other.head_;
    tail_ = other.tail_;
    sentinel_ = other.sentinel_;
    tree_size_ = other.tree_size_;

    other.root_ = nullptr;
    other.nil_ = nullptr;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.sentinel_ = nullptr;
    other.tree_size_ = 0;
  }

  return *this;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::begin() noexcept {
  return iterator(head_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::const_iterator
RBTree<K, T, Compare, Extracter>::begin() const noexcept {
  return const_iterator(head_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::const_iterator
RBTree<K, T, Compare, Extracter>::cbegin() const noexcept {
  return const_iterator(head_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::end() noexcept {
  return iterator(sentinel_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::const_iterator
RBTree<K, T, Compare, Extracter>::end() const noexcept {
  return const_iterator(sentinel_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::const_iterator
RBTree<K, T, Compare, Extracter>::cend() const noexcept {
  return const_iterator(sentinel_);
}

template <typename K, typename T, class Compare, class Extracter>
bool RBTree<K, T, Compare, Extracter>::empty() const noexcept {
  return begin() == end();
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::size_type
RBTree<K, T, Compare, Extracter>::size() const noexcept {
  return tree_size_;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::size_type
RBTree<K, T, Compare, Extracter>::max_size() const {
  return (std::numeric_limits<size_type>::max() /
          sizeof(RBTree<K, T, Compare, Extracter>::node_type)) /
         2;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::clear() {
  if (root_ == nullptr) {
    return;
  }

  Free(root_);

  root_ = nullptr;
  head_ = tail_ = sentinel_;
  sentinel_->left_child_ = sentinel_->right_child_ = sentinel_;
  tree_size_ = 0;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::Free(node_type *creep) {
  if (creep == nil_ || creep == sentinel_) {
    return;
  }

  Free(MLeft(creep));
  Free(MRight(creep));
  delete creep;
}

template <typename K, typename T, class Compare, class Extracter>
std::pair<typename RBTree<K, T, Compare, Extracter>::iterator, bool>
RBTree<K, T, Compare, Extracter>::insert_unique(const value_type &val) {
  std::pair<iterator, bool> out;
  std::pair<node_type *, bool> res = GetInsertUniqPos(val);

  if (res.second) {
    return out = std::make_pair(Insert(res.first, val), true);
  }

  return out = std::make_pair(iterator(res.first), false);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::insert_equal(const value_type &val) {
  node_type *pos = GetInsertEqPos(val);

  return Insert(pos, val);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::MLeft(const node_type *current) noexcept {
  return current->left_child_;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::MRight(const node_type *current) noexcept {
  return current->right_child_;
}

template <typename K, typename T, class Compare, class Extracter>
std::pair<typename RBTree<K, T, Compare, Extracter>::node_type *, bool>
RBTree<K, T, Compare, Extracter>::GetInsertUniqPos(const value_type &k) {
  std::pair<node_type *, bool> res;
  node_type *tmp = root_;
  node_type *parent = nullptr;
  bool comp = true;

  while (tmp != nil_ && tmp != sentinel_ && tmp != nullptr) {
    parent = tmp;
    comp = comp_(extracter_(k), extracter_(tmp->key_));
    tmp = comp ? MLeft(tmp) : MRight(tmp);
  }

  iterator x = iterator(parent);

  if (comp) {
    if (x == begin()) {
      return res = std::make_pair(parent, true);

    } else if (x.it_ == nullptr) {
      return res = std::make_pair(nullptr, true);

    } else {
      --x;
    }
  }

  if (comp_(extracter_(x.it_->key_), extracter_(k))) {
    return res = std::make_pair(parent, true);
  }

  return res = std::make_pair(x.it_, false);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::GetInsertEqPos(const value_type &k) {
  node_type *tmp = root_;
  node_type *parent = nullptr;

  while (tmp != nil_ && tmp != sentinel_ && tmp != nullptr) {
    parent = tmp;
    tmp = comp_(k, tmp->key_) ? MLeft(tmp) : MRight(tmp);
  }

  return parent;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::RebalanceInsert(
    node_type *node) noexcept {
  node_type *uncle = nil_;

  while (node != root_ && node->parent_->color_ == RED) {
    if (node->parent_ == node->parent_->parent_->left_child_) {
      uncle = node->parent_->parent_->right_child_;

      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;

      } else {
        if (node == node->parent_->right_child_) {
          node = node->parent_;
          LeftRotate(node);
        }

        node->parent_->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        RightRotate(node->parent_->parent_);
      }

    } else {
      uncle = node->parent_->parent_->left_child_;

      if (uncle->color_ == RED) {
        node->parent_->color_ = BLACK;
        uncle->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        node = node->parent_->parent_;

      } else {
        if (node == node->parent_->left_child_) {
          node = node->parent_;
          RightRotate(node);
        }

        node->parent_->color_ = BLACK;
        node->parent_->parent_->color_ = RED;
        LeftRotate(node->parent_->parent_);
      }
    }
  }

  root_->color_ = BLACK;

  tail_->right_child_ = sentinel_;
  head_->left_child_ = sentinel_;
  sentinel_->left_child_ = sentinel_->right_child_ = tail_;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::LeftRotate(node_type *x) noexcept {
  node_type *y = x->right_child_;
  x->right_child_ = y->left_child_;

  if (y->left_child_ != nil_ && y->left_child_ != sentinel_) {
    y->left_child_->parent_ = x;
  }

  y->parent_ = x->parent_;

  if (x->parent_ == nullptr) {
    root_ = y;

  } else if (x == x->parent_->left_child_) {
    x->parent_->left_child_ = y;

  } else {
    x->parent_->right_child_ = y;
  }

  y->left_child_ = x;
  x->parent_ = y;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::RightRotate(node_type *y) noexcept {
  node_type *x = y->left_child_;
  y->left_child_ = x->right_child_;

  if (x->right_child_ != nil_ && x->right_child_ != sentinel_) {
    x->right_child_->parent_ = y;
  }

  x->parent_ = y->parent_;

  if (y->parent_ == nullptr) {
    root_ = x;

  } else if (y == y->parent_->left_child_) {
    y->parent_->left_child_ = x;

  } else {
    y->parent_->right_child_ = x;
  }

  x->right_child_ = y;
  y->parent_ = x;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::Insert(node_type *parent,
                                         const value_type &arg) {
  node_type *newNode = new node_type;
  newNode->key_ = arg;
  newNode->left_child_ = nil_;
  newNode->right_child_ = nil_;
  newNode->parent_ = parent;

  return iterator(InsertHandler(parent, newNode));
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::Insert(node_type *parent,
                                         node_type *nh) noexcept {
  nh->left_child_ = nil_;
  nh->right_child_ = nil_;
  nh->parent_ = parent;

  return iterator(InsertHandler(parent, nh));
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::InsertHandler(node_type *parent,
                                                node_type *nh) noexcept {
  ++tree_size_;

  nh->color_ = RED;

  if (parent == nullptr) {
    root_ = nh;
    head_ = nh;
    tail_ = nh;

    head_->left_child_ = sentinel_;
    tail_->right_child_ = sentinel_;
    sentinel_->left_child_ = sentinel_->right_child_ = tail_;

    root_->color_ = BLACK;

    return iterator(root_);
  }

  if (comp_(extracter_(nh->key_), extracter_(parent->key_))) {
    parent->left_child_ = nh;

  } else {
    parent->right_child_ = nh;
  }

  if (head_->left_child_ != sentinel_) {
    head_ = MLeft(head_);
  }

  if (tail_->right_child_ != sentinel_) {
    tail_ = MRight(tail_);
  }

  RebalanceInsert(nh);

  return iterator(nh);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::search(const key_type target) const noexcept {
  return iterator(SearchHelper(root_, target));
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::SearchHelper(node_type *node,
                                               key_type data) const noexcept {
  if (node == nullptr || node == sentinel_ || node == nil_) {
    return sentinel_;
  }

  if (data == extracter_(node->key_)) {
    return node;
  }

  if (data < extracter_(node->key_)) {
    return SearchHelper(node->left_child_, data);
  }

  return SearchHelper(node->right_child_, data);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::erase(iterator pos) {
  if (root_ == nullptr) {
    return end();
  }

  if (pos == end()) {
    return pos;
  }

  std::pair<node_type *, iterator> deletable = EraseHandler(pos);

  delete deletable.first;

  return deletable.second;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::Transplant(node_type *from,
                                                  node_type *to) noexcept {
  if (from->parent_ == nullptr) {
    root_ = to;

  } else if (from == from->parent_->left_child_) {
    from->parent_->left_child_ = to;

  } else {
    from->parent_->right_child_ = to;
  }

  to->parent_ = from->parent_;
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::RebalanceDelete(node_type *x) noexcept {
  node_type *sibling = nullptr;

  while (x != root_ && x->color_ == BLACK) {
    if (x == x->parent_->left_child_) {
      sibling = x->parent_->right_child_;

      if (sibling->color_ == RED) {
        sibling->color_ = BLACK;
        x->parent_->color_ = RED;
        LeftRotate(x->parent_);
        sibling = x->parent_->right_child_;
      }

      if (sibling->left_child_->color_ == BLACK &&
          sibling->right_child_->color_ == BLACK) {
        sibling->color_ = RED;
        x = x->parent_;

      } else {
        if (sibling->right_child_->color_ == BLACK) {
          sibling->left_child_->color_ = BLACK;
          sibling->color_ = RED;
          RightRotate(sibling);
          sibling = x->parent_->right_child_;
        }

        sibling->color_ = x->parent_->color_;
        x->parent_->color_ = BLACK;
        sibling->right_child_->color_ = BLACK;
        LeftRotate(x->parent_);
        x = root_;
      }

    } else {
      sibling = x->parent_->left_child_;

      if (sibling->color_ == RED) {
        sibling->color_ = BLACK;
        x->parent_->color_ = RED;
        RightRotate(x->parent_);
        sibling = x->parent_->left_child_;
      }

      if (sibling->left_child_->color_ == BLACK &&
          sibling->right_child_->color_ == BLACK) {
        sibling->color_ = RED;
        x = x->parent_;

      } else {
        if (sibling->left_child_->color_ == BLACK) {
          sibling->right_child_->color_ = BLACK;
          sibling->color_ = RED;
          LeftRotate(sibling);
          sibling = x->parent_->left_child_;
        }

        sibling->color_ = x->parent_->color_;
        x->parent_->color_ = BLACK;
        sibling->left_child_->color_ = BLACK;
        RightRotate(x->parent_);
        x = root_;
      }
    }
  }

  x->color_ = BLACK;
}

template <typename K, typename T, class Compare, class Extracter>
std::pair<typename RBTree<K, T, Compare, Extracter>::node_type *,
          typename RBTree<K, T, Compare, Extracter>::iterator>
RBTree<K, T, Compare, Extracter>::EraseHandler(const_iterator pos) noexcept {
  node_type *tmp = nullptr;
  node_type *deletable = pos.it_;
  color_t originalColor = pos.it_->color_;

  if (deletable->left_child_ == nil_ || deletable->left_child_ == sentinel_) {
    tmp = deletable->right_child_;
    Transplant(deletable, deletable->right_child_);

  } else if (deletable->right_child_ == nil_ ||
             deletable->right_child_ == sentinel_) {
    tmp = deletable->left_child_;
    Transplant(deletable, deletable->left_child_);

  } else {
    node_type *minNode = FindMinNode(deletable->right_child_);
    originalColor = minNode->color_;
    tmp = minNode->right_child_;

    if (minNode->parent_ == deletable) {
      tmp->parent_ = minNode;

    } else {
      Transplant(minNode, minNode->right_child_);
      minNode->right_child_ = deletable->right_child_;
      minNode->right_child_->parent_ = minNode;
    }

    Transplant(deletable, minNode);
    minNode->left_child_ = deletable->left_child_;
    minNode->left_child_->parent_ = minNode;
    minNode->color_ = deletable->color_;
  }

  if (originalColor == BLACK) {
    RebalanceDelete(tmp);
    sentinel_->parent_ = nullptr;
  }

  iterator next(deletable);

  if (next.it_->left_child_ == sentinel_ &&
      next.it_->right_child_ == sentinel_) {
    ++next;
    head_ = sentinel_;
    tail_ = sentinel_;

  } else if (next.it_->left_child_ == sentinel_) {
    ++next;
    head_ = next.it_;
    head_->left_child_ = sentinel_;

  } else if (next.it_->right_child_ == sentinel_) {
    --next;
    tail_ = next.it_;
    tail_->right_child_ = sentinel_;
    sentinel_->parent_ = nullptr;
    sentinel_->left_child_ = sentinel_->right_child_ = tail_;

  } else {
    ++next;
  }

  --tree_size_;

  if (root_ == sentinel_) {
    root_ = nullptr;
  }

  return std::pair<node_type *, iterator>(deletable, next);
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::swap(RBTree &other) {
  std::swap(root_, other.root_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(nil_, other.nil_);
  std::swap(sentinel_, other.sentinel_);
  std::swap(tree_size_, other.tree_size_);
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::merge_unique(RBTree &other) {
  iterator pos;
  std::pair<node_type *, bool> search_pos;
  node_type *cutting = nullptr;

  for (auto i = other.begin(), end = other.end(); i != end;) {
    pos = i++;
    search_pos = GetInsertUniqPos(pos.it_->key_);

    if (search_pos.second) {
      cutting = other.extract(pos);
      Insert(search_pos.first, cutting);
    }
  }
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::merge_equal(RBTree &other) {
  iterator pos;
  node_type *cutting = nullptr;

  for (auto i = other.begin(), end = other.end(); i != end;) {
    pos = i++;
    cutting = other.extract(pos);
    Insert(GetInsertEqPos(pos.it_->key_), cutting);
  }
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::extract(const_iterator position) {
  node_type *seized = EraseHandler(position).first;
  return seized;
}

template <typename K, typename T, class Compare, class Extracter>
bool RBTree<K, T, Compare, Extracter>::contains(
    const key_type &Key) const noexcept {
  iterator finder = search(Key);

  if (finder == end()) {
    return false;
  }

  return true;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::lower_bound(const key_type &Key) noexcept {
  iterator it = begin();

  while (it != end() && comp_(extracter_(it.it_->key_), Key)) {
    ++it;
  }

  return it;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::upper_bound(const key_type &Key) noexcept {
  iterator it = begin();

  while (it != end() && !comp_(Key, extracter_(it.it_->key_))) {
    ++it;
  }

  return it;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::size_type
RBTree<K, T, Compare, Extracter>::count(const key_type &k) const {
  size_type coincidences = 0;

  for (auto it = cbegin(); it != cend(); ++it) {
    if (extracter_(it.it_->key_) == k) {
      ++coincidences;
    }
  }

  return coincidences;
}

template <typename K, typename T, class Compare, class Extracter>
std::pair<typename RBTree<K, T, Compare, Extracter>::iterator,
          typename RBTree<K, T, Compare, Extracter>::iterator>
RBTree<K, T, Compare, Extracter>::equal_range(const key_type &k) {
  iterator lower = lower_bound(k);
  iterator upper = upper_bound(k);

  return std::make_pair(lower, upper);
}

template <typename K, typename T, class Compare, class Extracter>
void RBTree<K, T, Compare, Extracter>::CopyT(const RBTree &other) {
  if (this != &other) {
    if (!empty()) {
      clear();
    }

    tree_size_ = other.tree_size_;
    root_ = CopySubT(other.root_, nullptr, other.nil_, other.sentinel_);
    sentinel_->left_child_ = sentinel_->right_child_ = tail_;
  }
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::CopySubT(node_type *node, node_type *parent,
                                           const node_type *other_nil,
                                           const node_type *other_sen) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node == other_nil) {
    return nil_;
  }

  if (node == other_sen) {
    return sentinel_;
  }

  node_type *newNode = CopyN(node);
  newNode->parent_ = parent;

  if (head_ == sentinel_) {
    head_ = newNode;
  } else if (head_->key_ >= newNode->key_) {
    head_ = newNode;
  }

  if (tail_ == sentinel_) {
    tail_ = newNode;
  } else if (newNode->key_ >= tail_->key_) {
    tail_ = newNode;
  }

  newNode->left_child_ = CopySubT(MLeft(node), newNode, other_nil, other_sen);
  newNode->right_child_ = CopySubT(MRight(node), newNode, other_nil, other_sen);

  return newNode;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::CopyN(const node_type *src) {
  node_type *dst = new node_type;
  dst->key_ = src->key_;
  dst->color_ = src->color_;
  dst->left_child_ = nil_;
  dst->right_child_ = nil_;
  return dst;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::FindMinNode(node_type *enter) noexcept {
  node_type *finder = enter;
  if (finder == nullptr || finder == nil_ || finder == sentinel_) {
    return finder;
  }

  while (finder->left_child_ != nil_ && finder->left_child_ != sentinel_) {
    finder = MLeft(finder);
  }

  return finder;
}

/*Iterator*/

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBIterator::RBIterator() noexcept
    : it_(nullptr) {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBIterator::RBIterator(node_type *src)
    : it_(src) {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBIterator::RBIterator(const iterator &src)
    : it_(src.it_) {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::RBIterator::RBIterator(
    iterator &&other) noexcept
    : RBIterator() {
  std::swap(other.it_, it_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator &
RBTree<K, T, Compare, Extracter>::RBIterator::operator=(const iterator &other) {
  it_ = other.it_;
  return *this;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator &
RBTree<K, T, Compare, Extracter>::RBIterator::operator=(
    iterator &&other) noexcept {
  it_ = other.it_;
  other.it_ = nullptr;
  return *this;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator &
RBTree<K, T, Compare, Extracter>::iterator::operator++() noexcept {
  if (it_->right_child_->right_child_ != nullptr) {
    it_ = GetMin(it_->right_child_);
    return *this;
  }

  node_type *steper = it_->parent_;

  if (it_ == steper->right_child_) {
    while (steper != nullptr && it_ == steper->right_child_) {
      it_ = steper;
      steper = it_->parent_;
    }

    it_ = steper;

  } else {
    it_ = steper;
  }

  return *this;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::iterator::operator++(int) noexcept {
  iterator temp = *this;
  operator++();
  return temp;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator &
RBTree<K, T, Compare, Extracter>::iterator::operator--() noexcept {
  if (it_->left_child_->left_child_ != nullptr) {
    it_ = GetMax(it_->left_child_);
    return *this;
  }

  node_type *steper = it_->parent_;

  if (it_ == steper->left_child_) {
    while (steper != nullptr && it_ == steper->left_child_) {
      it_ = steper;
      steper = it_->parent_;
    }

    it_ = steper;

  } else {
    it_ = steper;
  }

  return *this;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::iterator
RBTree<K, T, Compare, Extracter>::iterator::operator--(int) noexcept {
  iterator temp = *this;
  operator--();
  return temp;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::reference
RBTree<K, T, Compare, Extracter>::iterator::operator*() {
  return *reinterpret_cast<value_type *>(&it_->key_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::pointer
RBTree<K, T, Compare, Extracter>::iterator::operator->() {
  return reinterpret_cast<pointer>(&it_->key_);
}

template <typename K, typename T, class Compare, class Extracter>
inline bool RBTree<K, T, Compare, Extracter>::iterator::operator==(
    const iterator &other) const noexcept {
  return it_ == other.it_;
}

template <typename K, typename T, class Compare, class Extracter>
inline bool RBTree<K, T, Compare, Extracter>::iterator::operator!=(
    const iterator &other) const noexcept {
  return it_ != other.it_;
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::iterator::GetMax(node_type *enter) noexcept {
  if (enter == nullptr) return nullptr;

  if (enter->right_child_->right_child_ == nullptr) {
    return enter;

  } else if (enter->right_child_->parent_ == nullptr) {
    return enter;

  } else if (enter->parent_ == nullptr) {
    return enter;
  }

  return GetMax(enter->right_child_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::node_type *
RBTree<K, T, Compare, Extracter>::iterator::GetMin(node_type *enter) noexcept {
  if (enter == nullptr) return nullptr;

  if (enter->left_child_->left_child_ == nullptr) {
    return enter;

  } else if (enter->parent_ == nullptr) {
    return enter;
  }

  return GetMin(enter->left_child_);
}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::const_iterator::RBConstIterator() noexcept
    : RBIterator() {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::const_iterator::RBConstIterator(
    node_type *src)
    : RBIterator(src) {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::const_iterator::RBConstIterator(
    const iterator &other)
    : RBIterator(other) {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::const_iterator::RBConstIterator(
    const const_iterator &other)
    : RBIterator(other) {}

template <typename K, typename T, class Compare, class Extracter>
RBTree<K, T, Compare, Extracter>::const_iterator::RBConstIterator(
    const_iterator &&other)
    : RBConstIterator() {
  std::swap(RBIterator::it_, other.it_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::reference
RBTree<K, T, Compare, Extracter>::const_iterator::operator*() const {
  return *static_cast<value_type *>(&RBIterator::it_->key_);
}

template <typename K, typename T, class Compare, class Extracter>
typename RBTree<K, T, Compare, Extracter>::pointer
RBTree<K, T, Compare, Extracter>::const_iterator::operator->() const {
  return static_cast<value_type *>(&RBIterator::it_->key_);
}

}  // namespace s21

#endif