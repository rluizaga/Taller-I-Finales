#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

#define MAX_BACKLOG 1

void received_data(int client_socket) {
  char buffer[1024];
  int bytes_received;

  while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) >
         0) {
    buffer[bytes_received] = '\0'; // Agregar el terminador de cadena
    if (strcmp(buffer, "FIN") == 0) {
      break; // Finalizar el bucle si se recibe 'FIN'
    }
    std::cout << buffer << std::endl;
  }

  if (bytes_received == -1) {
    std::cerr << "Error en recv: " << strerror(errno) << std::endl;
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
  int status, server_socket, client_socket;

  // Configuración de los parámetros para getaddrinfo
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;       // Utilizar IPv4
  hints.ai_socktype = SOCK_STREAM; // Tipo de socket TCP

  // Obtener información de direcciones para el servidor
  if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
    std::cerr << "Error en getaddrinfo: " << gai_strerror(status) << std::endl;
    return EXIT_FAILURE;
  }

  // Recorrer la lista de resultados de direcciones hasta encontrar una
  // disponible
  for (p = res; res != nullptr; p = p->ai_next) {
    // Crear el socket para el servidor
    if ((server_socket =
             socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      std::cerr << "Error en el socket: " << strerror(errno) << std::endl;
      continue;
    }

    // Asociar el socket a la dirección y el puerto
    if (bind(server_socket, p->ai_addr, p->ai_addrlen) == -1) {
      close(server_socket); // Cerrar el socket antes de continuar
      std::cerr << "Error en el bind: " << strerror(errno) << std::endl;
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  // Si no se encontró una dirección disponible, mostrar un mensaje de error
  if (p == nullptr) {
    std::cerr << "No se pudo hacer el bind" << std::endl;
    return EXIT_FAILURE;
  }

  // Configurar el socket para escuchar conexiones entrantes
  if (listen(server_socket, MAX_BACKLOG) == -1) {
    std::cerr << "Error en listen: " << strerror(errno) << std::endl;
    return EXIT_FAILURE;
  }

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  // Aceptar la conexión entrante del cliente
  client_socket =
      accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

  // Si hay un error en la conexión, mostrar un mensaje de error y cerrar el
  // socket del servidor
  if (client_socket == -1) {
    std::cerr << "Error en accept: " << strerror(errno) << std::endl;
    close(server_socket);
    return EXIT_FAILURE;
  }

  printf("Cliente conectado\n");

  // Procesar los datos recibidos del cliente hasta recibir 'FIN'
  received_data(client_socket);

  // Cerrar los sockets del cliente y del servidor antes de finalizar el
  // programa
  close(client_socket);
  close(server_socket);

  return 0;
}