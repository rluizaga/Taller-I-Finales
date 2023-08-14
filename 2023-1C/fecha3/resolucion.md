**1) Declare una clase QUEUE para encapsular una cola doblemente enlazada de elementos  genericos tipo T (template) implementada con memoria dinamica. Considere:** 
- **Atributos necesarios**
- **Accesibilidad a los atributos y metodos de la clase** 
- **Incluir los operadores +, ==, <<(impresion), >> (carga desde consola), int (cast a int)**
  
```c++
template <typename T>
class QUEUE {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;
        Node(const T& value);
    };

    Node* front;
    Node* rear;

public:
    QUEUE();
    void enqueue(const T& value);
    void dequeue();
    bool isEmpty() const;
    friend std::ostream& operator<<(std::ostream& os, const QUEUE<T>& queue);
    friend std::istream& operator>>(std::istream& is, QUEUE<T>& queue);
    operator int() const;
    QUEUE<T> operator+(const QUEUE<T>& other) const;
    bool operator==(const QUEUE<T>& other) const;
    ~QUEUE();
};
```

**2) Que es un iterador de STL? Ejemplifique.**
Un iterador en el contexto de la STL (Standard Template Library) de C++ es un objeto que proporciona una forma de acceder secuencialmente a los elementos de un contenedor, como un vector, una lista, un conjunto, un mapa, entre otros. Los iteradores permiten recorrer los elementos de un contenedor sin tener que preocuparse por los detalles de su implementación subyacente.

