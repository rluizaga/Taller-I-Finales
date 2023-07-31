**1) Explique qué es y para qué sirve un constructor de copia en C++.**  
  **a) Indique cómo se comporta el sistema si éste no es definido por el desarrollador;**  
  **b) Explique al menos una estrategia para evitar que una clase particular sea copiable;**  
  **c) Indique qué diferencia existe entre un constructor de copia y uno move.**

El constructor de copia en C++ es una función especial que se utiliza para crear una copia exacta de un objeto existente de la misma clase. Cuando se utiliza este constructor, se copian todos los miembros del objeto original en el nuevo objeto. Es útil para trabajar con clases que contienen recursos dinámicos o cuando se necesita hacer una copia profunda del objeto en lugar de copiar solo los punteros. Esto asegura que la copia sea independiente del objeto original.

a) Si el desarrollador no define un constructor de copia en una clase, el compilador proporcionará automáticamente uno por defecto. Este constructor de copia por defecto realizará una copia superficial del objeto. Una copia superficial significa que solo se copiarán los valores de los miembros simples, pero no se copiarán los recursos a los que apunten los punteros. Esto puede conducir a problemas de gestión de memoria y comportamientos inesperados si los objetos tienen recursos dinámicos que no se manejan adecuadamente.


b) Para que una clase no sea copiable se puede eliminar el constructor por copia y el operador asignacion por copia. Supongamos que tenemos una clase Complejo. Eliminamos el constructor por copia asi, junto con su operador asignacion por copia:  
    ```
    Complejo(Complejo& c) = delete;
    Complejo &operator=(const Complejo &c) = delete;
    ```  

c) La diferencia entre estos dos constructores es que el primero devuelve una copia de una instancia recibida. Osea, copia los atributos de la clase recibida por parametros. En cambio, el constructor por movimiento lo que hace es mover o *transferir* los recursos almacenados por la instancia recibida por parametro, y esta instancia recibida deja de ser duenio de dichos recursos. Cuando se destruye el objeto que movimos el nuevo objeto seguira teniendo las mismas referencias/ punteros.

**2) Escriba una función ISO C llamada Replicar que reciba 1 cadena (S), dos índices (I1 e I2) y una cantidad (Q). La función debe retornar una copia de S salvo los caracteres que se encuentran entre los índices I1 e I2 que serán duplicados Q veces.Ej. replicar(“Hola”, 1, 2, 3) retorna “Hololola”.**  

Resuelto

**3) Describa con exactitud las siguientes declaraciones/definiciones globales:**
<strong>1. void (*F)(int i);</strong>
**2. static void B(float a, float b){}**    
<strong>3. int *(*C)[5];</strong>

1. `void (*F)(int i);`
Esta declaración global define un puntero a una función llamada F, que toma un argumento de tipo int y no devuelve ningún valor (void). El puntero a la función se denota por (*F), y se puede usar para almacenar la dirección de una función que tenga el mismo tipo de firma (un argumento int y un valor de retorno void).

2. `static void B(float a, float b){}`
Esta es la definición de una función llamada B, que toma dos argumentos de tipo float, a y b, y no devuelve ningún valor (void). La palabra clave static antes de la declaración de la función limita su alcance a este archivo en particular, lo que significa que la función solo es visible y utilizable dentro de este archivo. Su scope es local archivo donde se define y reside en memoria en el code segment.

3. `int *(*C)[5];`
Esta declaración define un puntero llamado C, que apunta a un array de 5 punteros a enteros (int *). El puntero C puede utilizarse para acceder y manipular un array de punteros a enteros de tamaño 5. Cada elemento del array apuntará a un valor entero (un entero almacenado en memoria). La declaración no inicializa el puntero, por lo que su valor inicial será indeterminado hasta que se le asigne una dirección válida mediante una asignación. Su scope sera global y reside en memoria en el data segment.

**4) Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y lo procese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a memoria). El procesamiento consiste en eliminar las líneas de 1 sola palabra.**

Resuelto.

**5) Declare una clase de elección libre. Incluya todos los campos de datos requeridos con su correcta exposición/publicación, y los operadores ++, -, ==, >> (carga), << (impresión), constructor move y operador float().**  

```c++
#include <iostream>

class Numero {
private:
    int value;

public:
    // Constructor por defecto
    Numero() : value(0) {}

    // Constructor de inicialización
    Numero(int val) : value(val) {}

    // Constructor move
    Numero(Numero&& other) {
        value = other.value;
        other.value = 0;
    }

    // Operador de incremento (++), prefijo
    Numero& operator++() {
        ++value;
        return *this;
    }

    // Operador de decremento (--), prefijo
    Numero& operator--() {
        --value;
        return *this;
    }

    // Operador de resta (-)
    Numero operator-(const Numero& other) const {
        return Numero(value - other.value);
    }

    // Operador de igualdad (==)
    bool operator==(const Numero& other) const {
        return value == other.value;
    }

    // Operador de carga (>>)
    friend std::istream& operator>>(std::istream& is, Numero& obj) {
        is >> obj.value;
        return is;
    }

    // Operador de impresión (<<)
    friend std::ostream& operator<<(std::ostream& os, const Numero& obj) {
        os << obj.value;
        return os;
    }

    // Operador float() para conversión a tipo float
    operator float() const {
        return static_cast<float>(value);
    }
};
```

