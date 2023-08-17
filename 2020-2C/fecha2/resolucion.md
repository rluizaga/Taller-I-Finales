**1)Escriba un programa (desde la inicialización hasta la liberación de los recursos) que escuche el puerto 120 y reciba paquetes de la forma: `[CHAR_LIM]xxxxx.xxxxxx [CHAR_LIM]` donde `[CHAR_LIM]` puede ser cualquier caracter ASCII. Al completar la recepción del paquete deberá imprimir el caracter con más apariciones del mismo (sin considerar `[CHAR_LIM]`). Al recibir un paquete vacío (`[CHAR_LIM][CHAR_LIM]`) debe cerrarse ordenadamente. No considere errores.**

**2) ¿Qué función se utiliza para lanzar hilos?¿Qué parámetros tiene y para qué sirven? Ejemplifique.**
La funcion para lanzar un hilo en c++ es std::thread toma como primer argumento la funcion que se ejecutara en el thread y opcionalmente puede tener argumentos adicionales que se pasaran a la funcion.
ejemplo:
```c++
void imprimir(const std::String &mensaje) {
    std::cout << mensaje << std::endl;
}

int main() {
    std:thread mi_thread(imprimir, "hola")

    mi_thread.join();
    return 0;
}
```

**3) ¿Qué finalidad tiene la palabra virtual antepuesta a un método? Ejemplifique.**
La palabra virtual se utiliza para definir un metodo virtual lo que indica que el metodo puede ser reemplazado en la clases derivadas. Cuando se llama al metodo virtual a traves de un puntero o una referencia de la clase base, se invocara a la implementacion del metodo en la clase derivada.
Un metodo virtual permite que la implementacion se determine en tiempo de ejecucion.

```c++
#include <iostream>

class Forma {
public:
    virtual void dibujar() {
        std::cout << "Se dibuja una forma" << std::endl;
    }
};

class Cuadrado : public Forma {
public:
    void dibujar() override {
        std::cout <<"Se dibuja un cuadrado" << std::endl;
    }
};

int main() {
    Cuadrado cuadrado;
    Forma *forma = &cuadrado;
    forma -> dibujar();
}
```


**4) Implemente una función C++ denominada DUPLICAR que reciba dos listas de elementos y devuelva una nueva lista duplicando los elementos de la primera que están en la segunda:**
`std::list<T> Duplicar(std::list<T> a,std::list<T> b);`
Resuelto

**5) Declare una clase a elección considerando:**
- **Atributos que son necesarios**
- **Accesibilidad a la Clase**
- **Incluir los operadores --(pre-decremento), ++(post-incremento), << (impresión), >>(carga desde consola), functor**
```c++
class Counter {
private:
    int value;
public:
    Counter& operator--();
    Counter operator++(int);
    friend std::ostream& operator<<(std::ostream& os, const Counter& counter);
    friend std::istream& operator>>(std::istream& is, Counter& counter);
    void operator()() const; 
}
```

**6) Explique qué es (a), (b), (c) y (d), haciendo referencia a su valor y momento de inicialización, su comportamiento y el area de memoria donde residen:**

```c
extern int *a[25];
int b()
{
static float c; char d=70;
return c+(float) d;
}
```
`extern int *a[25]`: La palabra clave extern indica que la declaración del arreglo a se realiza aquí, pero su definición (es decir, la asignación de memoria real) se encuentra en otro archivo. La ubicación exacta de esas áreas de memoria dependerá de cómo y cuándo se asignen e inicialicen los punteros.
`int b(){...}`: Define una funcion que devuelve un entero y no tiene parametros
`static float c`: La variable c es una variable local estática de tipo float. Como es estática, se inicializa automáticamente a 0 antes de que la función sea llamada por primera vez. El valor de la variable c se mantiene entre llamadas a la funcion. La variable c es una variable local estática, lo que significa que su duración y alcance son los mismos que una variable estática global. Reside en el segmento de memoria denominado "Data Segment" y su valor persiste entre llamadas a la función.
`char d=70`: La variable d es una variable local de tipo char que se inicializa con el valor 70. La variable d es una variable local que reside en la pila de llamadas y su vida útil es limitada al alcance de la función.

**7) Escriba una rutina que dibuje un rombo verde que ocupe toda la ventana.**

**8) ¿Qué diferencia existe entre un constructor por copia y uno por movimiento? Ejemplifique.**
Un constructor por copia crea un nuevo objeto copiando los valores de los atributos del objeto existente al nuevo objeto.
Un constructor por movimiento transfiere la propiedad de los recursos del objeto existente al nuevo objeto.
```c++
class MiClase{
private:
    int *dato;
public:
    MiClase(int valor) {
        dato = new int(valor);
    }
    // constructor por copia
    MiClase(MiClase& otro) {
        dato = new int (*otro.dato)
    }
    // contructor por movimiento
    MiClase(MiClase&& otro) {
        dato = otro.dato;
        otro.dato = nullptr;
    }
}
```


**9) Escriba una función ISO C que permita procesar sobre sí mismo (sin generar archivos intermedios ni cargar el archivo completo a memoria) un archivo texto con palabras separadas por espacios. El procesamiento consiste en duplicar las palabras que tengan al menos de 2 vocales.**
Resuelto

**10) ¿Qué es la compiLación condicional? Ejemplifique**
La compilación condicional es una técnica en la programación que permite incluir o excluir porciones de código en función de ciertas condiciones predefinidas durante el proceso de compilación. Esto se logra mediante el uso de directivas de preprocesador y macros en el código fuente.
Un ejemplo clásico de compilación condicional es utilizar directivas como #ifdef, `#ifndef`, `#else`, `#endif`, `#define`, `#undef`, entre otras, para adaptar el código a diferentes plataformas, configuraciones o características.

```c
#ifndef __COMPLEJOS_H__
#define COMPLEJOS_H
...
#endif
```