#include <cstring>
#include <iostream>
#include <netdb.h>
#include <unistd.h>

// Función para enviar datos al servidor
void send_data(int client_socket) {
  std::cout << "Envía tus datos al servidor. Escribe 'FIN' para finalizar."
            << std::endl;

  while (true) {
    std::string input;
    std::getline(std::cin, input);

    // Enviar los datos al servidor
    if (send(client_socket, input.c_str(), input.length(), 0) == -1) {
      std::cerr << "Error en el send" << std::endl;
      break;
    }

    // Verificar si el usuario escribió "FIN" para finalizar la conexión
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

  // Configurar los parámetros para obtener la dirección del servidor
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  // Obtener la dirección del servidor
  if ((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
    std::cerr << "Error en getaddrinfo" << gai_strerror(status) << std::endl;
    return EXIT_FAILURE;
  }

  // Intentar conectar con el servidor utilizando una de las direcciones obtenidas
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

  // Verificar si se pudo conectar con el servidor
  if (p == nullptr) {
    std::cerr << "No se pudo conectar al servidor" << std::endl;
    return EXIT_FAILURE;
  }

  // Liberar la memoria de la estructura de dirección del servidor
  freeaddrinfo(res);

  // Mostrar mensaje de conexión exitosa
  std::cout << "Conexión establecida con el servidor en " << ip << ":" << port
            << std::endl;

  // Llamar a la función para enviar datos al servidor
  send_data(client_socket);

  // Cerrar el socket de la conexión
  close(client_socket);

  return 0;
}
