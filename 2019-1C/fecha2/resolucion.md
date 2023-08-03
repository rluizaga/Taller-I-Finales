**1) Declare la clase Número para encapsular una cadena numérica larga. Incluya al menos: Constructor(unsigned long), Constructor default y Constructor move; Operador <<, (), =, long y ++(int). Implemente el operador >>.**

``` c++
class Numero{
        Numero(unsigned long numero);
        Numero(const Numero & otro); //constructor por copia(default)
        Numero(Numero && otro); //constructor por movimiento
        std::istream operator>>(std::istream & input, Numero & numero){
            in>>numero;
            return in;
        }
        std::ostream operator<<(std::ostram &output, const Numero& numero);

        Numero& operator=(const Numero& otro); //asignacion por copia
        Numero& operator=(const Numero&& otro); //asignacion por movimiento
        Numero operator++(int);
        operator long() const;
};
```
</details>

**2) ¿Qué significa que una función es blocante?¿Cómo subsanaría esa limitación en término de mantener el programa ‘vivo’ ?**

Una función es considerada bloqueante cuando su ejecución impide que el hilo de ejecución actual (o el proceso) continúe hasta que la función termine su tarea. En otras palabras, la función bloquea el flujo de ejecución y no permite que otras partes del programa avancen hasta que esa función se complete. Para mantener el programa 'vivo' y evitar bloqueos prolongados que puedan afectar la capacidad de respuesta de la aplicación, se pueden agregarse hilos para ejecutar concurrentemente aquello que deba seguir ejecutandose

**3) Explique qué son los métodos virtuales y para qué sirven. De un breve ejemplo donde su uso sea imprescindible.**  

Los metodos virtuales son los metodos definidos dentro de una clase base y se redefinen en una clase derivada. Su principal propósito es permitir el polimorfismo, lo que significa que una llamada a un método virtual en un objeto se resuelve en tiempo de ejecución según el tipo real del objeto en lugar del tipo estático. Su uso imprescindible es, por ejemplo, en los casos en los que tenemos clases abstractas (o el ejemplo de la clase figura, que las distintas figuras tienen distintos comportamientos).

**4) Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear archivos intermedios y sin subir el archivo a memoria). El procesamiento consiste en leer grupos de 4 caracteres hexadecimales y reemplazarlos por los correspondientes dígitos decimales (que representen el mismo número leído pero en decimal).**

Resuelto

**5) Explique qué se entiende por “compilación condicional”. Ejemplifique mediante código.**

La "compilación condicional" se refiere a una técnica en programación donde ciertas partes del código fuente se incluyen o excluyen durante el proceso de compilación según condiciones predefinidas. Esto permite que diferentes variantes del código se generen a partir del mismo código fuente, lo que resulta útil para crear versiones específicas del programa para diferentes plataformas, configuraciones o características.

En C++ y otros lenguajes de programación, la compilación condicional se logra mediante el uso de directivas del preprocesador, que son instrucciones especiales que se procesan antes de la compilación.

Un ejemplo común de compilación condicional es el uso de la directiva #ifdef y #endif en C++. La sintaxis general es la siguiente:

``` c++
#ifdef CONSTANTE
    // Código que se incluirá si CONSTANTE está definida
#else
    // Código que se incluirá si CONSTANTE no está definida
#endif
```

Un uso común para la compilación condicional es evitar inclusiones múltiples del mismo archivo de encabezado.
Por ejemplo,

``` c++
#ifndef __CLASE__
#define __CLASE__
.
.
.
#endif
```

Si ```__CLASE__``` ya fue definido, entonces salta directamente a la directiva #endif. Si no, la define.

**6) Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la cadena A después de haber duplicado todas las ocurrencias de B..**  
**ej.: reemp.exe “Este es el final” final -----> Este es el final final**

Resuelto

**7) Escriba las siguientes definiciones/declaraciones:**  
  **a) Definición de una la función SUMA, que tome dos enteros largos con signo y devuelva su suma. Esta función sólo debe ser visible en el módulo donde se la define.**  
  **b) Declaración de un puntero a puntero a entero sin signo.**  
  **c) Definición de un caracter solamente visible en el módulo donde se define.**  
  
  a)

```
static long int SUMA(long int numero, long int otroNumero){
    return numero + otroNumero;
}
```

b)

```
extern unsigned int **p;
```

c)

```
static char c;
```

**8) ¿Qué valor arroja sizeof(int)? Justifique.**

La salida de sizeof(int) depende de la arquitectura y el compilador que utilicemos. Puede devolver 4 en el caso de una arquitectura de 32 bits, u 8 en el caso de una arquitectura de 64 bits.

**9) Describa el concepto de loop de eventos (events loop) utilizado en programación orientada a eventos y, en particular, en entornos de interfaz gráfica (GUIs).**

En la programación orientada a eventos, el programa se mantiene en un ciclo constante de espera y despacho de eventos. Este ciclo principal, conocido como loop de eventos, realiza dos tareas fundamentales:

1. Decodificar el siguiente evento: En esta etapa, se determina qué evento ha ocurrido y a qué manejador debe ser enviado para su procesamiento.

2. Despachar el evento: Una vez que se ha identificado el manejador adecuado para el evento, este se ejecuta de manera secuencial para responder a la aparición del evento.

Los manejadores son secciones de código que conocen cómo responder a eventos específicos. Dado que el event loop los dispara, se ejecutan de manera secuencial, lo que evita problemas de concurrencia entre ellos. Sin embargo, es importante tener en cuenta que si un manejador tarda mucho en completarse, puede retrasar la ejecución de los manejadores que vienen después. Por esta razón, especialmente en aplicaciones con interfaz gráfica (GUI), se recomienda programar manejadores cortos que brinden un rápido feedback al usuario.

En muchos frameworks gráficos, el event loop se ejecuta en el hilo principal del programa, lo que implica que el procesamiento de eventos debe ser ágil para mantener la responsividad de la interfaz de usuario.

**10) ¿Qué ventaja ofrece un lock raii frente al tradicional lock/unlock ?**

La ventaja principal de un lock RAII (Resource Acquisition Is Initialization) frente al tradicional lock/unlock es que garantiza automáticamente el desbloqueo seguro de recursos críticos cuando el objeto que adquirió el bloqueo sale de su alcance. Esto evita posibles bloqueos perpetuos y mejora la seguridad y mantenibilidad del código, ya que no es necesario realizar llamadas explícitas a unlock en cada punto de retorno o manejo de excepciones.