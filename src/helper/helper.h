#ifndef CPP_S21_CONTAINERS_HELPER_HELPER_H
#define CPP_S21_CONTAINERS_HELPER_HELPER_H

#include <utility>

namespace s21 {
template <typename C, typename V>
struct KeyExtract {
  C operator()(const std::pair<const C, V> &target) const {
    return target.first;
  }

  C operator()(const C target) const { return target; }
};

template <typename C, typename V>
struct Compare {
  // bool operator()(const std::pair<C, V> &lhs,
  //                 const std::pair<C, V> &rhs) const {
  //   return lhs.first < rhs.first;
  //}

  bool operator()(const C &lhs, const C &rhs) const { return lhs < rhs; }
};

template <class ImputIt1, typename ImputIt2>
bool lexicog_compare(ImputIt1 begin1, ImputIt1 end1, ImputIt2 begin2,
                     ImputIt2 end2) {
  while (begin1 != end1 && begin2 != end2) {
    if (*begin1 < *begin2) {
      return true;

    } else if (begin1 == end1 || *begin2 < *begin1) {
      return false;
    }

    ++begin1;
    ++begin2;
  }

  return begin2 != end2;
}

template <class ImputIt1, class ImputIt2>
bool is_equal(ImputIt1 lhs, ImputIt2 rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  auto it_l = lhs.begin(), it_l_end = lhs.end();
  auto it_r = rhs.begin();

  for (; it_l != it_l_end; ++it_l, ++it_r) {
    if (*it_l != *it_r) {
      return false;
    }
  }

  return true;
}

}  // namespace s21

#endif
