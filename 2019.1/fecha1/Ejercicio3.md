# 3) Describa con exactitud las siguientes declaraciones/definiciones globales:
  ## 1. void (*F)(int i);
  #####  Esta declaración define un puntero a una funcion de nombre "F" que recibe como argumento un entero y no devuelve nigun valor (void). 
  ## 2. static void B(float a, float b){}
  #####  Es una definicion de una funcion static de nombre "B" que recibe dos floats como argumentos.  
  ## 3. int *(*C)[5];
  ##### Vemos que la variable C es un puntero a un array de 5 elementos y cada elemento del array es un puntero a entero. 

  ## Ejemplo "saludo":
  ``` 
  char* saludo[6] = {"hola", "que", "onda", "todo", "bien" , "\0" };
  ``` 
  saludo es un array de 6 elementos y cada elemento del array es un puntero a char*.
  ## Ejemplos "ints":
  ```
  int * var[5];
  ```
  Var es una array de 5 elementos y cada elemento es un puntero a entero. 
  ```
  int  (var2*)[5];
  ```
  var2 es un puntero a un array de 5 elementos y cada elemento es un entero. 
  ``` 
  int *(*funcPtr)(int)
  ```
  funcPtr es un puntero a una funcion que recibe un entero como argumento y devuelve un puntero a entero. 
  
  
  
  
