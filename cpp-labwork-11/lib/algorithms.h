#include <utility>
#include <iterator>
namespace algo {

template <typename Iterator, typename Predicate>
bool all_of(Iterator from, Iterator to, Predicate predicate) {
  for (; from != to; from++)
    if (!predicate(*from)) return false;
  return true;
}

template <typename Iterator, typename Predicate>
bool any_of(Iterator from, Iterator to, Predicate predicate) {
  for (; from != to; from++)
    if (predicate(*from)) return true;
  return false;
}

template <typename Iterator, typename Predicate>
bool none_of(Iterator from, Iterator to, Predicate predicate) {
  for (; from != to; from++)
    if (predicate(*from)) return false;
  return true;
}

template <typename Iterator, typename Predicate>
bool one_of(Iterator from, Iterator to, Predicate predicate) {
  size_t counter = 0;
  for (; from != to; from++)
    if (predicate(*from)) counter++;
  return counter == 1;
}

template <typename Iterator,
          typename Compare =
              std::less<typename std::iterator_traits<Iterator>::value_type>>
bool is_sorted(Iterator from, Iterator to, Compare comparison = Compare()) {
  for (; from != to - 1; from++)
    if (comparison(*(from + 1), *from)) return false;
  return true;
}

template <typename Iterator, typename Predicate>
bool is_partitioned(Iterator from, Iterator to, Predicate predicate) {
  for (; from != to; ++from)
    if (!predicate(*from)) break;
  if (from == to) return true;
  ++from;
  for (; from != to; ++from)
    if (predicate(*from)) return false;
  return true;
}

template <typename Iterator, typename T>
Iterator find_not(Iterator from, Iterator to, const T& value) {
  for (; from != to; ++from)
    if (value != *from) break;
  return from;
}

template <typename Iterator, typename T>
Iterator find_backward(Iterator from, Iterator to, const T& value) {
  if (from == to) {
    return from;
  }

  Iterator it = to;
  while (it != from) {
    --it;
    if (*it == value) {
      return it;
    }
  }

  return from;
}

template <typename Iterator>
bool is_palindrome(Iterator from, Iterator to) {
  to--;
  for (; from < to; from++, to--)
    if (*from != *to) return false;
  return true;
}

template <typename T>
class xrange {
 public:
  class iterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;

    iterator(T value, T step) : value_(value), step_(step) {}

    T operator*() const { return value_; }

    iterator& operator++() {
      value_ += step_;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const {
      return other.value_ == value_;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    T value_;
    T step_;
  };

  xrange(T from, T to, T step = T(1)) : from_(from), to_(to), step_(step) {}

  iterator begin() const { return iterator(from_, step_); }

  iterator end() const { return iterator(to_, step_); }

 private:
  T from_;
  T to_;
  T step_;
};

template <typename T1, typename T2>
class zip {
 public:
  class iterator {
   public:
    using iterator1 = typename T1::iterator;
    using iterator2 = typename T2::iterator;

    iterator(iterator1 itr1, iterator2 itr2) : itr1_(itr1), itr2_(itr2) {}

    std::pair<typename iterator1::value_type&, typename iterator2::value_type&>
    operator*() const {
      return {*itr1_, *itr2_};
    }

    iterator& operator++() {
      ++itr1_;
      ++itr2_;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const {
      return (itr1_ == other.itr1_ && itr2_ != other.itr2_) ||
             (itr1_ != other.itr1_ && itr2_ == other.itr2_);
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    iterator1 itr1_;
    iterator2 itr2_;
  };

  zip(T1& container1, T2& container2)
      : container1_(container1), container2_(container2){};

  iterator begin() const {
    return iterator(container1_.begin(), container2_.begin());
  }

  iterator end() const {
    return iterator(container1_.end(), container2_.end());
  }

 private:
  T1& container1_;
  T2& container2_;
};

}  // namespace algo