/*
7) Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa
debe aceptar una única conexión e imprimir en stdout la sumatoria de los enteros recibidos
en cada paquete. Un paquete está definido como una sucesión de números recibidos como
texto, en decimal, separados por comas y terminado con un signo igual (ej: “27,12,32=”). Al
recibir el texto ‘FIN’ debe finalizar el programa ordenadamente liberando los recursos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#define BUFFER_SIZE 2

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <IP> <PUERTO>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *ip = argv[1];
    const char *port = argv[2];

    struct addrinfo hints, *res, *p;
    int status, server_socket, client_socket;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Solo soportamos IPv4 en este ejemplo
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
        fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // Recorrer la lista de direcciones y crear el socket
    for (p = res; p != NULL; p = p->ai_next) {
        if ((server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Error en socket");
            continue;
        }

        if (bind(server_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(server_socket);
            perror("Error en bind");
            continue;
        }

        break; // Si llegamos aquí, encontramos una dirección y bind exitoso
    }

    if (p == NULL) {
        fprintf(stderr, "No se pudo hacer bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    if (listen(server_socket, 1) == -1) {
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    printf("Servidor esperando conexiones en %s:%s\n", ip, port);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Error en accept");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado\n");

    // Bucle principal para recibir y imprimir los datos del cliente
    char buffer[BUFFER_SIZE];
    int suma = 0;
    bool terminar = false;
    while (!terminar)
    {
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) != -1) {
            if(buffer[1] == ',') {
                suma = suma + buffer[0];
            } else if (buffer[1] == '=') {
                suma = suma + buffer[0];
                terminar = true;
            }   
        }
    }
    printf("total = %i\n", suma);

    // Cerrar sockets y liberar recursos
    close(client_socket);
    close(server_socket);

    return 0;
}
