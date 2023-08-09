#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

#define IP "127.0.0.1"
#define PORT "8080"
#define MAX_BACKLOG 1

void send_data(int fd) {
  std::string data = "12+10+1+10+30=";

  if (send(fd, data.c_str(), data.size(), 0) == -1) {
    std::cerr << "Error: send" << std::endl;
  }
}

int main() {
  struct addrinfo hints, *res, *p;
  int status, server_fd, client_fd;

  // Configuramos los parametros de getaddrinfo
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo(IP, PORT, &hints, &res);
  if (status != 0) {
    std::cerr << "Error: getaddrinfo: " << gai_strerror(status) << std::endl;
    return 1;
  }

  // Recorremos la lista de direcciones obtenidas
  for (p = res; p != NULL; p = p->ai_next) {
    server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (server_fd == -1) {
      std::cerr << "Error: socket" << std::endl;
      continue;
    }

    if (bind(server_fd, p->ai_addr, p->ai_addrlen) == -1) {
      std::cerr << "Error: bind" << std::endl;
      close(server_fd);
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  if (p == NULL) {
    std::cerr << "No se pudo hacer bind" << std::endl;
    close(server_fd);
    return 1;
  }

  if (listen(server_fd, MAX_BACKLOG) == -1) {
    std::cerr << "Error: listen" << std::endl;
    return 1;
  }

  std::cout << "Esperando conexiones..." << std::endl;

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  client_fd =
      accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

  if (client_fd == -1) {
    std::cerr << "Error: accept" << std::endl;
    return 1;
  }

  std::cout << "Conexion establecida" << std::endl;

  send_data(client_fd);

  close(client_fd);
  close(server_fd);

  return 0;
}