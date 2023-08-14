/*
Escribir una funcion ISO C prototipada `int copiar(FILE *f, unsigned offSetTo,
unsigned offSetFrom, unsigned length)` que copie a la posicion offSetTo (para
adelante o para atras) el contenido del archivo f delimitado por lenght bytes
desde offSetFrom. La funcion debe devolver un entero con el siguiente
significado: 0 -> ok o <0 -> errores
*/

#include <stdio.h>
#include <stdlib.h>

int copiar(FILE *f, unsigned offSetTo, unsigned offSetFrom, unsigned length) {
  int offset = abs(offSetFrom - offSetTo);
  char c;

  if (offSetFrom == offSetTo) {
    return 0;
  }

  if (offSetFrom > offSetTo) {
    for (int i = offSetFrom; i < offSetFrom + length; i++) {
      fseek(f, i, SEEK_SET);
      fread(&c, 1, 1, f);
      fseek(f, i - offset, SEEK_SET);
      fwrite(&c, 1, 1, f);
    }
  } else {
    for (int i = offSetFrom + length; i > offSetFrom; i--) {
      fseek(f, i - 1, SEEK_SET);
      fread(&c, 1, 1, f);
      fseek(f, i + offset - 1, SEEK_SET);
      fwrite(&c, 1, 1, f);
    }
  }

  return 0;
}

int main() {
  FILE *file = fopen("archivo.txt", "r+");

  if (file == NULL) {
    printf("Error al abrir el archivo");
    return 1;
  }

  int value = copiar(file, 8, 4, 4);
  printf("%d\n", value);

  return 0;
}