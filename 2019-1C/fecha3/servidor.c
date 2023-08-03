#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 14

int main() {
    char* ip = "127.0.0.1";
    char* port = "8080";

    struct addrinfo hints, *res, *p;
    int status, server_socket, client_socket;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
        fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(status));
        return EXIT_FAILURE;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        if ((server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Error en el socket");
            continue;
        }
        if (bind(server_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(server_socket);
            perror("Error en el bind");
            continue;
        }
        break;
    }

    freeaddrinfo(res);

    if (p == NULL) {
        fprintf(stderr, "No se pudo hacer bind\n");
        return EXIT_FAILURE;
    }

    if (listen(server_socket, 1) == -1) {
        perror("Error en listen");
        return EXIT_FAILURE;
    }

    printf("Servidor esperando conexiones en %s:%s\n", ip, port);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    
    if (client_socket == -1) {
        perror("Error en accept");
        close(server_socket);
        return EXIT_FAILURE;
    }

    printf("Cliente conectado\n");

    char buffer[] = "[124+20+32][11+26][]";
    if (send(client_socket, buffer, sizeof(buffer)-1, 0) == -1) {
        perror("Error al enviar respuesta al cliente");
        return 1;
    }

    // Cerrar sockets y liberar recursos
    close(client_socket);
    close(server_socket);

    return 0;
}