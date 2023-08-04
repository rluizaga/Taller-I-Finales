/*
Escriba un programa C que tome 2 cadenas por línea de comandos: A y B; e imprima la
cadena A después de haber duplicado todas las ocurrencias de B.
*/

#include <stdio.h>
#include <string.h>

int main() {
    char cadenaA[] = "hola al mundo al";
    char cadenaB[] = "al";
    char *saveptr;

    char *token = strtok_r(cadenaA, " ", &saveptr);
    while (token != NULL) {
        printf("%s ", token);
        if (strcmp(token, cadenaB) == 0) {
            printf("%s ", token); // Imprimir la ocurrencia duplicada
        }
        token = strtok_r(NULL, " ", &saveptr);
    }

    printf("\n");

    return 0;
}
