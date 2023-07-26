/*
2) Escriba una función ISO C llamada Replicar que reciba 1 cadena (S), dos índices (I1 e I2) y
una cantidad (Q). La función debe retornar una copia de S salvo los caracteres que se
encuentran entre los índices I1 e I2 que serán duplicados Q veces.
Ej. replicar(“Hola”, 1, 2, 3) retorna “Hololola”.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* replicar(char* S, int I1, int I2, int Q) {
    int final_sz = strlen(S) + (I2 - I1 + 1) * (Q - 1);
    char* replica = (char*) malloc(sizeof(char) * final_sz + 1);

    memcpy(replica, S, I1);

    for (size_t i = 0; i < Q; i++)
    {
        memcpy(&replica[I1 + (I2 - I1 + 1) * i], &S[I1], I2 - I1 + 1);
    }

        memcpy(&replica[I1 + (I2 - I1 + 1) * Q], &S[I2 +1], strlen(S) - I2);
    
    replica[final_sz] = '\0';
    return replica;
}

int main() {
    char* input = "hola";
    char* result = replicar(input, 1, 2, 3);

    printf("String original: %s\n", input);
    printf("String modificado: %s\n", result);

    free(result);

    return 0;
}