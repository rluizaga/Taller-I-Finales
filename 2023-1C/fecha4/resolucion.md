**1) Que es un namespace? Para que se utiliza? Ejemplifique.**
Un namespace (espacio de nombres) es una característica en C++ que permite agrupar un conjunto de identificadores (como variables, funciones, clases, etc.) en un ámbito separado y único. Los namespaces son utilizados para evitar conflictos de nombres entre diferentes componentes y bibliotecas en un programa. Proporcionan una forma de organizar y estructurar el código de manera más ordenada y modular.

Los namespaces son particularmente útiles cuando se trabaja en proyectos grandes o cuando se utilizan bibliotecas externas, ya que evitan colisiones de nombres y permiten que diferentes componentes compartan nombres similares sin conflictos.

Ejemplo de uso de namespace:

```cpp
#include <iostream>

namespace MiNamespace {
    int numero = 42;

    void saludar() {
        std::cout << "¡Hola desde MiNamespace!" << std::endl;
    }
}

int main() {
    std::cout << MiNamespace::numero << std::endl; // Acceso a la variable en el namespace
    MiNamespace::saludar(); // Llamada a la función en el namespace

    return 0;
}
```

En este ejemplo, se define un namespace llamado `MiNamespace`. Dentro de ese namespace se declara una variable `numero` y una función `saludar()`. Al utilizar `MiNamespace::`, indicamos que estamos accediendo a los elementos dentro de ese namespace. Esto ayuda a evitar conflictos de nombres y hace que el código sea más claro y organizado.

En resumen, los namespaces son una forma de encapsular y organizar los identificadores en C++, evitando colisiones de nombres y permitiendo una mejor estructuración del código en proyectos más grandes.

**2) Escriba las siguientes definiciones/declaraciones:**
- **Declaracion de un arreglo de 1 puntero a entero con signo, llamado A.**
- **Definicion de un nro. de punto flotante de doble precision, visible en todos los modulos, llamado B.**
- **Definicion de la funcion DIV, que tome dos nros. de puntos flotante y que devuelva su division. Esta funcion debe ser visible solo en el archivo donde fue definida.**

```c
// Declaracion de un arreglo de 1 puntero a entero con signo, llamado A.
int* A[1];


// Definicion de un nro. de punto flotante de doble precision, visible en todos los modulos, llamado B.
extern double B;
double B = 3.14159;

// Definicion de la funcion DIV, que tome dos nros. de puntos flotante y que devuelva su division. Esta funcion debe ser visible solo en el archivo donde fue definida.
static double DIV(double a, double b) {
    if (b != 0.0) {
        return a / b;
    } else {
        return 0.0;
    }
}
```

**3) Que es un metodo virtual? Que diferencias ofrece frente a uno convencional? Codifique un ejemplo con un uso imprecindible.**
Un método virtual en C++ es un método de una clase base que se declara con la palabra clave `virtual`. Los métodos virtuales permiten que las clases derivadas (subclases) proporcionen su propia implementación de ese método, lo que permite la sobrescritura del método en las clases derivadas. Esto es fundamental para lograr el polimorfismo en C++, lo que significa que se puede usar un puntero o referencia a una clase base para acceder a objetos de diferentes clases derivadas y que el método invocado será el de la clase derivada en tiempo de ejecución.

Diferencias entre un método virtual y uno convencional:
- Un método virtual se declara usando la palabra clave `virtual`, mientras que un método convencional no lo hace.
- Un método virtual en la clase base puede ser sobrescrito en las clases derivadas, mientras que un método convencional en la clase base no puede ser sobrescrito en las clases derivadas.
- Cuando se invoca un método virtual a través de un puntero o referencia a la clase base, se resuelve dinámicamente en tiempo de ejecución para ejecutar el método de la clase derivada, mientras que con un método convencional se ejecuta el método de la clase base.

Aquí tienes un ejemplo simple de uso de un método virtual:

```cpp
#include <iostream>

class Figura {
public:
    virtual double area() const {
        return 0.0;
    }
};

class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(double r) : radio(r) {}

    double area() const override {
        return 3.14159 * radio * radio;
    }
};

class Rectangulo : public Figura {
private:
    double base;
    double altura;

public:
    Rectangulo(double b, double h) : base(b), altura(h) {}

    double area() const override {
        return base * altura;
    }
};

int main() {
    Circulo circulo(5.0);
    Rectangulo rectangulo(4.0, 3.0);

    Figura* figuras[] = { &circulo, &rectangulo };

    for (Figura* figura : figuras) {
        std::cout << "Área: " << figura->area() << std::endl;
    }

    return 0;
}
```

En este ejemplo, la clase base `Figura` tiene un método virtual `area()` que puede ser sobrescrito por las clases derivadas `Circulo` y `Rectangulo`. El bucle en la función `main()` muestra cómo se utiliza el polimorfismo para calcular el área de diferentes figuras sin necesidad de saber específicamente qué tipo de figura es.

**4) Implemente un programa de 2 threads (producer-consumer) que genere e imprima los numremos del 100 al 1.**
En este caso, el productor generará números del 100 al 1 y los enviará a un buffer compartido, mientras que el consumidor los imprimirá desde el buffer.
```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;

bool finished = false;

void producer() {
    for (int i = 100; i >= 1; --i) {
        std::unique_lock<std::mutex> lock(mtx);
        buffer.push(i);
        cv.notify_one();
    }

    std::unique_lock<std::mutex> lock(mtx);
    finished = true;
    cv.notify_one();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !buffer.empty() || finished; });

        if (!buffer.empty()) {
            int num = buffer.front();
            buffer.pop();
            std::cout << num << std::endl;
        }

        if (finished && buffer.empty()) {
            break;
        }
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
```
**5) Que es una condicional variable (std::condition_variable)? Ejemplifique.**
Una `std::condition_variable` es una clase en la biblioteca estándar de C++ que se utiliza para sincronizar la ejecución de hilos en base a ciertas condiciones. Proporciona una forma de poner a un hilo en espera hasta que otra parte del código cumpla una determinada condición, y luego notificar al hilo en espera para que continúe su ejecución.

