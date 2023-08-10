#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

int main() {
  FILE *file = fopen("enteros.dat", "rb");
  uint16_t number;
  while (fread(&number, sizeof(number), 1, file)) {
    printf("%hu\n", ntohs(number));
  }

  return 0;
}