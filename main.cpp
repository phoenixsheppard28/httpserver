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
#include <thread>
#include <time.h>
#include <unistd.h> // close() function

using namespace std;

int sock;

void thread_func(int arg1) { cout << "Hello! " << arg1 << "\n"; }

// std::thread t1(thread_func,20);
// std::thread t2(thread_func,10);
// t1.join();
// t2.join();

void cleanup(void) {
  cout << "Cleaning up socket " << sock;

  shutdown(sock, SHUT_RDWR);
  close(sock);
}

void handle_sigint(int signum) {
  cout << "\nCaught SIGINT (" << signum << ")" << endl;
  exit(0); // ensure atexit handlers and normal shutdown run
}

int main() {
  sock = socket(AF_INET, SOCK_STREAM, 0);
  atexit(cleanup);
  signal(SIGINT, handle_sigint);

  while (true) {
  }
}