/*
Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la
cadena A después de haber duplicado todas las ocurrencias de B..
ej.: reemp.exe “Este es el final” final -----> Este es el final final
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void duplicate_occurrences(const char *cadena1, const char *cadena2) {
    int len1 = strlen(cadena1);
    int len2 = strlen(cadena2);

    // Verificar si la cadena2 no está vacía
    if (len2 == 0) {
        printf("%s\n", cadena1);
        return;
    }

    // Contar el número de ocurrencias de cadena2 en cadena1
    int count = 0;
    const char *ptr = cadena1;
    while ((ptr = strstr(ptr, cadena2)) != NULL) {
        count++;
        ptr += len2;
    }

    // Calcular la longitud de la nueva cadena con las duplicaciones
    int new_len = len1 + count * len2;
    char *new_cadena = (char *)malloc(new_len + 1);
    if (new_cadena == NULL) {
        perror("Error al asignar memoria");
        return;
    }

    printf("original: %i\n", len1);
    printf("nuevo: %i\n", new_len);

    // Duplicar las ocurrencias de cadena2 en cadena1
    char *new_ptr = new_cadena;
    ptr = cadena1;
    while ((ptr = strstr(ptr, cadena2)) != NULL) {
        printf("entre\n");
        int len_before_occurrence = ptr - cadena1;
        int len_after_occurrence = len1 - len_before_occurrence - len2;

        // Copiar parte antes de la ocurrencia de cadena2
        strncpy(new_ptr, cadena1, len_before_occurrence);
        new_ptr += len_before_occurrence;

        // Duplicar cadena2
        strncpy(new_ptr, cadena2, len2);
        new_ptr += len2;

        // Actualizar puntero de cadena1
        cadena1 = ptr + len2;
        ptr += len2;
        len1 = len_after_occurrence;
    }

    // Copiar la parte restante de cadena1
    strcpy(new_ptr, cadena1);

    // Imprimir la cadena con las duplicaciones
    printf("%s\n", new_cadena);

    // Liberar la memoria asignada
    free(new_cadena);
}

int main() {
    char cadena1[] = "0 23 5";
    char cadena2[] = "23";

    duplicate_occurrences(cadena1, cadena2);

    return 0;
}
