/*
Escribir un programa ISO C que procese el archivo “nros2bytes.dat” sobre sí
mismo, duplicando los enteros de 2 bytes múltiplos de 3.
*/

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void resize_and_shift(FILE *fp, int offset) {
  fseek(fp, 0, SEEK_END);
  int file_size = ftell(fp);
  int new_size = file_size + offset;
  int16_t value;

  for (int i = file_size - 1; i >= 0; i--) {
    fseek(fp, i, SEEK_SET);
    fread(&value, sizeof(int16_t), 1, fp);
    fseek(fp, i + offset, SEEK_SET);
    fwrite(&value, sizeof(int16_t), 1, fp);
  }

  ftruncate(fileno(fp), new_size);
}

void double_multiples_of_three(FILE *fp) {
  int offset = 0;
  int16_t value;

  // first pass to count final size
  while (fread(&value, sizeof(int16_t), 1, fp) == 1) {
    if (value % 3 == 0) {
      offset += sizeof(int16_t);
    }
  }

  // resize and shift file "in-place"
  resize_and_shift(fp, offset);

  int rd = offset;
  int wr = 0;

   // second pass to double values
  fseek(fp, rd, SEEK_SET);
  while (fread(&value, sizeof(int16_t), 1, fp) == 1) {
    rd = ftell(fp);
    fseek(fp, wr, SEEK_SET);
    fwrite(&value, sizeof(int16_t), 1, fp);
    if (value % 3 == 0) {
      fwrite(&value, sizeof(int16_t), 1, fp);
    }
    wr = ftell(fp);
    fseek(fp, rd, SEEK_SET);
  }
}

int main() {
  FILE *fp = fopen("nros2bytes.dat", "rb+");
  if (fp == NULL) {
    printf("Error al abrir el archivo\n");
    return 1;
  }

  double_multiples_of_three(fp);

  return 0;
}