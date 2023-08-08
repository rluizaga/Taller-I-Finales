/*
Escriba un programa que reciba por línea de comandos un Puerto y una IP. El
programa debe establecer una unica conexión, quedar en escucha e imprimir en
stdout todo lo recibido. Al recibir el texto ‘FINAL’ debe finalizar el programa
sin imprimir dicho texto.
*/

#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

#define MAX_BACKLOG 1

void received_data(int client_socket) {
  char buffer[1024];
  int bytes_received;

  while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
    if (strcmp(buffer, "FINAL") == 0) {
      break;
    }
    std::cout << buffer << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    std::cerr << "Uso:" << argv[0] << " <ip> <puerto>" << std::endl;
    return 1;
  }

  const char *ip = argv[1];
  const char *port = argv[2];

  // Configuracion de los parametros para getaddrinfo
  struct addrinfo hints, *res, *p;
  int status, server_socket, client_socket;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  // Obtencion de la informacion de la direccion
  status = getaddrinfo(ip, port, &hints, &res);
  if (status != 0) {
    std::cerr << "Error al obtener la informacion de la direccion" << std::endl;
    return 1;
  }

  // Recorrer la lista de direcciones obtenidas
  for (p = res; p != NULL; p = p->ai_next) {
    // Crear el socket
    server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (server_socket < 0) {
      std::cerr << "Error al crear el socket" << std::endl;
      continue;
    }

    // Asociar el socket al puerto
    if (bind(server_socket, p->ai_addr, p->ai_addrlen) < 0) {
      close(server_socket);
      std::cerr << "Error al asociar el socket al puerto" << std::endl;
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  if (p == NULL) {
    std::cerr << "Error al hacer bind" << std::endl;
    return 1;
  }

  // Configurar el socket para escuchar conexiones entrantes
  if (listen(server_socket, MAX_BACKLOG) < 0) {
    std::cerr << "Error al hacer listen" << std::endl;
    return 1;
  }

  struct sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);

  // Aceptar conexiones entrante
  client_socket = accept(server_socket, (struct sockaddr *)&client_address,
                         &client_address_len);

  if (client_socket == -1) {
    std::cerr << "Error al aceptar la conexion" << std::endl;
    close(server_socket);
    return 1;
  }

  std::cout << "Cliente conectado" << std::endl;

  received_data(client_socket);

  close(client_socket);
  close(server_socket);
}