Aquí tienes un ejemplo simple para ilustrar cómo se usa una `std::condition_variable`:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });  // Espera hasta que "ready" sea verdadero
    std::cout << "Worker thread is working!" << std::endl;
}

int main() {
    std::thread t(worker_thread);

    // Realizar alguna tarea en el hilo principal...

    // Ahora, estamos listos para que el hilo de trabajo continúe
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();  // Notifica al hilo de trabajo

    t.join();

    return 0;
}
```

En este ejemplo, el hilo principal espera a que el hilo de trabajo esté listo para continuar. La `std::condition_variable` `cv` se utiliza junto con un mutex `mtx` para lograr esto. El hilo de trabajo espera en `cv.wait(lock, predicate)` hasta que `ready` se establezca como verdadero en el hilo principal. Cuando el hilo principal establece `ready` como verdadero y llama a `cv.notify_one()`, el hilo de trabajo se despierta y continúa su ejecución.

En resumen, una `std::condition_variable` es una herramienta esencial para sincronizar y coordinar la ejecución de hilos en situaciones donde uno o más hilos deben esperar hasta que se cumpla cierta condición antes de continuar.

**6) Escriba un programa que reciba por linea de comandos un Puerto. El programa debe conectarse al puerto indicado y quedar a la espera de recibir paquetes limitados por "[" y "]" (ej. [paquete1][paquete2]). El programa debera imprimir por stdout los paquetes de largo par. Cuando se reciba un paquete vacio([]) se debe finalizar ordenadamente.**
Resuelto.

**7) Declare la clase stack para encapsular una pila de elementos genericos tipo T (template) implementada con memoria dinamica. Considere:**
**a) Atributos que necesitamos**
**b) Accesibilidad a los atributos y metodos de la clase.**
**c) Incluir los operadores +, ==, << (impresion), >> (carga desde consola), int (cast a int)**

```c++
template <typename T> class Stack {
private:
  T *arr;
  T top;
  int capacity;

public:
  Stack(int size = SIZE);
  ~Stack();

  void push(T x);
  T pop();
  T peek() const;

  int size() const;
  bool isEmpty() const;
  bool isFull() const;

  Stack<T> operator+(const Stack<T> &other) const;
  bool operator==(const Stack<T> &other) const;
  operator int() const;

  template <typename U>
  friend ostream &operator<<(ostream &os, const Stack<U> &stack);

  template <typename U>
  friend istream &operator>>(istream &is, Stack<U> &stack);
};
```

**8) Escriba una rutina que tome el contenido de un edit (ej.: "conTenido oRIGINal"), lo formatee en "Camel Case" (ej.: "Contenido Original") y lo vuelva a guardar en el mismo edit.**
Resuelto

**9) Explique y ejemplifique el uso de la directiva de precompilacion #include**
La directiva de precompilación `#include` se utiliza en lenguajes como C y C++ para incluir el contenido de un archivo en otro archivo fuente durante el proceso de compilación. Esta directiva es útil cuando se desea utilizar código desde otros archivos, como bibliotecas, encabezados o módulos personalizados, sin tener que copiar y pegar manualmente ese código en cada archivo.

Hay dos formas principales de usar `#include`:

1. **Incluir archivos de biblioteca estándar**: Puedes incluir archivos de biblioteca estándar proporcionados por el compilador o el lenguaje. Estos archivos contienen declaraciones y definiciones de funciones, clases y otros elementos que puedes usar en tu programa. Ejemplo:

```cpp
#include <iostream> // Incluye el archivo de encabezado de la biblioteca iostream
```

2. **Incluir archivos personalizados**: Puedes incluir tus propios archivos de encabezado o módulos personalizados que contengan declaraciones y definiciones necesarias para tu programa. Ejemplo:

```cpp
#include "mi_archivo.h" // Incluye tu propio archivo de encabezado
```

Un ejemplo más completo:

Supongamos que tienes dos archivos: `main.cpp` y `mi_archivo.h`.

Archivo `mi_archivo.h`:
```cpp
// mi_archivo.h
#ifndef MI_ARCHIVO_H
#define MI_ARCHIVO_H

void saludar() {
    std::cout << "¡Hola desde mi_archivo.h!" << std::endl;
}

#endif // MI_ARCHIVO_H
```

Archivo `main.cpp`:
```cpp
// main.cpp
#include <iostream>
#include "mi_archivo.h"

int main() {
    std::cout << "Hola desde main.cpp" << std::endl;
    saludar(); // Llamamos a la función definida en mi_archivo.h
    return 0;
}
```

En este ejemplo, el uso de `#include` permite que el contenido de `mi_archivo.h` sea insertado en `main.cpp`, de modo que la función `saludar()` definida en `mi_archivo.h` puede ser utilizada en `main.cpp`.

**10) Escribir un programa ISO C Multiplataforma que procese el archivo "base5.txt" sobre si mismo. El procesamiento consiste en leer numeros base 5 de 6 simbolos y duplicar aquellos multiplos de 23.**
Resuelto