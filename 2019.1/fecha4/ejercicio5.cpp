/*
Implemente una función C++ denominada DobleSegunda que reciba dos listas de elementos
y devuelva una nueva lista duplicando los elementos de la primera si están en la segunda:
               std::list<T> DobleSegunda(std::list<T> a,std::list<T> b);
*/

#include <iostream>
#include <list>
#include <algorithm>

template <typename T>
std::list<T> DobleSegunda(std::list<T> a, std::list<T> b) {
    std::list<T> result;

    // Iteramos sobre los elementos de la primera lista (a).
    for (const auto& elem : a) {
        // Añadimos el elemento a la lista de resultado.
        result.push_back(elem);

        // Si el elemento también está en la segunda lista (b), lo añadimos una vez más.
        if (!(std::find(b.begin(), b.end(), elem) == b.end())) {
            result.push_back(elem);
        }
    }

    return result;
}

int main() {
    // Crear las dos listas de ejemplo.
    std::list<std::string> lista1 = {"ho", "la", "co", "mo", "es"};
    std::list<std::string> lista2 = {"la", "co", "ta"};

    // Llamar a la función DobleSegunda y obtener la lista resultante.
    std::list<std::string> resultado = DobleSegunda(lista1, lista2);

    // Imprimir la lista resultante.
    std::cout << "Lista resultante: ";
    for (const auto& elem : resultado) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