**6) ¿Qué es una macro de C? Describa las buenas prácticas para su definición y ejemplifique.** 

En C, una macro es una construcción del preprocesador que permite definir una abreviatura para un fragmento de código. Se trata de una especie de sustitución de texto que ocurre antes de que el código sea procesado por el compilador. Las macros se definen mediante la directiva #define y se utilizan para simplificar el código, mejorar la legibilidad o permitir una mayor reutilización.

Las buenas prácticas para definir macros en C incluyen:

Usar mayúsculas para el nombre de la macro: Por convención, los nombres de las macros se escriben completamente en mayúsculas para distinguirlas de otras identificadores del código.

Utilizar paréntesis alrededor de los argumentos: Si la macro tiene argumentos, asegúrate de colocar paréntesis alrededor de los argumentos y también alrededor de todo el cuerpo de la macro. Esto ayuda a evitar problemas inesperados en la expansión de la macro cuando se utilizan expresiones más complejas.

Evitar efectos secundarios: No se deben incluir efectos secundarios dentro de las macros, ya que podrían conducir a comportamientos inesperados. Por ejemplo, no es recomendable incrementar una variable dentro de una macro, ya que podría conducir a resultados no deseados.

Usar paréntesis en las definiciones de la macro: Cuando definas una macro, asegúrate de colocar paréntesis alrededor de toda la definición para garantizar la precedencia adecuada de los operadores en la expansión de la macro.

Ejemplo:

Supongamos que deseamos definir una macro simple para calcular el cuadrado de un número. Aplicando las buenas prácticas mencionadas, la macro se vería así:

```c++
#include <stdio.h>

#define SQUARE(x) ((x) * (x))

int main() {
    int num = 5;
    int result = SQUARE(num);

    printf("El cuadrado de %d es %d\n", num, result);

    return 0;
}
```

**7) Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe aceptar una única conexión e imprimir en stdout la sumatoria de los enteros recibidos en cada paquete. Un paquete está definido como una sucesión de números recibidos como texto, en decimal, separados por comas y terminado con un signo igual (ej: “27,12,32=”). Al recibir el texto ‘FIN’ debe finalizar el programa ordenadamente liberando los recursos.**

Resuelto

**8) Describa el proceso de transformación de código fuente a un ejecutable. Precise las etapas, las tareas desarrolladas y los tipos de error generados en cada una de ellas.**

La compilación consta de 3 etapas: preprocesamiento, compilación y enlazado (en ese orden). Se parte del código fuente y al finalizar se obtiene el ejecutable.

Preprocesamiento: se procesan las macros y las directivas al compilador. Se expanden las macros que se hayan definido y se incluyen los archivos .h que se hayan incluido utilizando la directiva #include. Puede ocurrir que el módulo incluido no se encuentre y ahí tendríamos un error.

Compilación: se parsea el código C y se pasa de un archivo de texto a un código objeto. Contiene la información sobre las funciones, segmento de texto, datos, etc. Pueden ocurrir errores de sintaxis y advertencias.

Enlazado: etapa en la que se vinculan los distintos módulos para generar el archivo ejecutable. Junta las dependencias. Pueden ocurrir errores de enlace porque no incluimos alguna biblioteca o archivo objeto, o puede que hayamos olvidado definir alguna función o variable, o lo hayamos hecho mal.

**9) ¿Qué ventaja ofrece un lock raii frente al tradicional lock/unlock ?**  

Un lock RAII (Resource Acquisition Is Initialization) es una clase que maneja automáticamente un lock de un mutex al crearse (recibiendo el mutex como parámetro en su constructor) y realiza automáticamente el unlock del mutex al destruirse. La característica clave del RAII es que el destructor de la clase se invoca automáticamente al finalizar el ámbito de la función, garantizando la liberación del lock sin importar si se produjo una excepción o si el desarrollador olvidó explícitamente realizar el unlock.

Esta técnica evita el riesgo de dejar un hilo bloqueado (deadlock), ya que el unlock se realizará automáticamente incluso si se lanza una excepción en el código protegido por el lock. Además, la implementación del lock RAII promueve una programación más segura y limpia, ya que el programador no necesita preocuparse explícitamente por liberar el lock al salir de un bloque protegido por el mutex. Al utilizar el lock RAII, el código es más resistente a errores y más fácil de mantener, ya que la liberación del recurso se asegura mediante el mecanismo de la destrucción automática del objeto RAII al finalizar el ámbito.

  **10) ¿Qué significa que una función es blocante?¿Cómo subsanaría esa limitación en términos de mantener el programa ‘vivo’ ?**  

  Que una funcion sea bloqueante significa que se queda esperando hasta que se cumpla una tarea o hasta obtener un resultado. Para mantener el programa vivo, pueden agregarse hilos para ejecutar concurrentemente aquello que deba seguir ejecutandose, mientras que otro hilo es el que se queda esperando.