Los iteradores actúan como punteros, permitiendo acceder a los elementos del contenedor y avanzar o retroceder a través de ellos. Cada tipo de contenedor proporciona su propio conjunto de iteradores con diferentes capacidades y restricciones.

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> miVector = {1, 2, 3, 4, 5};

    // Usando un iterador para recorrer el vector
    std::vector<int>::iterator it;
    for (it = miVector.begin(); it != miVector.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
```

**Explique que es cada uno de los siguientes, haciendo referencia a su scope, lifetime, valor de inicializacion, y el area de memoria donde reside:**
**a) Una variable global static**
**b) Una variable global**
**c) Una variable local static**
**d) Una variable local**
**e) Un atributo de clase static**
**f) Un atributo de clase**

a) Una variable global static:
- **Scope:** El alcance de una variable global static es global, lo que significa que es accesible en todo el archivo donde se declara.
- **Lifetime:** La variable global static tiene una duración durante toda la ejecución del programa, desde que se inicializa hasta el final de la ejecución.
- **Valor de inicialización:** Si no se proporciona un valor de inicialización, la variable global static se inicializará automáticamente a cero (0) o a un valor nulo si es un puntero.
- **Área de memoria:** La variable global static se almacena en el segmento de datos estáticos.

b) Una variable global:
- **Scope:** Al igual que una variable global static, la variable global tiene un alcance global en todo el archivo donde se declara.
- **Lifetime:** La variable global tiene una duración durante toda la ejecución del programa, desde que se inicializa hasta el final de la ejecución.
- **Valor de inicialización:** Al igual que una variable global static, si no se proporciona un valor de inicialización, la variable global se inicializará automáticamente a cero (0) o a un valor nulo si es un puntero.
- **Área de memoria:** La variable global se almacena en el segmento de datos.

c) Una variable local static:
- **Scope:** El alcance de una variable local static es local a la función o bloque donde se declara.
- **Lifetime:** La variable local static tiene una duración durante toda la ejecución del programa, pero su alcance es limitado a la función o bloque donde se declara.
- **Valor de inicialización:** Al igual que con otras variables estáticas, si no se proporciona un valor de inicialización, se inicializará automáticamente a cero (0) o a un valor nulo si es un puntero.
- **Área de memoria:** La variable local static se almacena en el segmento de datos estáticos.

d) Una variable local:
- **Scope:** El alcance de una variable local está limitado al bloque o función donde se declara.
- **Lifetime:** La variable local tiene una duración que abarca desde el momento en que se declara hasta el final del bloque o función en el que se encuentra.
- **Valor de inicialización:** Una variable local no estática no se inicializa automáticamente. Su valor dependerá de lo que se le asigne o del estado anterior de la memoria en ese lugar.
- **Área de memoria:** La variable local se almacena en la pila.

e) Un atributo de clase static:
- **Scope:** El alcance de un atributo de clase static es global dentro de la clase y se comparte entre todas las instancias de la clase.
- **Lifetime:** El atributo de clase static tiene una duración durante toda la ejecución del programa.
- **Valor de inicialización:** Un atributo de clase static se inicializa automáticamente a cero (0) o a un valor nulo si es un puntero si no se proporciona un valor de inicialización.
- **Área de memoria:** El atributo de clase static se almacena en el segmento de datos estáticos.

f) Un atributo de clase:
- **Scope:** El alcance de un atributo de clase es global dentro de la clase y se comparte entre todas las instancias de la clase.
- **Lifetime:** El atributo de clase tiene una duración que coincide con el tiempo de vida de la instancia de la clase que lo contiene.
- **Valor de inicialización:** Un atributo de clase no estático se inicializa automáticamente según sus constructores o puede ser inicializado en el constructor de la clase.
- **Área de memoria:** El atributo de clase se almacena en la memoria asociada con cada instancia de la clase.

**4) Escribir una funcion ISO C prototipada `int copiar(FILE *f, unsigned offSetTo, unsigned offSetFrom, unsigned length)` que copie a la posicion offSetTo (para adelante o para atras) el contenido del archivo f delimitado por lenght bytes desde offSetFrom. La funcion debe devolver un entero con el siguiente significado: 0 -> ok o <0 -> errores**
Resuelto

**5) Como se logra que dos threads accedan (lectura/escritura) a un mismo recurso compartido sin que se generen problemas de consistencia? Ejemplifique**
Esto se logra usando un mecanismo llamado mutex. Cuando un hilo necesita acceder a un recurso compartido toma el mutex mediante una operacion lock. Si un hilo intenta tomar el mutex mientras este esta bloqueado por otro hilo se quedara esperando hasta que el mutex sea liberado mediante la operacion unlock.

```c
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int globalNumber = 1;

void printEvenNumbers() {
  while (globalNumber <= 100) {
    std::lock_guard<std::mutex> lock(mtx);
    if (globalNumber % 2 == 0) {
      std::cout << "Even Thread: " << globalNumber << std::endl;
      globalNumber++;
    }
  }
}

void printOddNumbers() {
  while (globalNumber < 100) {
    std::lock_guard<std::mutex> lock(mtx);
    if (globalNumber % 2 != 0) {
      std::cout << "Odd Thread: " << globalNumber << std::endl;
      globalNumber++;
    }
  }
}

int main() {
  std::thread t1(printEvenNumbers);
  std::thread t2(printOddNumbers);

  t1.join();
  t2.join();

  return 0;
}
```

**6) Que es un Namespace? Para que se utiliza? Ejemplifique.**
Un namespace (espacio de nombres en español) en C++ es una forma de organizar y encapsular el código en grupos lógicos y separados. Los namespaces se utilizan para evitar conflictos de nombres entre diferentes elementos del programa, como variables, funciones, clases y otros símbolos. Ayudan a mantener el código ordenado, modular y fácil de entender al proporcionar un contexto para los nombres de los elementos.

Un ejemplo sencillo podría ser el siguiente:
```c++
#include <iostream>

// Definición de un namespace llamado MiNamespace
namespace MiNamespace {
    int valor = 42; // Una variable dentro del namespace
    void funcion() {
        std::cout << "Función en MiNamespace" << std::endl;
    }
}

int main() {
    std::cout << MiNamespace::valor << std::endl; // Accediendo a la variable del namespace
    MiNamespace::funcion(); // Llamando a la función del namespace

    return 0;
}
```

**7) Escriba un programa que reciba por linea de comandos un Puerto. El programa debe escuchar en el puerto indicado a la espera de una unica conexion por donde recibira paquetes de la forma [largo] [largo]... (es decir 2 bytes al principio que indican, en litle endian, el largo del paquete) y los imprima por stdout. Cuando se reciba un paquete 0000 se debe finalizar ordenadamente.**

**8) Que es una macro de precompilacion? Que buenas practicas deben adoptarse al momento de definirse?**

Una macro en C es una secuencia de código que se define utilizando la directiva del preprocesador "#define". Las macros son una forma de realizar sustituciones de texto en el código fuente antes de que comience la fase de compilación. Aquí hay algunas buenas prácticas para definir macros en C:

- Usar Nombres en Mayúsculas: Es una convención común en C utilizar nombres en mayúsculas para las macros para distinguirlas fácilmente de las variables y funciones en el código. Esto ayuda a mejorar la legibilidad y facilita la identificación de macros en el código.

- Paréntesis alrededor de los argumentos: Si la macro tiene argumentos, es importante encerrarlos en paréntesis para evitar problemas con la precedencia de operadores y asegurar que la macro funcione correctamente en todas las situaciones.

- Evitar Efectos Secundarios: Las macros pueden tener efectos secundarios inesperados, especialmente si los argumentos se evalúan más de una vez en la macro. Es importante evitar operaciones con efectos secundarios dentro de las macros para garantizar un comportamiento consistente y predecible.

- Evitar Macros Complicadas: Si una macro se vuelve demasiado complicada o difícil de entender, es preferible utilizar una función en su lugar. Las funciones en C son más seguras y fáciles de mantener que las macros complejas.

- Documentar las Macros: Es buena práctica agregar comentarios que describan el propósito y el uso de la macro para que otros desarrolladores puedan entender su función sin tener que revisar la definición de la macro.

```c
#include <stdio.h>

// Ejemplo de macro para calcular el cuadrado de un número
#define SQUARE(x) ((x) * (x))

int main() {
    int num = 5;
    int result = SQUARE(num);
    printf("El cuadrado de %d es %d\n", num, result);
    return 0;
}
```

**9) Como se declara un Constructor Move? Ejemplifique.**
Un constructor de movimiento (move constructor) es una función especial en C++ que se utiliza para realizar transferencias eficientes de recursos de un objeto a otro, en lugar de realizar copias costosas. Se declara utilizando la siguiente sintaxis:

```cpp
NombreClase(NombreClase&& otro) {
    // Realizar la transferencia eficiente de recursos aquí
}
```

Donde:
- `NombreClase` es el nombre de la clase para la cual se está declarando el constructor de movimiento.
- `otro` es una referencia rvalue al objeto del mismo tipo que se está moviendo.

Un ejemplo de un constructor de movimiento podría ser en una clase que gestiona recursos de memoria dinámica, como un `Vector` simple:

```cpp
#include <iostream>

class Vector {
private:
    size_t size;
    int* data;

public:
    Vector(size_t s) : size(s), data(new int[s]) {}

    // Constructor de movimiento
    Vector(Vector&& other) : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
    }

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Resto de la implementación de la clase...
};

