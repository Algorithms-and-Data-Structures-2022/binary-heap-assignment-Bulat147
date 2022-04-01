#pragma once

#include <optional>

namespace assignment {

  struct BinaryHeap {

    virtual ~BinaryHeap() = default;

    virtual bool Insert(int key, int value) = 0;

    virtual std::optional<int> Extract() = 0;

    virtual bool Remove(int key) = 0;

    virtual void Clear() = 0;

    virtual std::optional<int> Search(int key) const = 0;

    virtual bool Contains(int key) const = 0;

    virtual bool IsEmpty() const = 0;

    virtual int capacity() const = 0;

    virtual int size() const = 0;
  };

}  // namespace assignment