/*
Escriba un programa que imprima por salida estándar los números entre 1 y 100, en orden
ascendente. Se pide que los números sean contabilizados por una variable global única y que
los pares sean escritos por un hilo mientras que los impares sean escritos por otro.
Contemple la correcta sincronización entre hilos y la liberación de los recursos utilizados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUM 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int contador = 1;

void* imprimir_pares(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (contador > MAX_NUM) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (contador % 2 == 0) {
            printf("Hilo Pares: %d\n", contador);
            contador++;
        }

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* imprimir_impares(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (contador > MAX_NUM) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (contador % 2 != 0) {
            printf("Hilo Impares: %d\n", contador);
            contador++;
        }

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilo_pares, hilo_impares;

    if (pthread_create(&hilo_pares, NULL, imprimir_pares, NULL) != 0) {
        fprintf(stderr, "Error al crear el hilo pares.\n");
        return 1;
    }

    if (pthread_create(&hilo_impares, NULL, imprimir_impares, NULL) != 0) {
        fprintf(stderr, "Error al crear el hilo impares.\n");
        return 1;
    }

    pthread_join(hilo_pares, NULL);
    pthread_join(hilo_impares, NULL);

    return 0;
}
