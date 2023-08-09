/*
Escriba un programa (desde la inicialización hasta la liberación de los
recursos) que reciba paquetes de la forma [nnn+nn+….+nnnn] (numeros separados
por +, encerrados entre corchetes) e imprima el resultado de la suma de cada
paquete por pantalla. Al recibir un paquete vacío (“[]”) debe cerrarse
ordenadamente. No considere errores.
*/

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT "8080"
#define BUFFER_SIZE 1024

int main() {
  addrinfo hints, *res, *p;
  int status, client_socket;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &res)) != 0) {
    std::cerr << "Error en getaddrinfo: " << gai_strerror(status) << std::endl;
    return EXIT_FAILURE;
  }

  // Recorrer la lista de direcciones y crear el socket
  for (p = res; p != nullptr; p = p->ai_next) {
    if ((client_socket =
             socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
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

  if (p == nullptr) {
    std::cerr << "No se pudo conectar al servidor\n";
    return EXIT_FAILURE;
  }

  std::cout << "Conexión establecida con el servidor en " << SERVER_IP << ":"
            << SERVER_PORT << std::endl;

  // Bucle principal para recibir y procesar paquetes
  char buffer[BUFFER_SIZE];
  int bytesRead;
  std::string currentNumber;
  bool in_brackets = false;
  int sum = 0;

  while ((bytesRead = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
    buffer[bytesRead] = '\0'; // Agregar el carácter nulo al final del buffer
                              // para asegurar que sea una cadena válida

    for (int i = 0; i < bytesRead; i++) {
      char currentChar = buffer[i];

      if (currentChar == '[') {
        in_brackets = true;
        currentNumber.clear();
      } else if (currentChar == ']') {
        in_brackets = false;
        if (!currentNumber.empty()) {
          int number = std::stoi(currentNumber);
          std::cout << "Sumando número: " << number << std::endl;
          sum += number;
          std::cout << "Resultado de la suma del paquete: " << sum << std::endl;
          sum = 0;
        }
      } else if (in_brackets && std::isdigit(currentChar)) {
        currentNumber += currentChar;
      } else if (currentChar == '+') {
        if (!currentNumber.empty()) {
          int number = std::stoi(currentNumber);
          sum += number;
          std::cout << "Sumando número: " << number << std::endl;
          currentNumber.clear();
        }
      }
    }
  }

  // Detener todas las operaciones de lectura y escritura en el socket
  // utilizando
  shutdown(client_socket, SHUT_RDWR);
  // Cerrar el socket y finalizar el cliente
  close(client_socket);

  return 0;
}
