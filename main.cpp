#include <iostream>
#include "heap-tree.cpp"

int main() {
  spec::heap<int> heap{1,8,9,6,3,0,74,58};
  std::cout << heap;
}