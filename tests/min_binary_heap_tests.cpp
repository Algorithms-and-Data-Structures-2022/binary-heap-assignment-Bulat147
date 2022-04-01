#include <catch2/catch.hpp>

#include "testing_min_binary_heap.hpp"

using MinBinaryHeap = assignment::TestingMinBinaryHeap;
using assignment::Node;

using Catch::Equals;

SCENARIO("MinBinaryHeap::MinBinaryHeap") {

  SECTION("capacity > 0") {
    const int capacity = GENERATE(range(1, 11));

    const auto heap = MinBinaryHeap(capacity);

    CHECK(heap.IsEmpty());
    CHECK(heap.size() == 0);
    CHECK(heap.capacity() == capacity);

    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{}));
  }

  SECTION("capacity <= 0") {
    const int capacity = GENERATE(range(-10, 1));
    CHECK_THROWS(MinBinaryHeap(capacity));
  }
}

SCENARIO("MinBinaryHeap::Insert") {

  SECTION("size < capacity") {
    constexpr int capacity = 1 + 2 + 4 + 8;
    auto heap = MinBinaryHeap(capacity);

    REQUIRE(heap.IsEmpty());
    REQUIRE(heap.capacity() == capacity);

    CHECK(heap.Insert(2, 1));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{2, 1}}));

    CHECK(heap.Insert(1, 0));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{1, 0}, {2, 1}}));

    CHECK(heap.Insert(36, 6));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{1, 0}, {2, 1}, {36, 6}}));

    CHECK(heap.Insert(25, 7));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{1, 0}, {2, 1}, {36, 6}, {25, 7}}));

    CHECK(heap.Insert(19, 4));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{1, 0}, {2, 1}, {36, 6}, {25, 7}, {19, 4}}));

    CHECK(heap.Insert(40, 5));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{1, 0}, {2, 1}, {36, 6}, {25, 7}, {19, 4}, {40, 5}}));

    CHECK(heap.Insert(7, 2));
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{1, 0}, {2, 1}, {7, 2}, {25, 7}, {19, 4}, {40, 5}, {36, 5}}));

    CHECK(heap.Insert(17, 3));
    CHECK_THAT(heap.toVector(),
               Equals(std::vector<Node>{{1, 0}, {2, 1}, {7, 2}, {17, 3}, {19, 4}, {40, 5}, {36, 5}, {25, 7}}));

    CHECK(heap.Insert(100, 8));
    CHECK_THAT(
        heap.toVector(),
        Equals(std::vector<Node>{{1, 0}, {2, 1}, {7, 2}, {17, 3}, {19, 4}, {40, 5}, {36, 5}, {25, 7}, {100, 8}}));
  }

  SECTION("size == capacity") {
    const int capacity = GENERATE(range(1, 11));
    const int insert_key = GENERATE(take(10, random(-100, 100)));
    const int insert_value = GENERATE(take(5, random(-100, 100)));

    auto arr = std::vector<Node>(capacity);

    for (int index = 0; index < arr.size(); ++index) {
      arr[index] = Node(index, index);
    }

    auto heap = MinBinaryHeap(arr, capacity);

    const bool inserted = heap.Insert(insert_key, insert_value);

    CHECK_FALSE(inserted);
    CHECK(heap.size() == capacity);
    CHECK_THAT(heap.toVector(), Equals(arr));
  }
}

SCENARIO("MinBinaryHeap::Extract") {
  const auto tree_data = std::vector<Node>{{1, 0}, {2, 1}, {3, 2}, {17, 3}, {19, 4}, {36, 5}, {7, 6}};

  auto heap = MinBinaryHeap(tree_data, static_cast<int>(tree_data.size()));

  REQUIRE(heap.size() == tree_data.size());
  REQUIRE(heap.capacity() == tree_data.size());
  REQUIRE_THAT(heap.toVector(), Equals(tree_data));

  auto extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 0);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{2, 3}, {7, 6}, {3, 2}, {17, 3}, {19, 4}, {36, 5}}));

  extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 1);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{3, 2}, {7, 6}, {36, 5}, {17, 3}, {19, 4}}));

  extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 2);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{7, 6}, {17, 3}, {36, 5}, {19, 4}}));

  extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 6);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{17, 3}, {19, 4}, {36, 5}}));

  extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 3);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{19, 4}, {36, 5}}));

  extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 4);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{36, 5}}));

  extracted = heap.Extract();

  REQUIRE(extracted.has_value());
  CHECK(extracted.value() == 5);
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{}));

  extracted = heap.Extract();

  REQUIRE_FALSE(extracted.has_value());
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{}));

  CHECK(heap.capacity() == tree_data.size());
}

