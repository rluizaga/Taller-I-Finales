/*
Escriba un programa que reciba por linea de comandos un Puerto. El programa debe
escuchar en el puerto indicado a la espera de una unica conexion por donde
recibira paquetes de la forma [largo] [largo]... (es decir 2 bytes al principio
que indican, en litle endian, el largo del paquete) y los imprima por stdout.
Cuando se reciba un paquete 0000 se debe finalizar ordenadamente.
*/

#include <cstring>
#include <iostream>
#include <netdb.h>
#include <stdint.h>
#include <unistd.h>

void recv_data(int client_fd) {
  int16_t len;
  char buffer[1024];

  while (recv(client_fd, &len, sizeof(len), 0) > 0) {
    std::cout << len << std::endl;

    recv(client_fd, buffer, len, 0);
    buffer[len] = '\0';
    std::cout << buffer << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Error: debe indicar el puerto a usar" << std::endl;
    return 1;
  }

  char *ip = argv[1];
  char *port = argv[2];

  struct addrinfo hints, *res, *p;
  int status, client_fd, server_fd;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo(ip, port, &hints, &res);

  if (status != 0) {
    std::cerr << "Error: getaddrinfo: " << gai_strerror(status) << std::endl;
    return 1;
  }

  for (p = res; p != NULL; p = p->ai_next) {
    server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (server_fd < 0) {
      continue;
    }

    if (bind(server_fd, p->ai_addr, p->ai_addrlen) < 0) {
      close(server_fd);
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  if (p == NULL) {
    std::cerr << "Error: no se pudo crear el socket" << std::endl;
    return 1;
  }

  if (listen(server_fd, 1) < 0) {
    std::cerr << "Error en listen" << std::endl;
    return 1;
  }

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                          &client_addr_len)) < 0) {
    std::cerr << "Error en accept" << std::endl;
    return 1;
  }

  std::cout << "Conexion establecida" << std::endl;

  recv_data(client_fd);

  close(client_fd);
  close(server_fd);

  return 0;
}