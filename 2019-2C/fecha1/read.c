#include <stdint.h>
#include <stdio.h>

int main() {
  FILE *fp = fopen("nros2bytes.dat", "rb");
  if (fp == NULL) {
    printf("Error al abrir el archivo\n");
    return 1;
  }

  int16_t value;

  while (fread(&value, sizeof(int16_t), 1, fp) == 1) {
    printf("%d\n", value);
  }

  return 0;
}