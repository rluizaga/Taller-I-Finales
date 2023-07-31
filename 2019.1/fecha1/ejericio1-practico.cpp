#include <iostream>
/*
Explique qué es y para qué sirve un constructor de copia en C++. a) Indique cómo se
comporta el sistema si éste no es definido por el desarrollador; b) Explique al menos una
estrategia para evitar que una clase particular sea copiable; c) Indique qué diferencia existe
entre un constructor de copia y uno move

Un constructor de copia es un constructor que tiene como argumento una referencia de otro objeto
de la misma clase por lo tanto los atributos del objeto que se esta creando se inicializaran con el valor
del los atributos del objeto que se pasa como argumento.

a) Si no esta definido el constructor de copia entonces el se  genera automaticamente un cosntructor
que copia bit por bit  todos los atributos del objeto que se recibe como argumento al objeto que se esta creando.

b) Para evitar que una clase sea copiable podemos
 eliminar el constructor por copia de la siguiente manera:
    ClaseFoo (ClaseFoo& unObjetoDeFoo) = delete;

c)La diferencia es que el constructor de copia, copia byte por byte los atributos del objeto
 pasado por agumento al objeto que se esta creando. En cambio con el move transferimos el ownerShip
 del objeto que le pasamos argumento al objeto que se esta creando, es decir "robamos" o "movemos"
 el recurso del objeto fuente dejandolo en un estado seguro para ser destruido.


*/


class Persona {
private:
    int edad;
    int DNI;

public:

    Persona(){
        edad = 0;
        DNI = 0;
    }

    void setValores(int unaEdad, int unDni){
        this->edad = unaEdad;
        this->DNI = unDni;
    }

    void printPersona(){
        std::cout << "Edad: " << edad << "DNI: " << DNI <<"\n";
    }
    //Eliminamos el construtor de copia.
    Persona (const Persona& otraPersona) = delete;

    //Implementamos el constructor por moviento.
    Persona(Persona&& otraPersona) {
        this->edad = otraPersona.edad;
        this->DNI = otraPersona.DNI;
    }
};


int main() {
    Persona juan;
    juan.setValores(100,111);
    Persona pedro(std::move(juan));
    // Aca usar un metodo para juan ya no tiene sentido porque le robamos su "recurso".  
    juan.printPersona();
    pedro.printPersona();
}