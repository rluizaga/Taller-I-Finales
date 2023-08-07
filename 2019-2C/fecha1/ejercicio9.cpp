/*
9) Implemente una función C++ denominada Sacar que reciba dos listas de
elementos y devuelva una nueva lista con los elementos de la primera que no
están en la segunda: std::list<T> Sacar(std::list<T> a,std::list<T> b);
*/

#include <iostream>
#include <list>
#include <algorithm>

template <typename T> std::list<T> sacar(std::list<T> a, std::list<T> b) {
  std::list<T> result;

  for (auto elem : a) {
    if(!(std::find(b.begin(), b.end(), elem) == b.end())) {
      result.push_back(elem);
    }
  }

  return result;
}

int main() {
  std::list<int> a = {1,2,3,4,5,6,7,8,9,10};
  std::list<int> b = {4,5,6};

  std::list<int> result;

  result = sacar(a, b);

  // Imprimir resultado
  for (auto i : result) {
    std::cout << i << " " << std::endl;
  }

  return 0;
}