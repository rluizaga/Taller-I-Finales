#### Describa con exactitud las sgts declaraciones/definiciones globales: 
```
1. void (*F) (int i);
2. static void B(float a, float b){}
3. int *(*C) [5];
```
En (1) vemos que si cambiamos (*F) por X nos queda ``` void X(int i) ```  que es la firma de una funcion.
X es una funcion que recibe un entero y no devuelve nada.  Ahora completo: 
F es un puntero a una funcion que recibe un entero y no devuelve nada. 
Ademas como tiene un ';' es una declaracion de F.
Tiene un scope global. y su lifetime es desde que inicia el programa hasta que termina el programa. 

En (2) Vemos que tenemos la firma de una funcion definida (por los {}). 
Ademas tenemos el modificador static entonces la funcion B  tiene como Scope: este unico archivo.  
Lifetime: Desde que inicia el  programa hasta que termina. 
B es una funcion que recibe dos floats a y b , no devuelve nada y no hace nada. 

En (3) si cambiamos (*C) por X tenemos ```int *X[5] ```  
Obtenemos X es array de 5 punteros a enteros. Entonces completo: 
C es un puntero a un array de 5 punteros a enteros. 
Debido al ';' es una declaracion de una variable. 
Scope: global  . Lifetime: Inicio a Fin del programa. 


