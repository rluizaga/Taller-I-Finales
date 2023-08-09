**1) Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba paquetes de la forma nnn+nn+....+nnnn= (numeros separados por +, seguidos de =) e imprima el resultado de la suma de cada paquete por pantalla. Al recibir un paquete vacío (“=”) debe cerrarse ordenadamente. No considere errores.**
Resuelto

**2) Explique breve y concretamente qué es f:**
```
int (*f) (short *, char[4]);
```  
f es un puntero a funcion que devuelve un entero y recibe como parametros un puntero a entero corto y un array de char de tamanio 4

**3) Analice el siguiente código y determine lo que se imprime (valor de Pi)**

```c
main(){
  int *Pi=1000;
  Pi++;
  printf(“Pi apunta a la dirección: %l”, (long)Pi);
}
```  
En el código proporcionado, Pi es un puntero a un entero. Inicialmente, se le asigna el valor 1000, lo que significa que apunta a la dirección de memoria 1000. Luego, la instrucción Pi++ incrementa el puntero, avanzándolo a la siguiente posición de memoria. La cantidad de bytes que avanza depende de la arquitectura: en una arquitectura de 32 bits, avanzaría 4 bytes (tamaño de un int), y en una arquitectura de 64 bits, avanzaría 8 bytes (tamaño de un int en esta arquitectura). Finalmente, se imprime en pantalla la dirección de memoria a la que apunta el puntero Pi después de haber sido incrementado.

**4) ¿Qué es un functor? ¿Qué ventaja ofrece frente a una función convencional? Ejemplifique.**
Un functor es un objeto que se comporta como una función al sobrecargar el operador (). Esto permite invocarlo como si fuera una función. La ventaja principal de un functor sobre una función convencional es su capacidad para mantener un estado interno, lo que le permite retener datos entre llamadas y utilizarlos en operaciones posteriores. A diferencia de las funciones convencionales, que solo pueden operar con los parámetros proporcionados en la llamada, los funtores pueden almacenar información a medida que se utilizan, lo que puede ser útil para implementar ciertos patrones o lógicas más complejas.

```c++
#include <iostream>

class Sumador {
private:
    int total;
public:
    Sumador(int valorInicial) : total(valorInicial) {}

    int operator()(int numero) {
        total += numero;
        return total;
    }
};

int main() {
    Sumador sumador(5);

    std::cout << sumador(10) << std::endl; // Salida: 15 (5 + 10)
    std::cout << sumador(20) << std::endl; // Salida: 35 (15 + 20)
    std::cout << sumador(5) << std::endl;  // Salida: 40 (35 + 5)

    return 0;
}
```

**5) ¿Cómo se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido sin que se generen problemas de consistencia? Ejemplifique.**
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

**6) Describa el concepto de loop de eventos (events loop) utilizado en programación orientada a eventos y, en particular, en entornos de interfaz gráfica (GUIs).**
En un loop de eventos, el programa espera continuamente a que ocurran eventos, como clics de mouse, pulsaciones de teclas u otras interacciones del usuario. Cuando ocurre un evento, este se coloca en una cola de eventos. El loop de eventos luego toma eventos de la cola uno por uno y los envía a los manejadores correspondientes, que son fragmentos de código diseñados para manejar eventos específicos.

**7) Considere la estructura struct ejemplo { int a; char b;}. ¿Es verdad que sizeof (ejemplo)=sizeof(a) +sizeof(b)? Justifique.**
El tamaño total de la estructura podría ser ligeramente mayor si el compilador agrega relleno o realiza alineaciones específicas en la memoria por cuestiones de eficiencia y alineación de datos. En algunas arquitecturas o compiladores, podría haber casos en los que la igualdad no se cumpla debido a consideraciones de alineación,

**8) ¿En qué consiste el patrón de diseño RAII? Ejemplifique.**
El patrón de diseño RAII (Recurso Adquisición es Inicialización, en inglés Resource Acquisition Is Initialization) es una técnica en programación que se utiliza para gestionar recursos de manera segura y automática mediante el uso de objetos. La idea principal detrás de RAII es que la adquisición y liberación de recursos se asocian con el ciclo de vida de un objeto, lo que garantiza que los recursos se gestionen correctamente incluso en situaciones de excepción o de finalización inesperada.

El patrón de diseño RAII es especialmente útil para la gestión de recursos como memoria dinámica, archivos, sockets y otros recursos que deben ser adquiridos y liberados adecuadamente para prevenir fugas de memoria y otros problemas.

Un ejemplo concreto de RAII podría ser el uso de objetos para gestionar recursos de memoria dinámica en C++:

```c++
#include <iostream>

class RecursoMemoria {
private:
    int* data;
    
public:
    RecursoMemoria(int size) : data(new int[size]) {
        std::cout << "RecursoMemoria adquirido" << std::endl;
    }

    ~RecursoMemoria() {
        delete[] data;
        std::cout << "RecursoMemoria liberado" << std::endl;
    }
};

int main() {
    RecursoMemoria recurso(10); // Adquiere el recurso de memoria dinámica

    // Realiza operaciones con el recurso

    // Cuando 'recurso' sale del ámbito, se libera automáticamente el recurso
    return 0;
}
```

**9) Escribir un programa ISO C que procese el archivo de enteros de 2 bytes bigendian cuyo nombre es recibido como parámetro. El procesamiento consiste en eliminar los número múltiplos de 3, trabajando sobre el mismo archivo (sin archivos intermedios ni en memoria).**


**10) Implemente una función C++ denominada DobleSiNo que reciba dos listas de elementos y devuelva una nueva lista duplicando los elementos de la primera que no están en la segunda:**
```
std::list<T> DobleSiNo(std::list<T> a,std::list<T> b);
```  
