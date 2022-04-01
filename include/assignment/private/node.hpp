#pragma once

#include <ostream>

namespace assignment {

  struct Node final {
    int key{0};
    int value{0};

    Node() = default;

    Node(int key, int value) : key{key}, value{value} {}

    bool operator==(const Node& other) const {
      return key == other.key;
    }

    bool operator!=(const Node& other) const {
      return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& node);
  };

  inline std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << '{' << node.key << ',' << node.value << '}';
    return os;
  }

}  // namespace assignment