SCENARIO("MinBinaryHeap::Remove") {
  const auto tree_data = std::vector<Node>{{1, 0}, {2, 1}, {3, 2}, {17, 3}, {19, 4}, {36, 5}, {7, 6}};

  auto heap = MinBinaryHeap(tree_data, static_cast<int>(tree_data.size()));

  REQUIRE(heap.size() == tree_data.size());
  REQUIRE(heap.capacity() == tree_data.size());
  REQUIRE_THAT(heap.toVector(), Equals(tree_data));

  SECTION("non-existing key") {
    const auto removed = heap.Remove(0);

    CHECK_FALSE(removed);
    CHECK_THAT(heap.toVector(), Equals(tree_data));
  }

  SECTION("existing keys") {

    // root
    auto removed = heap.Remove(1);

    CHECK(removed);
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{2, 1}, {7, 6}, {3, 2}, {17, 3}, {19, 4}, {36, 5}}));

    // leaf node
    removed = heap.Remove(19);

    CHECK(removed);
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{2, 1}, {7, 6}, {3, 2}, {17, 3}, {36, 5}}));

    // internal node
    removed = heap.Remove(7);

    CHECK(removed);
    CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{{2, 1}, {17, 3},  {3, 2}, {36, 5}}));
  }

}

SCENARIO("MinBinaryHeap::Clear") {
  const auto tree_data = std::vector<Node>{{1, 0}, {2, 1}, {3, 2}, {17, 3}, {19, 4}, {36, 5}, {7, 6}};

  auto heap = MinBinaryHeap(tree_data, static_cast<int>(tree_data.size()));

  REQUIRE(heap.size() == tree_data.size());
  REQUIRE(heap.capacity() == tree_data.size());
  REQUIRE_THAT(heap.toVector(), Equals(tree_data));

  heap.Clear();

  CHECK(heap.capacity() == tree_data.size());
  CHECK_THAT(heap.toVector(), Equals(std::vector<Node>{}));
}

SCENARIO("MinBinaryHeap::Search") {
  const auto tree_data = std::vector<Node>{{1, 0}, {2, 1}, {3, 2}, {17, 3}, {19, 4}, {36, 5}, {7, 6}};

  auto heap = MinBinaryHeap(tree_data, static_cast<int>(tree_data.size()));

  REQUIRE(heap.size() == tree_data.size());
  REQUIRE(heap.capacity() == tree_data.size());
  REQUIRE_THAT(heap.toVector(), Equals(tree_data));

  SECTION("not-existing key") {
    const auto search = heap.Search(0);
    CHECK_FALSE(search.has_value());
  }

  SECTION("existing key") {
    REQUIRE(heap.Search(1).has_value());
    CHECK(heap.Search(1).value() == 0);

    REQUIRE(heap.Search(3).has_value());
    CHECK(heap.Search(3).value() == 2);

    REQUIRE(heap.Search(19).has_value());
    CHECK(heap.Search(19).value() == 4);
  }
}

SCENARIO("MinBinaryHeap::Contains") {
  const auto tree_data = std::vector<Node>{{1, 0}, {2, 1}, {3, 2}, {17, 3}, {19, 4}, {36, 5}, {7, 6}};

  auto heap = MinBinaryHeap(tree_data, static_cast<int>(tree_data.size()));

  REQUIRE(heap.size() == tree_data.size());
  REQUIRE(heap.capacity() == tree_data.size());
  REQUIRE_THAT(heap.toVector(), Equals(tree_data));

  SECTION("not-existing key") {
    const auto contains = heap.Contains(0);
    CHECK_FALSE(contains);
  }

  SECTION("existing key") {
    CHECK(heap.Contains(1));
    CHECK(heap.Contains(7));
    CHECK(heap.Contains(36));

  }
}
