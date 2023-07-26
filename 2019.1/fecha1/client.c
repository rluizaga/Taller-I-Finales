#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <IP> <PUERTO>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *ip = argv[1];
    const char *port = argv[2];

    struct addrinfo hints, *res, *p;
    int status, client_socket;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Solo soportamos IPv4 en este ejemplo
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
        fprintf(stderr, "Error en getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // Recorrer la lista de direcciones y crear el socket
    for (p = res; p != NULL; p = p->ai_next) {
        if ((client_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Error en socket");
            continue;
        }

        if (connect(client_socket, p->ai_addr, p->ai_addrlen) == -1) {
            close(client_socket);
            perror("Error en connect");
            continue;
        }

        break; // Si llegamos aquí, la conexión fue exitosa
    }

    if (p == NULL) {
        fprintf(stderr, "No se pudo conectar al servidor\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(res);

    printf("Conexión establecida con el servidor en %s:%s\n", ip, port);

    // Bucle principal para enviar datos al servidor
    char buffer[6] = {27, ',', 12, ',', 32, '='};
    if (send(client_socket, buffer, 6, 0) == -1) {
            perror("Error al enviar respuesta al cliente");
            return 1;
        }

    // Cerrar el socket y finalizar el cliente
    close(client_socket);

    return 0;
}
