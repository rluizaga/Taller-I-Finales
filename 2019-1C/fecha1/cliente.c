#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <IP> <Puerto>\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    // Crear el socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error al crear el socket");
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &(serverAddress.sin_addr)) <= 0) {
        perror("Error al configurar la dirección del servidor");
        return 1;
    }

    // Conectar al servidor
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error al conectar al servidor");
        return 1;
    }

    // Leer y enviar datos al servidor
    char buffer[BUFFER_SIZE];
    printf("Ingrese un mensaje: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Enviar datos al servidor
    if (send(clientSocket, buffer, strlen(buffer), 0) == -1) {
        perror("Error al enviar datos al servidor");
        return 1;
    }

    // Recibir respuesta del servidor
    memset(buffer, 0, sizeof(buffer));
    if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("Error al recibir respuesta del servidor");
        return 1;
    }

    printf("Respuesta del servidor: %s\n", buffer);

    // Cerrar el socket
    close(clientSocket);

    return 0;
}
