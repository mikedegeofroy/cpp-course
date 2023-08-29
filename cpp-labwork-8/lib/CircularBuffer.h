#pragma once

#include <algorithm>
#include <memory>


template <typename CircularBuffer, bool isConst>
class BufferIterator {
 public:
  using value_type = typename CircularBuffer::value_type;
  using difference_type = typename CircularBuffer::difference_type;
  using pointer_type = value_type*;
  using reference_type = value_type&;

  using iterator_category = std::random_access_iterator_tag;
  using pointer =
      typename std::conditional<isConst, const value_type*, value_type*>::type;
  using reference =
      typename std::conditional<isConst, const value_type&, value_type&>::type;

  BufferIterator(pointer_type buffer_ptr) : buffer_ptr_(buffer_ptr) {}

  BufferIterator operator+(const int& index) {
    BufferIterator temp(buffer_ptr_ + index);
    return temp;
  }

  BufferIterator& operator++() {
    ++buffer_ptr_;
    return *this;
  }

  BufferIterator operator++(int) {
    BufferIterator iterator = (*this);
    ++(*this);
    return iterator;
  }

  BufferIterator& operator+=(const int& index) {
    buffer_ptr_ += index;
    return *(this);
  }

  BufferIterator operator-(const int& index) {
    BufferIterator temp(buffer_ptr_ + index);
    return temp;
  }

  difference_type operator-(const BufferIterator& rhs) {
    return buffer_ptr_ - rhs.buffer_ptr_;
  }

  BufferIterator& operator--() {
    --buffer_ptr_;
    return *this;
  }

  BufferIterator operator--(int) {
    BufferIterator iterator = (*this);
    --(*this);
    return iterator;
  }

  BufferIterator& operator-=(const int& index) {
    buffer_ptr_ += index;
    return *(this);
  }

  BufferIterator operator[](size_t index) { return *(buffer_ptr_[index]); }

  pointer_type operator->() { return buffer_ptr_; }

  reference_type operator*() { return *buffer_ptr_; }

  bool operator==(const BufferIterator& other) const {
    return buffer_ptr_ == other.buffer_ptr_;
  }

  bool operator!=(const BufferIterator& other) { return !(*this == other); }

  bool operator<(const BufferIterator& other) {
    return buffer_ptr_ < other.buffer_ptr_;
  }

  bool operator<=(const BufferIterator& other) {
    return buffer_ptr_ <= other.buffer_ptr_;
  }

  bool operator>(const BufferIterator& other) {
    return buffer_ptr_ > other.buffer_ptr_;
  }

  bool operator>=(const BufferIterator& other) {
    return buffer_ptr_ >= other.buffer_ptr_;
  }

 protected:
  pointer_type buffer_ptr_;
};

template <typename T, typename Allocator = std::allocator<T>>
class CircularBuffer {
 public:
  using value_type = T;
  using allocator_type = Allocator;
  using allocator_traits = std::allocator_traits<Allocator>;
  using size_type = typename allocator_traits::size_type;
  using difference_type = typename allocator_traits::difference_type;

  using pointer = typename allocator_traits::pointer;
  using reference = typename allocator_type::reference;
  using const_reference = typename allocator_type::const_reference;

  using Iterator = BufferIterator<CircularBuffer<T>, false>;
  using ConstIterator = BufferIterator<CircularBuffer<T>, true>;

  CircularBuffer(const size_type& capacity,
                 const Allocator& alloc = Allocator())
      : allocator_(alloc),
        buffer_(allocator_.allocate(capacity)),
        capacity_(capacity),
        head_(0),
        tail_(0),
        size_(0) {}

  CircularBuffer(CircularBuffer& other, const Allocator& alloc = Allocator())
      : allocator_(alloc),
        buffer_(allocator_.allocate(other.capacity_)),
        capacity_(other.capacity_),
        head_(0),
        tail_(0),
        size_(0) {
    if (other.size_ > 0) {
      copy(other);
    }
  }

  CircularBuffer(size_type count, const_reference element,
                 const Allocator& alloc = Allocator())
      : allocator_(alloc),
        buffer_(allocator_.allocate(count)),
        capacity_(count),
        head_(0),
        tail_(count),
        size_(count) {
    for (size_type i = 0; i < count; ++i) {
      allocator_traits::construct(allocator_, buffer_ + i, element);
    }
  }

  CircularBuffer& operator=(CircularBuffer& other) {
    clear();
    copy(other);
    return *(this);
  }

  bool operator==(CircularBuffer& other) {
    if (size_ != other.size_) return false;
    for (Iterator data1 = begin(), data2 = other.begin(); data1 != end();
         data1++, data2++) {
      if (*data1 != *data2) return false;
    }
    return true;
  }

