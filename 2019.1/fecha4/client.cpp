#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

void send_data(int client_socket) {
  std::cout << "Envía tus datos al servidor. Escribe 'FIN' para finalizar."
            << std::endl;

  while (true) {
    std::string input;
    std::getline(std::cin, input);

    if (send(client_socket, input.c_str(), input.length(), 0) == -1) {
      std::cerr << "Error en el send" << std::endl;
      break;
    }

    if (input == "FIN") {
      std::cout << "Texto 'FIN' enviado. Finalizando la conexión." << std::endl;
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Uso: " << argv[0] << " <IP> <PUERTO>" << std::endl;
    return EXIT_FAILURE;
  }

  const char *ip = argv[1];
  const char *port = argv[2];

  struct addrinfo hints, *res, *p;
  int status, client_socket;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
    std::cerr << "Error en getaddrinfo" << gai_strerror(status) << std::endl;
    return EXIT_FAILURE;
  }

  for (p = res; p != nullptr; p = p->ai_next) {
    if ((client_socket =
             socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      std::cerr << "Error en el socket: " << strerror(errno) << std::endl;
      continue;
    }

    if (connect(client_socket, p->ai_addr, p->ai_addrlen) == -1) {
      close(client_socket); // Cerrar el socket antes de continuar
      std::cerr << "Error en la conexión: " << strerror(errno) << std::endl;
      continue;
    }
    break;
  }

  if (p == nullptr) {
    std::cerr << "No se pudo conectar al servidor" << std::endl;
    return EXIT_FAILURE;
  }

  freeaddrinfo(res);

  std::cout << "Conexión establecida con el servidor en " << ip << ":" << port
            << std::endl;

  send_data(client_socket);

  close(client_socket);

  return 0;
}