#include "heap-tree.hpp"
#include <initializer_list>

namespace spec {

// CONSTRUCTOR WITH INITIALIZER LIST

template <typename T>
heap<T>::heap(std::initializer_list<T> ilist) :heap() {
  auto begin = ilist.begin();
  auto end = ilist.end();
  for (; begin != end; ++begin) {
    this->insert(*begin);
  }
}

// OPERRATORS

template <typename T>
heap<T>& heap<T>::operator=(const heap<T>& rhs) {
  m_array = rhs.m_array;
  return *this;
}

template <typename T>
heap<T>& heap<T>::operator=(heap<T>&& rhs) {
  m_array = std::move(rhs.m_array);
  return *this;
}

template <typename E>
std::ostream& operator<<(std::ostream& os, const heap<E>& heap) {
  for (const auto& elem : heap.m_array) {
    os << elem << " ";
  }
  return os;
}

template <typename E>
bool operator==(const heap<E>& lhs, const heap<E>& rhs) {
  if (lhs.m_array.size() != rhs.m_array.size())
    return false;
  int size = lhs.m_array.size();
  for (int i{}; i < size; ++i) 
    if (lhs.m_array[i] != rhs.m_array[i])
      return false;
  return true;
}

template <typename E>
bool operator!=(const heap<E>& lhs, const heap<E>& rhs) {
  return !(lhs == rhs);
}

template <typename E>
heap<E> operator+(const heap<E>& lhs, const heap<E>& rhs) {
  heap<E> result(lhs.m_array.size() + rhs.m_array.size());
  int left_size = lhs.m_array.size();
  int right_size = rhs.m_array.size();
  for (int i{}; i < left_size; ++i)
    result.m_array[i] = lhs.m_array[i];
  for (int j{}; j < right_size; ++j)
    result[j + left_size] = rhs.m_array[j];
  return result;
}

// MAIN FUNCTIONALITY

template <typename T>
void heap<T>::insert(const T& value) {
  this->m_array.push_back(value);
  this->build_max_heap();
}

template <typename T>
int heap<T>::parent(int child) const {
  if (child)
    return (child - 1) / 2;
  return -1;
}

template <typename T>
int heap<T>::left(int parent) const {
  if ((2 * parent + 1) < this->m_array.size())
    return 2 * parent + 1;
  return -1;
}

template <typename T>
int heap<T>::right(int parent) const {
  if ((2 * parent + 2) < this->m_array.size())
    return 2 * parent + 2;
  return -1;
}

template <typename T>
int heap<T>::height() const {
  int height{};
  int index{};
  while (left(index) != -1) {
    ++height;
    index = left(index);
  }
  return height;
}

template <typename T>
void heap<T>::delete_element(const T& value) {
  std::remove(m_array.begin(), m_array.end(), value);
}

template <typename T>
int heap<T>::linear_search(const T& value) const {
  int size = m_array.size();
  for (int i{}; i < size; ++i)
    if (m_array[i] == value)
      return i;
  return -1;
}

template <typename T>
void heap<T>::max_heapify(int parent) {
  int maximum = parent;
  int l = left(parent);
  int r = right(parent);
  if ((r != -1) && (m_array[r] > m_array[maximum]))
    maximum = r;
  if ((l != -1) && (m_array[l] > m_array[maximum]))
    maximum = l;
  if (maximum != parent) {
    std::swap(m_array[maximum], m_array[parent]);
    max_heapify(maximum);
  }
}

template <typename T>
void heap<T>::build_max_heap() {
  int size = m_array.size();
  for (int i{size / 2}; i >= 0; --i) {
    max_heapify(i);
  }
}

template <typename T>
T heap<T>::extract_max_element() {
  this->build_max_heap();
  if (!m_array.size())
    throw std::out_of_range("no more elements left");
  T temp = m_array[0];
  m_array.erase(m_array.begin());
  return temp;
}

template <typename T>
void heap<T>::min_heapify(int parent) {
  int minimum = parent;
  int l = left(parent);
  int r = right(parent);
  if ((r != -1) && m_array[r] < m_array[minimum])
    minimum = r;
  if ((l != -1) && m_array[l] < m_array[minimum])
    minimum = l;
  if (minimum != parent) {
    std::swap(m_array[minimum], m_array[parent]);
    max_heapify(minimum);
  }
}

template <typename T>
void heap<T>::build_min_heap() {
  int size = m_array.size();
  for (int i{size / 2}; i >= 0; --i) {
    min_heapify(i);
  }
}

template <typename T>
T heap<T>::extract_min_element() {
  this->build_min_heap();
  if (!m_array.size())
    throw std::out_of_range("no more elements left");
  T temp = m_array[0];
  m_array.erase(m_array.begin());
  return temp;
}

} // spec