  bool operator!=(CircularBuffer& other) { return !(*this == other); }

  template <typename... Args>
  Iterator emplace(Iterator position, Args&&... args) {
    difference_type index = std::distance(begin(), position);
    if (size_ < capacity_) {
      emplace_back(std::move(buffer_[(head_ + size_ - 1) % capacity_]));
    }

    for (difference_type i = size_ - 2; i > index; --i) {
      buffer_[(head_ + i) % capacity_] =
          std::move(buffer_[(head_ + i - 1) % capacity_]);
    }

    allocator_traits::destroy(allocator_,
                              buffer_ + (head_ + index) % capacity_);
    allocator_traits::construct(allocator_,
                                buffer_ + (head_ + index) % capacity_,
                                std::forward<Args>(args)...);

    if (size_ < capacity_) {
      tail_ = (tail_ + 1) % capacity_;
    } else {
      tail_ = (tail_ + 1) % capacity_;
      head_ = (head_ + 1) % capacity_;
    }

    return Iterator(buffer_ + (head_ + index) % capacity_);
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (size_ < capacity_) {
      allocator_traits::construct(allocator_, buffer_ + tail_,
                                  std::forward<Args>(args)...);
      tail_ = (tail_ + 1) % capacity_;
      ++size_;
    } else {
      allocator_traits::destroy(allocator_, buffer_ + head_);
      allocator_traits::construct(allocator_, buffer_ + head_,
                                  std::forward<Args>(args)...);
      head_ = (head_ + 1) % capacity_;
      tail_ = (tail_ + 1) % capacity_;
    }
  }

  void push_back(const_reference value) {
    if (size_ < capacity_) {
      allocator_traits::construct(allocator_, buffer_ + tail_, value);
      tail_ = (tail_ + 1) % capacity_;
      ++size_;
    } else {
      allocator_traits::destroy(allocator_, buffer_ + head_);
      allocator_traits::construct(allocator_, buffer_ + head_, value);
      head_ = (head_ + 1) % capacity_;
      tail_ = (tail_ + 1) % capacity_;
    }
  }

  void pop_front() {
    if (empty()) {
      throw std::underflow_error("Circular buffer is empty");
    }
    allocator_traits::destroy(allocator_, buffer_ + head_);
    head_ = (head_ + 1) % capacity_;
    --size_;
  }

  void pop_back() {
    if (empty()) {
      throw std::underflow_error("Circular buffer is empty");
    }
    tail_ = (capacity_ + tail_ - 1) % capacity_;
    allocator_traits::destroy(allocator_, buffer_ + tail_);
    --size_;
  }

  void assign(size_type count, const_reference value) {
    clear();
    if (count > capacity_) {
      throw std::length_error(
          "The count is greater than the buffer's capacity");
    }

    for (size_type i = 0; i < count; ++i) {
      push_back(value);
    }
  }

  template <typename OtherIterator>
  void assign(OtherIterator first, OtherIterator last) {
    clear();
    size_type count = std::distance(first, last);

    if (count > capacity_) {
      throw std::length_error("The range is larger than the buffer's capacity");
    }

    for (; first != last; ++first) {
      push_back(*first);
    }
  }

  Iterator erase(Iterator first, Iterator last) {
    if (first == last) {
      return first;
    }

    if (first < begin() || first >= end() || last < begin() || last > end()) {
      throw std::out_of_range("Iterators are out of range");
    }

    Iterator source = last;
    Iterator target = first;

    while (source != end()) {
      *target = std::move(*source);
      ++target;
      ++source;
    }

    size_type elements_to_destroy = std::distance(first, last);
    for (size_type i = 0; i < elements_to_destroy; ++i) {
      pop_back();
    }

    return first;
  }

  Iterator erase(Iterator element) { return erase(element, element + 1); }

  Iterator insert(Iterator position, const_reference value) {
    if (position < begin() || position > end()) {
      throw std::out_of_range("Position out of range");
    }

    if (size_ < capacity_) {
      ++size_;
    }

    int max_size = int(capacity_);
    int insert_index = std::distance(begin(), position);
    int last_index = size_ - 1;
    for (int i = last_index; i > insert_index; --i) {
      if (i == last_index && size_ == capacity_) {
        allocator_traits::destroy(allocator_, buffer_ + (head_ + i) % max_size);
      }
      allocator_traits::construct(
          allocator_, buffer_ + (head_ + i) % max_size,
          std::move(buffer_[(head_ + i - 1) % max_size]));
    }

    allocator_traits::destroy(allocator_,
                              buffer_ + (head_ + insert_index) % max_size);
    allocator_traits::construct(
        allocator_, buffer_ + (head_ + insert_index) % max_size, value);

    if (size_ < capacity_) {
      tail_ = (capacity_ + (tail_ + 1)) % capacity_;
    } else {
      tail_ = (capacity_ + (tail_ + 1)) % capacity_;
    }
    // Think about moving the head thing.
    return position;
  }

