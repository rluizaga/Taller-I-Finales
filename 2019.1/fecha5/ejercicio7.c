/*
7) Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo
(sin crear archivos intermedios y sin subir el archivo a memoria). El
procesamiento consiste en leer nros hexadecimales de 4 símbolos y reemplazarlos
por su valor decimal (en texto).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 1024

int hexGroupToDecimal(char *hexa) {
  char *ptr;
  int decimal = strtol(hexa, &ptr, 16);

  if (*ptr != '\0' || ptr == hexa) {
    return -1;
  }

  return decimal;
}

void resizeAndShiftFileInplace(FILE *file, int shift) {
  fseek(file, 0, SEEK_END);
  int file_sz = ftell(file);

  int new_sz = file_sz + shift;

  for (int i = new_sz; i > 0; --i) {
    fseek(file, i, SEEK_SET);
    char c = fgetc(file);
    fseek(file, i + shift, SEEK_SET);
    fputc(c, file);
  }

  ftruncate(fileno(file), new_sz);

  rewind(file);
}

void processFile(FILE *file) {
  char line[MAX_SIZE];
  int count = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    count++;
  }

  rewind(file);

  resizeAndShiftFileInplace(file, count);

  int rd = count;
  int wr = 0;

  int decimal;
  char decimalStr[6];
  char hexa[5];
  int final_sz = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    rd = ftell(file);
    memcpy(hexa, line, 4);
    hexa[4] = '\0';
    decimal = hexGroupToDecimal(hexa);
    final_sz += sprintf(decimalStr, "%d\n", decimal);
    fseek(file, wr, SEEK_SET);
    fputs(decimalStr, file);
    wr = ftell(file);
    fseek(file, rd, SEEK_SET);
  }
  ftruncate(fileno(file), final_sz);
}

int main() {
  FILE *file = fopen("numeros.txt", "r+");

  if (file == NULL) {
    printf("Error al abrir el archivo\n");
  }

  processFile(file);

  fclose(file);
  return 0;
}