#pragma once

#include <vector>
#include <utility>  // swap

#include "assignment/private/node.hpp"         // Node
#include "assignment/private/binary_heap.hpp"  // BinaryHeap

namespace assignment {

  /**
   * Возвращает индекс родительского узла.
   *
   * @param index - индекс узла
   * @return индекс родительского узла
   */
  inline constexpr int parent_index(int index) {
    return (index - 1) / 2;
  }

  /**
   * Возвращает индекс левого потомка для узла.
   *
   * @param index - индекс узла
   * @return индекс левого потомка
   */
  inline constexpr int left_child_index(int index) {
    return 2 * index + 1;
  }

  /**
   * Возвращает индекс правого потомка для узла.
   *
   * @param index - индекс узла
   * @return индекс правого потомка
   */
  inline constexpr int right_child_index(int index) {
    return 2 * index + 2;
  }

  /**
   * Структура данных "двоичная куча".
   *
   * Представляется из себя сбалансированное дерево.
   * Узлы в куче располагаются по уровням слева направо без "пустот".
   * Родительские узлы в минимальной двоичной куче (Min-heap) должны быть меньше или равны потомкам.
   *
   * В памяти эффективно представляется одномерным массивом.
   *
   * Индексация узлов в массиве:
   *  0 - корневой узел
   *  2*i + 1 - левый потомок узла i
   *  2*i + 2 - правый потомок узла i
   *  (i - 1)/2 - родитель узла i
   */
  struct MinBinaryHeap : BinaryHeap {
   protected:
    // поля структуры
    int size_{0};
    int capacity_{0};
    Node* data_{nullptr};

   public:
    // максимальное кол-во узлов в двоичной куче (элементов в массиве)
    static constexpr int kDefaultCapacity = 1 + 2 + 4 + 8 + 16;

    /**
     * Создание двоичной кучи указанной емкости.
     *
     * Емкость кучи ограничена и не может быть изменена.
     *
     * @param capacity - значение емкости двоичной кучи
     */
    explicit MinBinaryHeap(int capacity = kDefaultCapacity);

    /**
     * высвобождение выделенной памяти.
     *
     * Поля устанавливаются в нулевые значения.
     */
    ~MinBinaryHeap() override;

    /**
     * Вставка узла в двоичную кучу.
     *
     * Разрешена вставка существующих ключей.
     *
     * @param key - значение ключа
     * @param value - хранимые данные
     * @return true - успешная вставка, false - при превышении значения емкости
     */
    bool Insert(int key, int value) override;

    /**
     * Извлечение корневого узла из двоичной кучи.
     *
     * Происходит удаление корня и перестройка кучи с установкой нового корневого узла.
     *
     * @return хранимые данные корневого узла или ничего (при пустой куче)
     */
    std::optional<int> Extract() override;

    /**
     * Удаление узла из двоичной кучи по ключу.
     *
     * @param key - значение ключа удаляемого узла
     * @return true - успешное удаление, false - узел с ключом не найден
     */
    bool Remove(int key) override;

    /**
     * Очистка двоичной кучи.
     *
     * Сброс текущего размера кучи до нулевого значения.
     * Выделенная память не высвобождается.
     */
    void Clear() override;

    /**
     * Поиск узла по ключу в двоичной куче.
     *
     * @param key - значение ключа
     * @return хранимые данные или ничего (если узел с ключом не найден)
     */
    std::optional<int> Search(int key) const override;

    /**
     * Проверка наличия узла в двоичной куче по ключу.
     *
     * @param key - значение ключа
     * @return true - узел найден, false - узла с ключом не существует
     */
    bool Contains(int key) const override;

    /**
     * Проверка пустоты двоичной кучи.
     *
     * @return true - куча пустая, false - куча не пустая
     */
    bool IsEmpty() const override;

    /**
     * Возвращает установленную емкость двоичной кучи.
     *
     * @return значение емкости
     */
    int capacity() const override;

    /**
     * Возвращает текущий размер двоичной кучи.
     *
     * @return значение кол-ва узлов в куче
     */
    int size() const override;

   private:
    /**
     * Поднятие узла с указанным индексом по двоичной куче.
     *
     * Является операцией поддерживающей балансировку двоичной кучи.
     *
     * @param index - значение индекса поднимаемого узла
     */
    void sift_up(int index);

    /**
     * Спуск узла с указанным индексом по двоичной куче.
     *
     * Является операцией поддерживающей балансировку двоичной кучи.
     *
     * @param index - значение индекса спускаемого узла
     */
    void heapify(int index);

    /**
     * Поиск индекса узла по ключу.
     *
     * @param key - значение ключа узла
     * @return индекс найденного узла или ничего (при его отсутствии)
     */
    std::optional<int> search_index(int key) const;
  };

}  // namespace assignment
