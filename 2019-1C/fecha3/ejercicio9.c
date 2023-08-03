/*
Escriba una función ISO C que permita procesar un archivo texto que contenga frases (1
por línea) sobre sí mismo, sin generar archivos intermedios ni cargar el archivo completo a
memoria. El procesamiento consiste en eliminar las palabras de más de 3 letras de cada línea.
*/

#include <stdio.h>
#include <string.h>

#define WORD_SIZE 1024

int main() {
    FILE *file = fopen("archivo.txt", "r+");
    if (file == NULL) {
        printf("El puntero del archivo es nulo.\n");
        return 1;
    }

    char word[WORD_SIZE];
    char c;
    int index = 0;

    int rd = 0;
    int wr = 0;

    while ((c=fgetc(file)) != EOF) {
        if (c == ' ' || c == '\n') {
            word[index] = '\0';
            if (index <= 3) {
                fseek(file, wr, SEEK_SET);
                fwrite(word, sizeof(char), strlen(word),file);
                wr = ftell(file);
            }
            fseek(file, wr, SEEK_SET);
            fwrite(&c, sizeof(char), 1,file);
            wr = ftell(file);
            index = 0;
        } else if(index <= 3){
            word[index] = c;
            index++;
        } else {
            index++;
        }
        rd++;
        fseek(file, rd, SEEK_SET);
    }
    ftruncate(fileno(file), wr);
    return 0;
}