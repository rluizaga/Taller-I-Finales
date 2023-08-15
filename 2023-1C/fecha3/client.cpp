#include <cstring>
#include <iostream>
#include <netdb.h>
#include <stdint.h>
#include <unistd.h>

void send_data(int sockfd) {
  char data[100] = "Hola mundo";
  int16_t len = strlen(data);

  if (send(sockfd, &len, sizeof(len), 0) == -1) {
    std::cout << "Error: could not send length" << std::endl;
    return;
  }

  std::cout<<"len: "<<len<<std::endl;

  if (send(sockfd, data, len, 0) == -1) {
    std::cout << "Error: could not send data" << std::endl;
    return;
  }

  char data1[100] = "Hola mundo como estas?";
  int16_t len1 = strlen(data1);

  if (send(sockfd, &len1, sizeof(len1), 0) == -1) {
    std::cout << "Error: could not send length" << std::endl;
    return;
  }

  std::cout<<"len: "<<len1<<std::endl;

  if (send(sockfd, data1, len1, 0) == -1) {
    std::cout << "Error: could not send data" << std::endl;
    return;
  }
}

int main(int argc, char *argv[]) {
  // Se recive ip  y port por consola
  if (argc != 3) {
    std::cout << "Usage: ./server <ip> <port>" << std::endl;
    return 1;
  }

  char *ip = argv[1];
  char *port = argv[2];

  struct addrinfo hints, *res, *p;
  int status, sockfd;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  status = getaddrinfo(ip, port, &hints, &res);

  if (status != 0) {
    std::cout << "Error: " << gai_strerror(status) << std::endl;
    return 1;
  }

  for (p = res; p != NULL; p = p->ai_next) {
    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sockfd == -1) {
      continue;
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      continue;
    }

    break;
  }

  freeaddrinfo(res);

  if (p == NULL) {
    std::cout << "Error: could not connect" << std::endl;
    return 1;
  }

  std::cout << "Conectado" << std::endl;

  send_data(sockfd);

  close(sockfd);
  return 0;
}