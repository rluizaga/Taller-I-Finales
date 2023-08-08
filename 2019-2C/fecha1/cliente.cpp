/*
Cliente usando sockets
*/

#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

void send_data(int client_socket) {
  std::string data;
  std::cout << "Introduce los datos a enviar: " << std::endl;

  while (true) {
    std::getline(std::cin, data);
    if (send(client_socket, data.c_str(), data.length(), 0) == -1) {
      std::cerr << "Error al enviar" << std::endl;
      return;
    }

    if (data == "FINAL") {
      break;
    }
  }
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Uso: " << argv[0] << " <host> <puerto>" << std::endl;
    return 1;
  }

  char *host = argv[1];
  char *port = argv[2];

  struct addrinfo hints, *res, *p;
  int status, client_socket;

  // Inicializar hints
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  // Obtener información de la dirección
  if ((status = getaddrinfo(host, port, &hints, &res)) != 0) {
    std::cout << "getaddrinfo: " << gai_strerror(status) << std::endl;
    return 1;
  }

  // Recorrer la lista de direcciones
  for (p = res; p != NULL; p = p->ai_next) {
    client_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (client_socket == -1) {
      std::cerr << "Error al crear el socket" << std::endl;
      continue;
    }

    if (connect(client_socket, p->ai_addr, p->ai_addrlen) == -1) {
      std::cerr << "Error al conectar el socket" << std::endl;
      close(client_socket);
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  if (p == NULL) {
    std::cerr << "No se pudo conectar" << std::endl;
    return 1;
  }

  std::cout << "Conectado" << std::endl;

  send_data(client_socket);

  return 0;
}