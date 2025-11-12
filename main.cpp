#include "helpers.h"
#include <arpa/inet.h> // inet_pton / inet_ntop helpers
#include <cstring>     // memset, etc.
#include <cstring>
#include <iostream>
#include <iostream>     // for printing/logging
#include <netinet/in.h> // sockaddr_in structure (for IP addresses)
#include <stdlib.h>
#include <string>
#include <sys/socket.h> // main socket functions
#include <sys/types.h>
#include <thread>
#include <time.h>
#include <unistd.h> // close() function

int sock = -1;

void thread_func(int arg1) { std::cout << "Hello! " << arg1 << "\n"; }

// std::thread t1(thread_func,20);
// std::thread t2(thread_func,10);
// t1.join();
// t2.join();

void cleanup(void) {
  std::string msg = sock != -1 ? "Cleaning up socket " + std::to_string(sock)
                               : "No socket ever connected";
  std::cout << msg << "\n";

  shutdown(sock, SHUT_RDWR);
  close(sock);
}

void handle_sigint(int signum) {
  std::cout << "\nCaught SIGINT (" << signum << ")" << std::endl;
  exit(0); // ensure atexit handlers and normal shutdown run
}

int main() {
  atexit(cleanup);
  signal(SIGINT, handle_sigint);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cout << "Error opening socket" << std::endl;
    exit(1);
  }

  sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8000);
  serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

  socklen_t addrLen = sizeof(serverAddress);

  if (bind(sock, (struct sockaddr *)&serverAddress, addrLen) == -1) {
    std::cout << "Error binding socket" << std::endl;
    exit(1);
  }

  if (listen(sock, 8000) == -1) {
    std::cout << "Error listening to port" << std::endl;
    return 1;
  }

  while (true) {
    int client_sock = accept(sock, (struct sockaddr *)&serverAddress, &addrLen);
    if (client_sock == -1) {
      std::cout << "Error accepting connection" << std::endl;
      return 1;
    }
    std::cout << "HI";
  }
}