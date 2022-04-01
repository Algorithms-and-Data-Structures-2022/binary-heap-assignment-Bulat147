#pragma once

#include <ostream>

namespace assignment {

  /**
   * Узел двоичной кучи.
   */
  struct Node final {
    // поля
    int key{0};
    int value{0};

    // конструкторы
    Node() = default;
    Node(int key, int value) : key{key}, value{value} {}

    // операторы сравнения
    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

    // оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
  };

  inline bool Node::operator==(const Node& other) const {
    return key == other.key;
  }

  inline bool Node::operator!=(const Node& other) const {
    return !(*this == other);
  }

  inline std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << '{' << node.key << ',' << node.value << '}';
    return os;
  }

}  // namespace assignment