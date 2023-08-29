#pragma once

#include <stdlib.h>

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <vector>

#include "stack.h"

class MemoryPool {
 public:
  MemoryPool(size_t chunk_size, size_t chunk_count)
      : m_chunk_count_(chunk_count),
        m_chunk_size_(chunk_size + sizeof(DataHeader)),
        raw_chunk_size_(chunk_size),
        m_size_(chunk_count * m_chunk_size_),
        pool_index_(0) {
    m_data_ = (void*)(new char[m_size_]);

    for (int i = 0; i < m_chunk_count_; ++i) {
      size_t address = (size_t)m_data_ + i * m_chunk_size_;

      Node* node_address = reinterpret_cast<Node*>(address);
      DataHeader* header = reinterpret_cast<DataHeader*>(node_address + 1);

      header->allocated = false;
      header->pool_index = pool_index_;

      fl_.push(node_address);
    }
  }

  ~MemoryPool() { delete[] (char*)m_data_; }

  void* allocate(size_t size) {
    if (size > raw_chunk_size_) throw std::bad_alloc();  // bad
    Node* current_address = fl_.pop();
    DataHeader* header = reinterpret_cast<DataHeader*>(current_address);
    header->allocated = true;
    header->pool_index = pool_index_;
    void* data_address = (char*)current_address + sizeof(DataHeader);
    return data_address;
  }

  void deallocate(void* ptr) {
    DataHeader* header_address =
        reinterpret_cast<DataHeader*>((char*)ptr - sizeof(DataHeader));

    if (header_address->allocated == false) throw std::bad_alloc();

    fl_.push((Node*)header_address);
  }

  bool empty() { return fl_.empty(); }

  void set_pool_index(size_t index) { pool_index_ = index; }

  size_t chunk_size() { return raw_chunk_size_; }

  struct DataHeader {
    bool allocated;
    size_t pool_index;
  };

 private:
  size_t raw_chunk_size_;
  size_t m_chunk_size_;
  size_t m_chunk_count_;
  size_t m_size_;

  size_t pool_index_;

  void* m_data_;

  LinkedList<DataHeader> fl_;
  typedef LinkedList<DataHeader>::Node Node;
};

template <typename T>
class Allocator {
 public:
  std::vector<MemoryPool*> mr_;
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;

  Allocator() {
    for (int i = 0; i < 5; ++i) {
      MemoryPool* mem_pool = new MemoryPool(200, 1000'000'000);
      mr_.push_back(mem_pool);
    }
    for (int i = 0; i < mr_.size(); ++i) {
      mr_[i]->set_pool_index(i);
    }
  }

  Allocator(std::initializer_list<MemoryPool*> memory_pools) {
    for (MemoryPool* pool : memory_pools) {
      mr_.push_back(pool);
    }
    for (int i = 0; i < mr_.size(); ++i) {
      mr_[i]->set_pool_index(i);
    }
  }

  template <typename U>
  Allocator(const Allocator<U>& other) noexcept : mr_(other.mr_) {}

  pointer allocate(size_t n) {
    size_t allocation_size = n * sizeof(T);

    auto it = std::find_if(
        mr_.begin(), mr_.end(), [allocation_size](MemoryPool* pool) {
          return !pool->empty() && pool->chunk_size() >= allocation_size;
        });

    if (it == mr_.end()) {
      throw std::bad_alloc();
    }

    return (T*)((*it)->allocate(allocation_size));
  }

  void deallocate(T* p, size_t n) {
    MemoryPool::DataHeader* header_address =
        reinterpret_cast<MemoryPool::DataHeader*>(
            (char*)p - sizeof(MemoryPool::DataHeader));
    return mr_[header_address->pool_index]->deallocate((void*)(p));
  }
};
