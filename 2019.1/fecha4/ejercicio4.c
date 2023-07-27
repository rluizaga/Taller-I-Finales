/*
Escribir un programa ISO C que procese el archivo “nros_2bytes_bigendian.dat”
sobre sí mismo, eliminando los número múltiplos de 7.
*/

#include <netinet/in.h>
#include <stdio.h>

int main() {
  FILE *file = fopen("nros_2bytes_bigendian.dat", "rb+");
  if (file == NULL) {
    printf("No se pudo abrir el archivo\n");
    return 1;
  }

  int rd = 0;
  int wr = 0;
  unsigned short value;
  unsigned short value_bg;

  while (fread(&value_bg, sizeof(value_bg), 1, file)) {
    rd = ftell(file);
    value = ntohs(value_bg);
    if (value % 7 != 0) {
      fseek(file, wr, SEEK_SET);
      printf("Valor leído: %hu\n", value);
      fwrite(&value_bg, sizeof(value_bg), 1, file);
      wr = ftell(file);
    }
    fseek(file, rd, SEEK_SET);
  }

  ftruncate(fileno(file), wr);
  fclose(file);

  return 0;
}