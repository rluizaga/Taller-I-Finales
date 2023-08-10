/*
Implemente una función C++ denominada DobleSiNo que reciba dos listas de
elementos y devuelva una nueva lista  duplicando   los   elementos   de   la
primera   que   no   están   en   la segunda: std::list<T>
DobleSiNo(std::list<T> a,std::list<T> b);
*/

#include <algorithm>
#include <iostream>
#include <list>

template <typename T> std::list<T> doble_sino(std::list<T> a, std::list<T> b) {
  std::list<T> c;

  for (auto elem : a) {
    c.push_back(elem);
    if (std::find(b.begin(), b.end(), elem) == b.end()) {
      c.push_back(elem);
    }
  }

  return c;
}

int main() {
  std::list<int> a = {1, 2, 3, 4, 5};
  std::list<int> b = {1, 2, 4, 5};
  std::list<int> c;
  c = doble_sino(a, b);

  std::cout << "Lista c: ";
  std::for_each(c.begin(), c.end(), [](int elem) { std::cout << elem << " "; });
  std::cout << std::endl;

  return 0;
}
