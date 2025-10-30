#include <iostream>
#include <cstring>        // memset, etc.
#include <iostream>       // for printing/logging
#include <cstring>
#include <string>
#include <thread>
#include <sys/socket.h>   // main socket functions
#include <netinet/in.h>   // sockaddr_in structure (for IP addresses)
#include <arpa/inet.h>    // inet_pton / inet_ntop helpers
#include <unistd.h>       // close() function
#include <time.h>
#include "helpers.h"

using namespace std;


int main(){
    
    std::thread t1(thread_func,20);
    std::thread t2(thread_func,10);
    t1.join();
    t2.join();
}


void thread_func(int arg1){
    cout << "Hello! " << arg1 << "\n";
}

