/* 
4) Escribir un programa ISO C que reciba por argumento el nombre de un archivo de texto y lo
procese sobre sí mismo (sin crear archivos intermedios ni subiendo todo su contenido a
memoria). El procesamiento consiste en eliminar las líneas de 1 sola palabra.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 1024

bool lineaTieneUnaPalabra(const char *linea) {
    int contador = 0;

    for (int i = 0; i < strlen(linea); i++) {
        if (linea[i] == ' ') {
            contador++;
        }
    }

    if (contador == 0) {
        return true;
    } else {
        return false;
    }
}

void procesar(FILE *archivo) {
    char linea[MAX_SIZE];
    rewind(archivo);
    long rd = 0;
    long wr = 0;
    if (archivo == NULL) {
        printf("El puntero de archivo es nulo.\n");
        return;
    }
    while (fgets(linea, MAX_SIZE, archivo) != NULL) {
        rd = ftell(archivo);
        if (!lineaTieneUnaPalabra(linea)) {
            fseek(archivo, wr, SEEK_SET);
            fputs(linea, archivo);
            wr = ftell(archivo);
        }
        fseek(archivo, rd, SEEK_SET);
    }
    ftruncate(fileno(archivo), wr);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: ejercicio4 archivo.txt\n");
        return 1;
    }

    FILE *archivo = fopen(argv[1], "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    procesar(archivo);

    fclose(archivo);

    return 0;
}