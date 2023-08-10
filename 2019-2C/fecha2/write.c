#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

int main() {
  FILE *file = fopen("enteros.dat", "wb");
  int16_t numbers[10];

  for (int i = 0; i < 10; i++) {
    numbers[i] = htons(i);
  }

  if (fwrite(numbers, sizeof(int16_t), 10, file) != 10) {
    printf("Error al escribir el archivo\n");
  }

  return 0;
}
