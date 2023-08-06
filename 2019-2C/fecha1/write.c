#include <stdio.h>
#include <stdint.h>

int main() {
  FILE *fp = fopen("nros2bytes.dat", "wb");
  if (fp == NULL) {
    printf("Error opening file");
    return 1;
  }

  int16_t value[] = {1, 2, 3, 4, 5};
  unsigned long sz = sizeof(value) / sizeof(int16_t);
  if (fwrite(value, sizeof(int16_t), sz, fp) != sz) {
    printf("Error writing to file");
    return 1;
  }

  return 0;
}