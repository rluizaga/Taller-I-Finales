/*
Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la
cadena A después de haber duplicado todas las ocurrencias de B.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void duplicate_occurrences(const char *cadena1, const char *cadena2) {
  int len1 = strlen(cadena1);
  int len2 = strlen(cadena2);

  // Verificar si la cadena2 no está vacía
  if (len2 == 0) {
    printf("%s", cadena1);
    return;
  }

  // Contar el numero de veces que aparece la cadena2 en la cadena1
  int count = 0;
  const char *ptr = cadena1;
  while ((ptr = strstr(ptr, cadena2)) != NULL) {
    count++;
    ptr += len2;
  }

  // Calcular la longitud de la cadena resultante
  int len_result = len1 + count * len2;
  char *result = (char *)malloc(len_result + 1);
  if (result == NULL) {
    printf("Error al reservar memoria");
    return;
  }

  // Duplicar las ocurrencias de cadena2 en la cadena1
  char *ptr_result = result;
  ptr = cadena1;
  while ((ptr = strstr(ptr, cadena2)) != NULL) {
    int len_before = ptr - cadena1;
    int len_after = len1 - len_before - len2;

    // Copiar la parte antes de la ocurrencia
    memcpy(ptr_result, cadena1, len_before + len2 +1);
    ptr_result += len_before + len2 + 1;

    // Copiar la ocurrencia
    memcpy(ptr_result, cadena2, len2);
    ptr_result += len2;

    // Actualizar puntero de cadena1
      cadena1 = ptr + len2;
      ptr += len2;
      len1 = len_after;
  }

  // Copiar la parte restante de cadena1
    strcpy(ptr_result, cadena1);

  // Imprimir la cadena resultante
  printf("%s\n", result);
}

int main() {
  char cadena1[] = "0 23 5";
  char cadena2[] = "23";

  duplicate_occurrences(cadena1, cadena2);
  return 0;
}