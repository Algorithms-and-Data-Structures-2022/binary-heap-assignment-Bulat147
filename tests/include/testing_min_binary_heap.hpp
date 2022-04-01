#pragma once

#include <vector>
#include <algorithm>  // copy

#include "assignment/min_binary_heap.hpp"  // MinBinaryHeap

namespace assignment {

  struct TestingMinBinaryHeap : MinBinaryHeap {

    explicit TestingMinBinaryHeap(int capacity) : MinBinaryHeap(capacity) {}

    std::vector<Node> toVector() const {
      return {data_, data_ + size_};
    }

    TestingMinBinaryHeap(const std::vector<Node>& nodes, int capacity) {

      size_ = static_cast<int>(nodes.size());
      capacity_ = capacity;

      data_ = new Node[capacity_];
      std::copy(nodes.data(), nodes.data() + size_, data_);
    }
  };

}  // namespace assignment