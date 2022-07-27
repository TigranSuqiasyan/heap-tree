#include <iostream>
#include <vector>
#include <initializer_list>

namespace spec {

template <typename T>
class heap {
public:
  heap() = default;
  heap(int count) : m_array(count) {}
  heap(int count, const T& value) : m_array(count, value) {}
  heap(std::initializer_list<T> ilist); /*: m_array(ilist) {}*/
  heap(const heap<T>& oth) : m_array{oth.m_arr} {}
  heap(heap<T>&& oth) : m_array{oth.m_arr} {}
  ~heap() = default;

public:
  heap<T>& operator=(const heap<T>&);
  heap<T>& operator=(heap<T>&&);
  template <typename E> friend std::ostream& operator<<(std::ostream&, const heap<E>&);
  template <typename E> friend bool operator==(const heap<E>&, const heap<E>&);
  template <typename E> friend bool operator!=(const heap<E>&, const heap<E>&);
  template <typename E> friend heap<E> operator+(const heap<E>&, const heap<E>&);
  heap<T>& operator+(const heap<T>&);

public:
  void insert(const T&);
  int height() const;
  void delete_element(const T&);
  int linear_search(const T&) const;
  T extract_max_element();
  T extract_min_element();

private:
  int parent(int) const;
  int left(int) const;
  int right(int) const;
  void max_heapify(int);
  void build_max_heap();
  void min_heapify(int);
  void build_min_heap();

private:
  std::vector<T> m_array;
};

} // spec