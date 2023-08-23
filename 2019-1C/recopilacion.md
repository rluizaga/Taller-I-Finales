#### Describa con exactitud las sgts declaraciones/definiciones globales: 
```
1. void (*F) (int i);
1. static void B(float a, float b){}
1. int (*C) [5];
```
En (1) vemos que si cambiamos (*F) por X nos queda ``` void X (int i) ```  que es la firma de una funcion.
X es una funcion que recibe un entero y no devuelve nada.  Ahora completo: 
F es un puntero a una funcion que recibe un entero y no devuelve nada. 
Ademas como tiene un ';' es una declaracion de F.
Tiene un scope global. y su lifetime es desde que inicia el programa hasta que termina el programa. 


