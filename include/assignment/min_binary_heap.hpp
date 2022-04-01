#pragma once

#include <vector>
#include <utility>  // swap

#include "assignment/private/node.hpp"         // Node
#include "assignment/private/binary_heap.hpp"  // BinaryHeap

namespace assignment {

  inline constexpr int parent_index(int index) {
    return (index - 1) / 2;
  }

  inline constexpr int left_child_index(int index) {
    return 2 * index + 1;
  }

  inline constexpr int right_child_index(int index) {
    return 2 * index + 2;
  }

  struct MinBinaryHeap : BinaryHeap {
   protected:
    int size_{0};
    int capacity_{0};
    Node* data_{nullptr};

   public:
    // максимальное кол-во узлов: 5 уровней полного двоичного дерева
    static constexpr int kDefaultCapacity = 1 + 2 + 4 + 8 + 16;

    explicit MinBinaryHeap(int capacity = kDefaultCapacity);

    ~MinBinaryHeap() override;

    bool Insert(int key, int value) override;

    std::optional<int> Extract() override;

    bool Remove(int key) override;

    void Clear() override;

    std::optional<int> Search(int key) const override;

    bool Contains(int key) const override;

    bool IsEmpty() const override;

    int capacity() const override;

    int size() const override;

   private:
    void sift_up(int index);
    void heapify(int index);
    std::optional<int> search_index(int key) const;
  };

}  // namespace assignment
