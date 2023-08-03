**1) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un triángulo amarillo del tamaño de la ventana.**

Resuelto

**2) Escriba las siguientes definiciones/declaraciones:**
**A) Declaración de un puntero a puntero a entero largo con signo.**
**B) Definición de una la función RESTA, que tome dos enteros largos con signo y devuelva su resta. Esta función debe ser visible en todos los módulos del programa.**
**C) Definición de un caracter solamente visible en el módulo donde se define.**

a) `long int **puntero_a_puntero;`
b) `long int RESTA(long int a, long int b) { return a - b; }`
c) `static char c = 'a'`


**3) Declare la clase Telefono para encapsular una cadena numérica correspondiente a un teléfono. Incluya al menos: Constructor(area, numero), Constructor move y Constructor de Copia; Operador <<, ==, =, long y >>. Implemente el operador >>.**

```c++
class Telefono {
private:
    std::string numero_telefono;

public:
    Telefono(const std::string& area, const std::string& numero);
    Telefono(const Telefono& other); // Constructor de copia
    Telefono(Telefono&& other);      // Constructor move
    ~Telefono();                     // Destructor

    bool operator==(const Telefono& other) const;
    Telefono& operator=(const Telefono& other);

    operator long() const;

    friend std::ostream& operator<<(std::ostream& os, const Telefono& telefono);
    friend std::istream& operator>>(std::istream& is, Telefono& telefono);
};
```

**4) Explique qué se entiende por “compilación condicional”. Ejemplifique mediante código.**

La "compilación condicional" se refiere a la práctica de incluir o excluir partes del código fuente durante el proceso de compilación, según ciertas condiciones predefinidas. Esto permite que diferentes partes del código se compilen o no, dependiendo de las características del entorno de compilación o las opciones de configuración. La compilación condicional es útil para crear versiones personalizadas de un programa, habilitar o deshabilitar características según la plataforma o el objetivo, o realizar ajustes específicos en función de ciertas condiciones.

Un mecanismo común para lograr la compilación condicional en C++ es el uso de directivas preprocesador #ifdef, #ifndef, #else y #endif. Estas directivas permiten incluir o excluir porciones de código basado en la definición de ciertos símbolos.

Aquí tienes un ejemplo sencillo de compilación condicional en C++:

```c++
#include <iostream>

#define DEBUG_MODE  // Define DEBUG_MODE para habilitar la compilación condicional

int main() {
#ifdef DEBUG_MODE
    std::cout << "Depuración activada" << std::endl;
#else
    std::cout << "Depuración desactivada" << std::endl;
#endif

    return 0;
}
```

**5) ¿Qué significa que una función es blocante?¿Cómo subsanaría esa limitación en término de mantener el programa ‘vivo’ ?**

Una función es considerada "bloqueante" cuando su ejecución detiene temporalmente la ejecución del programa hasta que se complete la tarea que realiza.

Para garantizar que el programa se mantenga vivo y receptivo a pesar de las funciones bloqueantes, una estrategia común es utilizar hilos (threads). Los hilos permiten que múltiples tareas se ejecuten concurrentemente. Puedes diseñar el programa para que las tareas bloqueantes se ejecuten en un hilo separado, mientras que otras partes del programa continúan ejecutándose en hilos adicionales. Esto significa que mientras un hilo se bloquea esperando una tarea, otros hilos pueden seguir trabajando y respondiendo a eventos.

**6) Explique qué son los métodos virtuales puros y para qué sirven. De un breve ejemplo donde su uso sea imprescindible.**

Los métodos virtuales puros son funciones definidas en una clase base que no tienen una implementación concreta en esa clase, sino que están destinadas a ser implementadas por las clases derivadas. Se declaran utilizando la sintaxis virtual y = 0 al final de la declaración del método en la clase base.

Estos métodos son utilizados en la programación orientada a objetos y en el concepto de herencia para crear una interfaz común que todas las clases derivadas deben proporcionar. Sirven para definir un contrato que las clases derivadas deben cumplir al implementar el método.

```c++
#include <iostream>

class Figura {
public:
    virtual double calcularArea() const = 0; // Método virtual puro
};

class Triangulo : public Figura {
private:
    double base;
    double altura;

public:
    Triangulo(double b, double h) : base(b), altura(h) {}

    double calcularArea() const override {
        return 0.5 * base * altura;
    }
};

class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(double r) : radio(r) {}

    double calcularArea() const override {
        return 3.14159 * radio * radio;
    }
};

int main() {
    Triangulo triangulo(5.0, 10.0);
    Circulo circulo(3.0);

    Figura* figuras[] = {&triangulo, &circulo};

    for (const auto& figura : figuras) {
        std::cout << "Área: " << figura->calcularArea() << std::endl;
    }

    return 0;
}
```

**7) Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear archivos intermedios y sin subir el archivo a memoria). El procesamiento consiste en leer nros hexadecimales de 4 símbolos y reemplazarlos por su valor decimal (en texto).**

Resuelto

**8) ¿Qué es el polimorfismo? Ejemplifique mediante código.**

El polimorfismo se refiere a la capacidad de que objetos de diferentes clases respondan a una misma llamada de función de una manera específica para cada uno de ellos. En otras palabras, un mismo método puede tener implementaciones diferentes en diferentes clases.
En C++, el polimorfismo se logra a menudo a través de herencia y el uso de funciones virtuales. Las funciones virtuales permiten que las subclases sobrescriban métodos de la superclase para proporcionar su propia implementación. Esto, combinado con el enlace dinámico, posibilita que se seleccione automáticamente la implementación adecuada del método en tiempo de ejecución según el tipo real del objeto.

```c++
#include <iostream>

class Animal {
public:
    virtual void hacerSonido() const {
        std::cout << "Sonido de un animal desconocido" << std::endl;
    }
};

class Perro : public Animal {
public:
    void hacerSonido() const override {
        std::cout << "Guau guau" << std::endl;
    }
};

class Gato : public Animal {
public:
    void hacerSonido() const override {
        std::cout << "Miau miau" << std::endl;
    }
};

int main() {
    Animal* animales[] = {new Perro(), new Gato()};

    for (const auto& animal : animales) {
        animal->hacerSonido();
        delete animal; // Liberar la memoria asignada dinámicamente
    }

    return 0;
}
```

**9) ¿Qué función utiliza para esperar la terminación de un thread? Ejemplifique mediante código.**


En C++, puedes usar la función join() para esperar la terminación de un hilo (thread). La función join() bloqueará la ejecución del hilo actual hasta que el hilo al que se aplica haya finalizado.

Aquí tienes un ejemplo de cómo usar std::thread y join() en C++:

```c++
#include <iostream>
#include <thread>

void miFuncion() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Hilo en ejecución: " << i << std::endl;
    }
}

int main() {
    std::thread miHilo(miFuncion);  // Crear un nuevo hilo

    std::cout << "Hilo principal en ejecución." << std::endl;

    miHilo.join();  // Esperar a que el hilo termine

    std::cout << "Hilo principal finalizado." << std::endl;

    return 0;
}
```
En este ejemplo, se crea un nuevo hilo miHilo que ejecuta la función miFuncion(). El hilo principal imprime un mensaje y luego espera la terminación del hilo miHilo utilizando join(). Esto garantiza que el hilo principal no continúe hasta que el hilo miHilo haya finalizado su ejecución.

**10) Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la cadena A después de haber duplicado todas las ocurrencias de B..**
**ej.: reemp.exe “El final está aprobado” aprobado -----> El final está aprobado aprobado**

Resuelto