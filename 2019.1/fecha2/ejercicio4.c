/*
4) Escribir un programa C que procese el archivo “numeros.txt” sobre sí mismo (sin crear
archivos intermedios y sin subir el archivo a memoria). El procesamiento consiste en leer
grupos de 4 caracteres hexadecimales y reemplazarlos por los correspondientes dígitos
decimales (que representen el mismo número leído pero en decimal).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

// Función para convertir un grupo de 4 caracteres hexadecimales a su valor decimal correspondiente
int hexGroupToDecimal(const char* hexGroup) {
    // Usamos strtol para realizar la conversión a decimal
    char* endptr;
    long int result = strtol(hexGroup, &endptr, 16);

    // Verificamos si hubo errores durante la conversión
    if (*endptr != '\0' || endptr == hexGroup) {
        // Caracter hexadecimal inválido o no se pudo realizar la conversión.
        // Devolvemos un valor negativo para indicar un error.
        return -1;
    }

    return (int)result; // Devolvemos el resultado como entero
}

void resize_and_shift_file_inplace(FILE* file, size_t n) {
    fseek(file, 0, SEEK_END);
    size_t file_sz = ftell(file);
    size_t new_file_sz = file_sz + n;

    for (long int i = file_sz - 1; i >= 0; --i) {
        fseek(file, i, SEEK_SET);
        char c = fgetc(file);
        fseek(file, i + n, SEEK_SET);
        fputc(c, file);
    }

    ftruncate(fileno(file), new_file_sz);
}

void procesar(FILE* file) {
    char line[MAX_SIZE];
    int count = 0;
    
    //Primera pasada para saber cuantos bytes debo agregar
    while(fgets(line, sizeof(line), file) != NULL) {
        count ++;
    }

    // Redimensionar y desplazar el archivo "in place"
    resize_and_shift_file_inplace(file, count);

    // Leer y escribir
    int rd = count;
    int wr = 0;
    char hexa[5];
    int decimal;
    char decimal_str[MAX_SIZE];
    int final_sz = 0;
    fseek(file, rd, SEEK_SET);
    while(fgets(line, sizeof(line), file) != NULL) {
        rd = ftell(file);
        if (strlen(line) > 1) {
            printf("%s",line);
            memcpy(hexa, line, 4);
            hexa[4] = '\0';
            decimal = hexGroupToDecimal(hexa);
            final_sz += sprintf(decimal_str, "%d\n", decimal);
            fseek(file, wr, SEEK_SET);
            fputs(decimal_str, file);
            wr = ftell(file);
        }
        fseek(file, rd, SEEK_SET);
    }
    ftruncate(fileno(file), final_sz);
}

int main() {
    FILE *file = fopen("numeros.txt", "r+");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    procesar(file);

    return 0;
}

