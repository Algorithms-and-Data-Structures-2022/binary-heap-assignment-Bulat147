#include "assignment/min_binary_heap.hpp"

#include <algorithm>  // fill
#include <stdexcept>  // invalid_argument
#include <limits>     // numeric_limits

namespace assignment {

  MinBinaryHeap::MinBinaryHeap(int capacity) {

    if (capacity <= 0) {
      throw std::invalid_argument("capacity must be positive");
    }

    // инициализируем поля
    size_ = 0;
    capacity_ = capacity;

    // выделяем память для узлов
    data_ = new Node[capacity_];

    // заполняем массив "пустыми узлами"
    std::fill(data_, data_ + capacity_, Node{});
  }

  MinBinaryHeap::~MinBinaryHeap() {

    // обнуляем поля
    size_ = 0;
    capacity_ = 0;

    // высвобождаем выделенную память
    delete[] data_;
    data_ = nullptr;
  }

  bool MinBinaryHeap::Insert(int key, int value) {

    if (size_ == capacity_) {
      // двоичная куча заполнена, операция вставки нового узла невозможна
      return false;
    }

    // Tips:
    // 1. Вставьте новый узел в "конец" массива.
    // 2. Увеличьте размер двоичной кучи.
    // 3. Вызовите операцию sift_up над индексом вставленного элемента.

    return false;
  }

  std::optional<int> MinBinaryHeap::Extract() {

    if (size_ == 0) {
      // двоичная куча пустая, операция извлечения корня невозможна
      return std::nullopt;
    }

    // Tips:
    // 1. Сохраните значение текущего корня в переменной.
    // 2. В корень поместите последний элемент (правый нижний в куче).
    // 3. Уменьшите размер двоичной кучи.
    // 4. Вызовите функцию "спуска" узлов heapify над индексом корня.

    return std::nullopt;
  }

  bool MinBinaryHeap::Remove(int key) {

    constexpr int min_key_value = std::numeric_limits<int>::min();

    // Tips:
    // 1. Найдите индекс удаляемого узла по ключу.
    // 2. Установите ключом удаляемого узла наименьшее возможное значение ключа min_key_value.
    // 3. Вызовите над индексом удаляемого элемента функцию sift_up.
    // 4. Извлеките корневой (удаляемый) узел из кучи операцией Extract.

    return true;
  }

  void MinBinaryHeap::Clear() {
    // Write your code here ...
  }

  std::optional<int> MinBinaryHeap::Search(int key) const {
    // Write your code here ...
    return std::nullopt;
  }

  bool MinBinaryHeap::Contains(int key) const {
    return Search(key).has_value();
  }

  bool MinBinaryHeap::IsEmpty() const {
    return size_ == 0;
  }

  int MinBinaryHeap::capacity() const {
    return capacity_;
  }

  int MinBinaryHeap::size() const {
    return size_;
  }

  // вспомогательные функции

  void MinBinaryHeap::sift_up(int index) {

    // Алгоритм:
    // Пока index не равен индексу корневого узла И ключ узла меньше ключа родителя:
    //  поднимаем "наверх" узел - меняем местами нижний и верхний узлы (swap)
    //  index = индекс родительского узла

    while (index != 0 && data_[index].key < data_[parent_index(index)].key) {

      std::swap(data_[index], data_[parent_index(index)]);
      index = parent_index(index);
    }
  }

  void MinBinaryHeap::heapify(int index) {

    // индексы левого и правого потомков узла с индексом index
    const int left_index = left_child_index(index);
    const int right_index = right_child_index(index);

    // вышли за пределы массива, останавливаемся
    if (left_index >= size_) {
      return;
    }

    // индекс узла-потомка с наименьшим значением ключа
    int smallest_key_index = index;

    if (data_[left_index].key < data_[index].key) {
      smallest_key_index = left_index;
    }

    if (data_[right_index].key < data_[smallest_key_index].key) {
      smallest_key_index = right_index;
    }

    // если индекс наименьшего узла найден (не равен индексу самого узла)
    if (smallest_key_index != index) {

      // меняем местами родителя и потомка (swap)
      std::swap(data_[index], data_[smallest_key_index]);

      // рекурсивно спускаемся по куче, следуя индексу
      heapify(smallest_key_index);
    }
  }

  std::optional<int> MinBinaryHeap::search_index(int key) const {
    // Write your code here ...
    return std::nullopt;
  }

}  // namespace assignment