  Iterator insert(Iterator position, size_type count, const_reference value) {
    difference_type index = std::distance(begin(), position);

    if (count + size_ > capacity_) {
      count = capacity_ - size_;
    }

    if (size_ + count > capacity_) {
      size_type num_to_destroy = count - (capacity_ - size_);
      for (size_type i = 0; i < num_to_destroy; ++i) {
        pop_front();
      }
    }

    size_ += count;

    for (difference_type i = size_ - 1; i >= index + count; --i) {
      buffer_[(head_ + i) % capacity_] =
          std::move(buffer_[(head_ + i - count) % capacity_]);
    }

    for (size_type i = 0; i < count; ++i) {
      allocator_traits::destroy(allocator_,
                                buffer_ + (head_ + index + i) % capacity_);
      allocator_traits::construct(
          allocator_, buffer_ + (head_ + index + i) % capacity_, value);
    }

    tail_ = (tail_ + count) % capacity_;
    if (size_ == capacity_) {
      head_ = (head_ + count) % capacity_;
    }

    return Iterator(buffer_ + (head_ + index) % capacity_);
  }

  void clear() {
    size_type current_index = (capacity_ + (tail_ - 1)) % capacity_;
    while (size_ > 0) {
      allocator_traits::destroy(allocator_, buffer_ + current_index);
      current_index = (capacity_ + (current_index - 1)) % capacity_;
      tail_ = (capacity_ + (tail_ - 1)) % capacity_;
      size_--;
    }
  }

  reference back() { return buffer_[(capacity_ + (tail_ - 1)) % capacity_]; }

  reference front() { return buffer_[head_]; }

  reference at(const size_type& index) {
    return buffer_[(head_ + index) % size_];
  }

  reference operator[](const size_type& index) {
    return buffer_[(head_ + index) % size_];
  }

  Iterator begin() { return Iterator(buffer_ + head_); }
  Iterator end() { return Iterator(buffer_ + size_); }

  ConstIterator begin() const { return ConstIterator(buffer_ + head_); }
  ConstIterator end() const { return ConstIterator(buffer_ + size_); }

  ConstIterator cbegin() const { return ConstIterator(buffer_ + head_); }
  ConstIterator cend() const { return ConstIterator(buffer_ + size_); }

  void swap(CircularBuffer& other) {
    CircularBuffer temp = other;
    other = (*this);
    (*this) = temp;
  }

  size_type size() { return size_; }

  size_type max_size() { return capacity_; }

  bool empty() { return size_ == 0; }

  ~CircularBuffer() { allocator_.deallocate(buffer_, capacity_); }

 protected:
  void copy(CircularBuffer& other) {
    for (Iterator data = other.begin(); data != other.end(); ++data) {
      allocator_traits::construct(allocator_, buffer_ + tail_, *data);
      tail_ = (tail_ + 1) % capacity_;
      ++size_;
    }
  }

  allocator_type allocator_;
  pointer buffer_;
  size_type capacity_;
  size_type head_;
  size_type tail_;
  size_type size_;
};

template <typename T, typename Allocator>
void swap(CircularBuffer<T, Allocator>& buffer1,
          CircularBuffer<T, Allocator>& buffer2) {
  buffer1.swap(buffer2);
}

template <typename T, typename Allocator = std::allocator<T>>
class ExtCircularBuffer : public CircularBuffer<T, Allocator> {
 public:
  using Base = CircularBuffer<T, Allocator>;
  using size_type = typename Base::size_type;
  using const_reference = typename Base::const_reference;

  ExtCircularBuffer(size_type capacity) : Base(capacity) {}

  void resize(size_type new_capacity) {
    if (new_capacity == Base::capacity_) {
      return;
    }

    T* new_buffer = Base::allocator_.allocate(new_capacity);

    size_type num_elements_to_copy = std::min(Base::size_, new_capacity);
    for (size_type i = 0; i < num_elements_to_copy; ++i) {
      Base::allocator_traits::construct(
          Base::allocator_, new_buffer + i,
          std::move(Base::buffer_[(Base::head_ + i) % Base::capacity_]));
      Base::allocator_traits::destroy(
          Base::allocator_,
          Base::buffer_ + (Base::head_ + i) % Base::capacity_);
    }

    Base::allocator_.deallocate(Base::buffer_, Base::capacity_);
    Base::buffer_ = new_buffer;
    Base::head_ = 0;
    Base::tail_ = num_elements_to_copy % new_capacity;
    Base::capacity_ = new_capacity;
    Base::size_ = num_elements_to_copy;
  }
};