**1) Explique breve y concretamente qué es f:**
`int *(**f) (short int *, char *[2]);`
f es un puntero a puntero a funcion que devuelve un puntero a entero y recibe como parametros un puntero a short int y un array de 2 de punteros a char.

**2) Explique qué es cada uno de los siguientes, haciendo referencia a su inicialización, su comportamiento y el area de memoria donde residen: 
a) Una variable global static 
b) Una variable local static 
c) Un atributo de clase static.**

a) Una variable global static:
- Inicialización: Si no se inicializa explícitamente, se inicializa automáticamente a cero (o a su valor inicial si se proporciona uno).
- Comportamiento: Mantiene su valor entre diferentes llamadas a las funciones y su ámbito es global dentro del archivo donde se define. Cualquier modificación realizada en una función afectará al valor de la variable en otras funciones.
- Área de memoria: Reside en el Data Segment y su alcance es global dentro del archivo donde se define.

b) Una variable local static:
- Inicialización: Si no se inicializa explícitamente, se inicializa automáticamente a cero (o a su valor inicial si se proporciona uno).
- Comportamiento: Mantiene su valor entre diferentes llamadas a la función.
- Área de memoria: Reside en el Stack Frame de la función y mantiene su valor entre llamadas a la función.

c) Un atributo de clase static:
- Inicialización: Se inicializa automáticamente a cero (o a su valor inicial si se proporciona uno).
- Comportamiento: Es compartido por todas las instancias de la clase. Su valor es único para la clase y no se relaciona con ninguna instancia en particular.
- Área de memoria: Reside en el Data Segment y su alcance es global dentro del archivo donde se define.


**3) Escribir un programa ISO C que procese el archivo “nros2bytes.dat” sobre sí mismo, duplicando los enteros de 2 bytes múltiplos de 3.**
Resuelto

**4) ¿Cómo se logra que 2 threads accedan (lectura/escritura) a un mismo recurso compartido sin que se generen problemas de consistencia? Ejemplifique.**
Para que 2 threads accedan a un mismo recurso compartido sin que se generen problemas se puede hacer uso de un recurso llamado mutex el cual puede ser tomado por un hilo mediante un lock el cual garantiza que el recurso no pueda ser accedido hasta que se libere el mutex mediante la funcion unlock.
Por ejemplo:
```c++
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; 

int sharedResource = 0;

void threadFunction() {
    for (int i = 0; i < 10000; ++i) {
        mtx.lock(); 
        sharedResource++; 
        mtx.unlock(); 
    }
}

int main() {
    std::thread thread1(threadFunction);
    std::thread thread2(threadFunction);

    thread1.join();
    thread2.join();

    std::cout << "Valor final del recurso compartido: " << sharedResource << std::endl;

    return 0;
}

``` 

**5) Escriba el .H de una biblioteca de funciones ISO C para cadenas de caracteres. Incluya, al menos, 4 funciones.**
```c++
#ifndef MI_STRING_H
#define MI_STRING_H

mi_strcmp(const char *str1, const char *str2)
mi_strlen(const char *str)
mi_strcpy(char *dest, const char *orig)
mi_strcat(char *dest, const char *orig)

#endif
```

**6) ¿Qué es una macro de C? Detalle las buenas prácticas para su definición. Ejemplifique**
Una macro es una secuencia de codigo que se define mediante la directiva de preprocesador #define y se reemplaza en el codigo en la etapa de preprocesamiento
Buenas prácticas para definir macros incluyen:
- Nombres Descriptivos: Asigna un nombre claro y descriptivo a la macro para que su propósito sea evidente para los desarrolladores que lean el código.
- Uso de Paréntesis: Usa paréntesis para rodear expresiones en la macro, especialmente si involucran operadores, para evitar problemas de precedencia.
- Uso de Mayúsculas: Usa nombres en mayúsculas para macros para distinguirlas fácilmente de otras construcciones en el código.

**7) Describa el proceso de transformación de código fuente a un ejecutable. Precise las etapas y las tareas desarrolladas en cada una de ellas.**
El proceso de transformacion de codigo fuente a un ejecutable consta de varias etapas:
- Preprocesamiento: Las tareas desarrolladas en esta etapa son la expancion de las macros inclusion de archivos de cabezera (#include), eliminacion de comentarios, definicion de variables simbolicas (#define)
- Compilacion: Se parcea el codigo en C a codigo objeto. Contiene informacion de sobre las funciones, segmento de codigo,  segmento de texto, datos. Pueden ocurrir errores de sintaxis y advertencias
- Linkeo: En esta etapa se vinculan los distintos modulos para generar el ejecutable. También se resuelven las referencias a funciones y variables definidas en otros archivos o bibliotecas externas. Se crea un archivo ejecutable que contiene todas las instrucciones de máquina necesarias para ejecutar el programa.

**8) Indique la salida del siguiente programa:**
```c++
class A {
    A(){cout << “A()” << endl;}
    ~A(){ cout << “~A()” << endl;}
}
class B : public A {
    B(){cout << “B()” << endl;}
    ~B(){ cout << “~B()” << endl;}
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

**9) Implemente una función C++ denominada Sacar que reciba dos listas de elementos y devuelva una nueva lista con los elementos de la primera que no están en la segunda:**
Resuelto

**10) Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe establecer una unica conexión, quedar en escucha e imprimir en stdout todo lo recibido. Al recibir el texto ‘FINAL’ debe finalizar el programa sin imprimir dicho texto.**
Resuelto