/*
Escribir un programa ISO C Multiplataforma que procese el archivo "base5.txt"
sobre si mismo. El procesamiento consiste en leer numeros base 5 de 6 simbolos y
duplicar aquellos multiplos de 23.
*/
#include <stdio.h>
#include <string.h>

int convert_to_decimal(char *number_base5) {
  int result = 0;
  int power = 1;
  int len = strlen(number_base5);

  for (int i = len - 1; i >= 0; --i) {
    result += (number_base5[i] - '0') * power;
    power *= 5;
  }

  return result;
}

void resize_and_shift(FILE *fp, int shift_sz) {
  fseek(fp, 0, SEEK_END);
  int initial_sz = ftell(fp);
  int final_sz = initial_sz + shift_sz;
  char c;

  for (int i = initial_sz - 1; i >= 0; --i) {
    fseek(fp, i, SEEK_SET);
    fread(&c, sizeof(char), 1, fp);
    fseek(fp, i + shift_sz, SEEK_SET);
    fwrite(&c, sizeof(char), 1, fp);
  }

  ftruncate(fileno(fp), final_sz);
}

void process(FILE *fp) {
  int shift_sz = 0;
  int number;
  char number_base5[7];

  while (fread(number_base5, sizeof(char), 6, fp)) {
    number_base5[7] = '\0';
    number = convert_to_decimal(number_base5);
    printf("%s --> %d\n", number_base5, number);
    if (number % 23 == 0) {
      shift_sz += 6;
    }
  }

  resize_and_shift(fp, shift_sz);

  rewind(fp);

  int rd = shift_sz;
  int wr = 0;

  fseek(fp, rd, SEEK_SET);

  while (fread(number_base5, sizeof(char), 6, fp)) {
    rd = ftell(fp);
    fseek(fp, wr, SEEK_SET);
    fwrite(number_base5, sizeof(char), 6, fp);
    wr = ftell(fp);

    number_base5[7] = '\0';
    number = convert_to_decimal(number_base5);
    
    if (number % 23 == 0) {
      fseek(fp, wr, SEEK_SET);
      fwrite(number_base5, sizeof(char), 6, fp);
      wr = ftell(fp);
    }

    fseek(fp, rd, SEEK_SET);
  }
}

int main() {
  FILE *fp;
  fp = fopen("base5.txt", "r+");

  if (fp == NULL) {
    printf("Error al abrir el archivo");
    return 1;
  }

  process(fp);

  return 0;
}