int main() {
    Vector v1(5);
    Vector v2(std::move(v1)); // Llamada al constructor de movimiento

    // v1 ya no contiene recursos, v2 los ha tomado

    return 0;
}
```

En este ejemplo, hemos definido un constructor de movimiento para la clase `Vector`. Cuando creamos `v2` usando `std::move(v1)`, se invoca el constructor de movimiento, que toma eficientemente los recursos (el arreglo dinámico) del objeto `v1` y deja `v1` en un estado válido pero sin recursos. Esto es especialmente útil para mejorar el rendimiento y evitar copias costosas cuando se trabaja con objetos grandes o que gestionan recursos.

**10) Que se entiende por RAII? Por que se usa? Que ventajas ofrece? Ejemplifique.**
RAII significa "Resource Acquisition Is Initialization" (Adquisición de Recursos es Inicialización). Es un patrón de diseño en programación que se utiliza para gestionar automáticamente recursos y garantizar su correcta liberación en C++.

La idea central del RAII es que la adquisición de un recurso (como memoria dinámica, archivos, bloqueos, etc.) se asocia con la inicialización de un objeto y su liberación se asocia con su destrucción. Esto significa que los recursos se obtienen cuando se crea un objeto y se liberan automáticamente cuando el objeto se destruye, incluso si se producen excepciones.

Las ventajas del RAII son varias:

1. **Gestión segura de recursos**: Garantiza que los recursos se liberen adecuadamente, lo que ayuda a prevenir fugas de memoria y otros problemas de manejo de recursos.

2. **Código más limpio y legible**: Al encapsular la adquisición y liberación de recursos en objetos, el código se vuelve más claro y fácil de entender, ya que se enfoca en la lógica de negocio en lugar de en la gestión de recursos.

3. **Prevención de errores**: Al delegar la liberación de recursos a la destrucción del objeto, se evitan olvidos accidentales de liberación y se minimizan los errores de programación.

4. **Facilita la gestión de excepciones**: El RAII se integra bien con el manejo de excepciones, ya que los recursos se liberarán correctamente incluso si se produce una excepción en el código.

5. **Promueve la modularidad**: Los objetos RAII pueden diseñarse para encapsular un recurso particular, lo que promueve la modularidad y reutilización del código.

Ejemplo de RAII:

```cpp
#include <iostream>
#include <vector>

class ManagedResource {
public:
    ManagedResource() {
        resource = new int[10];
        std::cout << "Recurso adquirido" << std::endl;
    }

    ~ManagedResource() {
        delete[] resource;
        std::cout << "Recurso liberado" << std::endl;
    }

private:
    int* resource;
};

int main() {
    std::vector<ManagedResource> resources;
    resources.push_back(ManagedResource()); // Adquisición de recurso

    // ...

    // Cuando el vector se destruye, se liberan automáticamente los recursos

    return 0;
}
```

En este ejemplo, la clase `ManagedResource` encapsula la adquisición y liberación de un recurso (un arreglo dinámico en este caso). Cuando se crea un objeto `ManagedResource`, se adquiere el recurso, y cuando se destruye (al salir de su ámbito), se libera el recurso automáticamente. Esto demuestra cómo el RAII garantiza la gestión segura y automática de recursos en C++.