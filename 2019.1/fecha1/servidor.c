#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <Puerto>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);

    // Crear el socket del servidor
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error al crear el socket del servidor");
        return 1;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Vincular el socket a la dirección y puerto especificados
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error al vincular el socket a la dirección y puerto");
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 1) == -1) {
        perror("Error al escuchar conexiones entrantes");
        return 1;
    }

    printf("Servidor escuchando en el puerto %d...\n", port);

    while (1) {
        // Aceptar una conexión entrante
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Error al aceptar la conexión entrante");
            return 1;
        }

        printf("Cliente conectado.\n");

        /* // Recibir datos del cliente
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));
        if (recv(clientSocket, buffer, BUFFER_SIZE, 0) == -1) {
            perror("Error al recibir datos del cliente");
            return 1;
        }

        printf("Mensaje recibido del cliente: %s\n", buffer);*/

        // Procesar los datos recibidos (aquí puedes realizar la lógica deseada)

        // Enviar respuesta al cliente
        char response[6] = {27, ',', 12, ',', 32, '='};
        if (send(clientSocket, response, 6, 0) == -1) {
            perror("Error al enviar respuesta al cliente");
            return 1;
        }

        // Cerrar el socket del cliente
        close(clientSocket);
        printf("Cliente desconectado.\n");
    }

    // Cerrar el socket del servidor
    close(serverSocket);

    return 0;
}
