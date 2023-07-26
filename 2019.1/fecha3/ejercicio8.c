/*
Escriba un programa (desde la inicialización hasta la liberación de los recursos) que reciba
paquetes de la forma [nnn+nn+….+nnnn] (numeros separados por +, encerrados entre
corchetes) e imprima el resultado de la suma de cada paquete por pantalla. Al recibir un
paquete vacío (“[]”) debe cerrarse ordenadamente. No considere errores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    const char* ip = "127.0.0.1";
    const char* port = "8080";

    struct addrinfo hints, *res, *p;
    int status, client_socket;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
        fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(status));
        return EXIT_FAILURE;
    }

    // recorrer la lista de direcciones y crear el socket
    for (p = res; p != NULL; p = p->ai_next) {
        if ((client_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Error en el socket");
            continue;
        }
        if (connect(client_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(client_socket);
            perror("Error en el connect");
            continue;
        }
        break;
    }

    freeaddrinfo(res);
    
    if(p == NULL) {
        fprintf(stderr, "No se pudo conectar al servidor\n");
        return EXIT_FAILURE;
    }

    printf("Conexión establecida con el servidor en %s:%s\n", ip, port);

    // Bucle principal para recibir y procesar paquetes
    char buffer;
    int sum = 0;
    bool in_brackets = false;
    bool in_operation = false;

    while (recv(client_socket, &buffer, 1, 0) > 0) {
        if (buffer == '[') {
            // Comenzar a procesar un paquete
            sum = 0;
            in_brackets = true;
        } else if (buffer == ']') {
            // Finalizar el paquete y mostrar el resultado de la suma
            if (in_brackets && in_operation) {
                in_operation = false;
                printf("Resultado de la suma del paquete: %d\n", sum);
            }
            in_brackets = false;
        } else if (in_brackets) {
            // Sumar los números dentro del paquete
            if(buffer != '+') {
                sum += buffer;
            }
            in_operation = true;
        }
    }


    // Cerrar el socket y finalizar el cliente
    close(client_socket);

    return 0;
}