**1) ¿Qué es una macro de C? Enumere buenas prácticas para su definición.**

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

**2) Describa el proceso de transformación de código fuente a un ejecutable. Precise las etapas y las tareas desarrolladas en cada una de ellas.**

La compilación consta de 3 etapas: preprocesamiento, compilación y enlazado (en ese orden). Se parte del código fuente y al finalizar se obtiene el ejecutable.

Preprocesamiento: se procesan las macros y las directivas al compilador. Se expanden las macros que se hayan definido y se incluyen los archivos .h que se hayan incluido utilizando la directiva #include. Puede ocurrir que el módulo incluido no se encuentre y ahí tendríamos un error.

Compilación: se parsea el código C y se pasa de un archivo de texto a un código objeto. Contiene la información sobre las funciones, segmento de texto, datos, etc. Pueden ocurrir errores de sintaxis y advertencias.

Enlazado: etapa en la que se vinculan los distintos módulos para generar el archivo ejecutable. Junta las dependencias. Pueden ocurrir errores de enlace porque no incluimos alguna biblioteca o archivo objeto, o puede que hayamos olvidado definir alguna función o variable, o lo hayamos hecho mal.

**3) Explique breve y concretamente qué es f:**
```
char (*f) (int *, char[3]);
```

f es un puntero a una funcion que devuelve un tipo de dato char. Recibe por parametro un puntero a un tipo de dato int y un arreglo de tipo char de tres elementos.

**4) Escribir un programa ISO C que procese el archivo “nros_2bytes_bigendian.dat” sobre sí mismo, eliminando los número múltiplos de 7.**

Resuelto

**5) Implemente una función C++ denominada DobleSegunda que reciba dos listas de elementos y devuelva una nueva lista duplicando los elementos de la primera si están en la segunda:**

```
std::list<T> DobleSegunda(std::list<T> a,std::list<T> b);
```

Resuelto

**6) Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe aceptar una unica conexión e imprimir en stdout todo lo recibido. Al recibir el texto ‘FIN’ debe finalizar el programa sin imprimir dicho texto.**

Resuelto

**7) Escriba el .H de una biblioteca de funciones ISO C para números complejos. Incluya, al menos, 4 funciones.**

```c
#ifndef COMPLEX_MATH_H
#define COMPLEX_MATH_H

typedef struct {
    double real;
    double imag;
} Complex;

// Función para sumar dos números complejos
Complex complex_add(Complex a, Complex b);

// Función para restar dos números complejos
Complex complex_subtract(Complex a, Complex b);

// Función para multiplicar dos números complejos
Complex complex_multiply(Complex a, Complex b);

// Función para dividir dos números complejos
Complex complex_divide(Complex a, Complex b);

#endif // COMPLEX_MATH_H
```

**8) Explique qué es cada uno de los siguientes, haciendo referencia a su inicialización, su comportamiento y el area de memoria donde residen:**
**a) Una variable global static**
**b) Una variable local static**
**c) Un atributo de clase static.**

a) Una variable global static:
- Inicialización: Una variable global static se inicializa solo una vez, en el momento en que se asigna memoria estática al programa, antes de que comience la ejecución.
- Comportamiento: La variable global static tiene un ámbito local al archivo donde se define, lo que significa que solo es accesible dentro de ese archivo. La variable mantiene su valor entre llamadas a funciones y conserva su estado incluso después de que la función que la inicializó haya terminado.
- Área de memoria: Reside en el Data Segment (también conocido como Static Data Segment) del programa, que es una región de memoria destinada a almacenar variables globales y estáticas.

b) Una variable local static:
- Inicialización: Una variable local static también se inicializa solo una vez, en el momento en que se asigna memoria estática al programa, pero a diferencia de las variables globales static, la inicialización ocurre la primera vez que se entra en el ámbito de la función donde está definida.
- Comportamiento: La variable local static tiene un ámbito local a la función donde está definida, lo que significa que solo es accesible dentro de esa función. Sin embargo, a diferencia de las variables locales regulares, la variable static mantiene su valor entre llamadas a la función y conserva su estado incluso después de que la función haya terminado.
- Área de memoria: Al igual que las variables globales static, las variables locales static también residen en el Data Segment.

c) Un atributo de clase static:
- Inicialización: Un atributo de clase static se inicializa cuando se carga la clase en la memoria, antes de que se cree cualquier objeto de la clase.
- Comportamiento: Los atributos de clase static son compartidos por todas las instancias (objetos) de la clase. Esto significa que todas las instancias de la clase comparten el mismo valor de la variable static. Si se modifica el valor de la variable static en una instancia, el cambio se reflejará en todas las demás instancias.
- Área de memoria: Los atributos de clase static se almacenan en el Data Segment junto con las variables globales y static. La única diferencia es que están asociados con la clase y no con un archivo específico.

**9) ¿Cómo se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido sin que se generen problemas de consistencia? Ejemplifique.**

Para permitir que dos hilos accedan (lectura/escritura) a un mismo recurso compartido sin generar problemas de consistencia, utilizamos un mecanismo de sincronización llamado mutex. Cuando un hilo necesita acceder al recurso compartido, adquiere el mutex mediante una operación de 'lock'. Si otro hilo intenta adquirir el mutex mientras está bloqueado por otro hilo, se quedará esperando hasta que el mutex esté disponible nuevamente.

Una vez que un hilo ha adquirido el mutex, puede acceder al recurso compartido de manera exclusiva y realizar sus operaciones. Una vez que ha terminado de trabajar con el recurso, libera el mutex mediante una operación de 'unlock', permitiendo que otros hilos adquieran el mutex y accedan al recurso compartido.

El uso del mutex garantiza que solo un hilo pueda acceder al recurso compartido a la vez, evitando situaciones de carrera y asegurando que los datos se mantengan consistentes y válidos.

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Crear el objeto mutex

int contador_compartido = 0;

void incrementarContador(int id) {
    for (int i = 0; i < 5; ++i) {
        mtx.lock(); // Adquirir el mutex antes de acceder al contador compartido
        contador_compartido++; // Operación de escritura en el contador compartido
        std::cout << "Thread " << id << " incrementó el contador a: " << contador_compartido << std::endl;
        mtx.unlock(); // Liberar el mutex después de usar el contador compartido

        // Simular un tiempo de espera aleatorio para ilustrar la concurrencia
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
    }
}

int main() {
    std::thread t1(incrementarContador, 1);
    std::thread t2(incrementarContador, 2);

    t1.join();
    t2.join();

    return 0;
}
```

**10) Indique la salida del siguiente programa:**

```cpp
class A{
  A(){
    cout << “A()” << endl;
  }       
  ~A(){
    cout << “~A()” << endl;
  }
}  
class B : public A {
   B(){
     cout << “B()” << endl;
   }     
  ~B(){
    cout << “~B()” << endl;
  }
}      
int main () {
  B b;
  return 0;
}
```
La salida del programa sera:
```
A()
B()
~B()
~A()
```