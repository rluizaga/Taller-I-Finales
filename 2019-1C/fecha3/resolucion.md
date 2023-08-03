**1) Declare una clase a elección considerando:**  
* **Atributos que son necesarios**
* **Accesibilidad a la Clase**
* **Incluir los operadores +, ++ (post-incremento), --(pre-incremento), >> (impresión), << (carga desde consola), long**

```c++
class Fraccion {
private:
    int numerador;
    int denominador;

public:
    Fraccion();
    Fraccion(int numerador, int denominador);
    Fraccion operator+(const Fraccion& otra) const;
    Fraccion operator++(int);
    Fraccion& operator++();
    Fraccion operator--(int);
    Fraccion& operator--();
    friend std::istream& operator>>(std::istream& in, Fraccion& fraccion);
    friend std::ostream& operator<<(std::ostream& out, const Fraccion& fraccion);
};
```
**2) ¿Qué es un functor? ¿Qué ventaja ofrece frente a una función convencional? Ejemplifique.**

Un functor es un objeto que actúa como una función. Es una instancia de una clase que sobrecarga el operador de llamada operator(), lo que le permite ser invocado como si fuera una función. En esencia, un functor es un objeto funcional que se puede utilizar de manera similar a una función.

La principal ventaja que ofrece un functor frente a una función convencional es que un functor puede tener estado. Esto significa que puede mantener datos y utilizarlos entre llamadas a través de sus atributos. En cambio, una función convencional no tiene estado y solo puede operar con los parámetros que se le pasan en cada llamada.

Ejemplo de un functor:

```c++
#include <iostream>

class Sumador {
public:
    Sumador(int valorInicial) : total(valorInicial) {}

    int operator()(int numero) {
        total += numero;
        return total;
    }

private:
    int total;
};

int main() {
    Sumador sumador(5);

    std::cout << sumador(10) << std::endl; // Salida: 15 (5 + 10)
    std::cout << sumador(20) << std::endl; // Salida: 35 (15 + 20)
    std::cout << sumador(5) << std::endl;  // Salida: 40 (35 + 5)

    return 0;
}
```

**3) Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden ascendente. Se pide que los números sean contabilizados por una variable global única y que los pares sean escritos por un hilo mientras que los impares sean escritos por otro.**  
**Contemple la correcta sincronización entre hilos y la liberación de los recursos utilizados.**

Resuelto

**4) Explique qué es (a), (b), (c) y (d), haciendo referencia a su valor y momento de inicialización, su comportamiento y el area de memoria donde residen:**

```c
static int a;
int b(){
static int c; char d=65;
return c+(int) d;
}
```

`static int a;`: Esta es una definición de una variable global de tipo int. Al ser static, se almacenará en el data segment y tendrá un ámbito local al archivo (no al programa completo). Esto significa que solo podrá ser accedida dentro del módulo (archivo) donde se declaró. La variable a será inicializada automáticamente a cero debido a su naturaleza estática, lo que ocurre antes de que comience la ejecución del programa.

`int b()`: Es una declaración y definición de una función llamada b. Esta función tiene un tipo de retorno int, lo que significa que devuelve un valor de tipo entero (int). Además la función no recibe parámetros. Esta función se almacena en el segmento de código (también conocido como código de texto o código ejecutable), que es una región de memoria donde se encuentran las instrucciones del programa.

`static int c;`: Esta es una variable estática local llamada c, que se inicializa automáticamente a cero debido a su naturaleza estática se almacenará en el data segment y su valor se mantiene entre diferentes llamadas a la función b(). Cada vez que la función b() se llama, c conserva su valor anterior.

`char d = 65`: La variable d es una variable local dentro de la función b(). La inicialización de la variable d ocurre cada vez que se llama a la función b(), ya que es una variable local. Esto significa que cada vez que la función b() se ejecuta, se crea una nueva instancia de la variable d y se le asigna el valor 65.

El área de memoria donde reside la variable d es el "stack segment". La pila es una estructura de datos que se utiliza para administrar la memoria de manera eficiente durante la ejecución del programa. Cuando se llama a una función, se reservan espacios en la pila para sus variables locales. Cuando la función termina su ejecución, esos espacios se liberan.

