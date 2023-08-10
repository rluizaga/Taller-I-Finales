/*
Escribir un programa ISO C  que procese el archivo de  enteros de 2 bytes
bigendian cuyo nombre es recibido como parámetro.  El procesamiento consiste en
eliminar los número múltiplos   de   3,  trabajando sobre el mismo archivo (sin
archivos intermedios ni en memoria).
*/

#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main () {
  FILE *file = fopen("enteros.dat", "rb+");
  
  int16_t value;
  int rd = 0;
  int wr = 0;

  while (fread(&value, sizeof(int16_t), 1, file)) {
    rd = ftell(file);
    // Si value no es multiplo de 3, escribirlo en el archivo
    if (value % 3 != 0) {
      fseek(file, wr, SEEK_SET);
      fwrite(&value, sizeof(int16_t), 1, file);
      wr = ftell(file);      
    }

    fseek(file, rd, SEEK_SET);
  }

  ftruncate(fileno(file), wr);

  return 0;
}