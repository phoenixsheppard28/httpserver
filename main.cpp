#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <cerrno>
#include <cstring>
#include <string>
#include <limits.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <thread>
#include "helpers.h"
#include <time.h>

using namespace std;


int main(){
    std::thread t1(thread_func,20);
    std::thread t2(thread_func,10);
    t1.join();
    t2.join();
}


void thread_func(int arg1){
    sleep(1);
    cout << "Hello! " << arg1 << "\n";
}

