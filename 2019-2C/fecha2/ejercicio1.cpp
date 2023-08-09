/*
Escriba un programa (desde la inicialización hasta la liberación de los
recursos) que reciba paquetes de la forma nnn+nn+....+nnnn= (numeros separados
por +, seguidos de =) e imprima el resultado de la suma de cada paquete por
pantalla. Al recibir un paquete vacío (“=”) debe cerrarse ordenadamente. No
considere errores.
*/

#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "8080"
#define BUFFER_SIZE 1024

void recv_data(int sockfd) {
  char buffer[BUFFER_SIZE];
  int bytes_read;
  std::string current_number;
  int result = 0;

  while ((bytes_read = read(sockfd, buffer, BUFFER_SIZE))) {
    buffer[bytes_read] = '\0';
    std::cout << buffer << std::endl;

    for (int i = 0; i < bytes_read; i++) {
      char current_char = buffer[i];
      if (std::isdigit(current_char)) {
        current_number += current_char;
      } else if (current_char == '+') {
        result += std::stoi(current_number);
        current_number.clear();
      } else if (current_char == '=') {
        result += std::stoi(current_number);
        std::cout << result << std::endl;
        result = 0;
        current_number.clear();
      }
    }
  }
}

  int main() {
    struct addrinfo hints, *res, *p;
    int status, sockfd;

    // Configurar parametros para getaddrinfo
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &res);
    if (status != 0) {
      std::cerr << "Error en getaddrinfo: " << gai_strerror(status)
                << std::endl;
      return 1;
    }

    // Recorrer las direcciones disponibles
    for (p = res; p != NULL; p = p->ai_next) {
      if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) ==
          -1) {
        std::cerr << "Error en socket" << std::endl;
        continue;
      }

      if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        std::cerr << "Error en connect" << std::endl;
        close(sockfd);
        continue;
      }

      break;
    }

    freeaddrinfo(res);

    if (p == NULL) {
      std::cerr << "No se pudo conectar con el servidor" << std::endl;
      return 1;
    }

    std::cout << "Conectado al servidor" << std::endl;

    recv_data(sockfd);

    close(sockfd);
    return 0;
  }