**5) Escriba una rutina que dibuje las dos diagonales de la pantalla en color rojo..**

Resuelto

**6) ¿Por qué las librerías que usan Templates se publican con todo el código fuente y no como un .h y .o/.obj?.**

Las librerías que utilizan templates en C++ se publican con todo el código fuente en lugar de proporcionar solo archivos de encabezado (.h) y archivos objeto (.o/.obj) debido a que los templates permiten realizar programación genérica, lo que significa que un mismo código puede ser utilizado con diferentes tipos de datos. Los templates generan código específico para cada tipo en tiempo de compilación, lo que requiere que el código fuente esté disponible durante el proceso de compilación en el cliente. Al proporcionar todo el código fuente, el cliente tiene acceso a las definiciones de los templates y el compilador puede generar el código objeto correspondiente para los tipos específicos que se utilicen en el programa del cliente. Esto permite una mayor flexibilidad y optimización en el uso de templates, lo que es fundamental para la funcionalidad de las librerías que los utilizan.

**7) ¿Qué características debe tener un compilador C para se considerado “portable”?** 

Un compilador C portable es aquel que soporta la sintaxis (y semantica) del lenguaje C dado un estandar y que no agrega ninguna sintaxis adicional por fuera del estandar (de tal manera que el mismo codigo podria ser compilado por otro compilador). Esto incluye tambien el proceso de compilacion estandar (precompilacion, compilacion, linkeo). Ademas el compilador debe ofrecer una implementacion a la libreria estandar de C respetando el estandar de C mencionado anteriormente tal que un programa compilado en un entorno pueda ser ejecutado en otro que tenga una libreria C compatible.

**8) Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba paquetes de la forma [nnn+nn+....+nnnn] (numeros separados por +, encerrados entre corchetes) e imprima el resultado de la suma de cada paquete por pantalla. Al recibir un paquete vacío (“[]”) debe cerrarse ordenadamente. No considere errores.**

Resuelto

**9) Escriba una función ISO C que permita procesar un archivo texto que contenga frases (1 por línea) sobre sí mismo, sin generar archivos intermedios ni cargar el archivo completo a memoria. El procesamiento consiste en eliminar las palabras de más de 3 letras de cada línea.**  

Resuelto

**10) ¿Qué diferencia existe entre un constructor por copia y uno por movimiento? Ejemplifique.**

La diferencia entre un constructor por copia y uno por movimiento es cómo se realiza la transferencia de recursos. El constructor por copia copia los datos de un objeto existente a un nuevo objeto, mientras que el constructor por movimiento mueve los recursos de un objeto existente al nuevo objeto sin copiarlos, dejando el objeto original en un estado válido pero no especificado. El constructor por movimiento es más eficiente para transferir recursos grandes y costosos, evitando copias innecesarias y mejorando el rendimiento.

```c++
#include <iostream>

class MyClass {
public:
    int* data;

    // Constructor por defecto
    MyClass() : data(nullptr) {}

    // Constructor por copia
    MyClass(const MyClass& other) {
        if (other.data) {
            data = new int(*other.data); // Copia profunda de los datos
        } else {
            data = nullptr;
        }
    }

    // Constructor por movimiento
    MyClass(MyClass&& other) {
        data = other.data; // Movimiento de los datos (no se realiza copia)
        other.data = nullptr; // El objeto original se deja en un estado válido pero no especificado
    }

    // Destructor
    ~MyClass() {
        delete data; // Liberar memoria asignada dinámicamente
    }
};

int main() {
    MyClass obj1;
    obj1.data = new int(42);

    // Constructor por copia
    MyClass obj2 = obj1;

    // Constructor por movimiento
    MyClass obj3 = std::move(obj1);

    std::cout << "obj1.data: " << obj1.data << std::endl; // Debe ser nullptr después del movimiento
    std::cout << "obj2.data: " << obj2.data << ", *obj2.data: " << (obj2.data ? *obj2.data : -1) << std::endl;
    std::cout << "obj3.data: " << obj3.data << ", *obj3.data: " << (obj3.data ? *obj3.data : -1) << std::endl;

    return 0;
}

```