#include <iostream>
#include <unistd.h>

#include "Socket.h"

using namespace std;

int main()
{
    Socket google("google.com", 80);
    google.write("GET / HTTP/1.1\r\nHost: google.com\r\n\r\n");
    sleep(1);
    std::string ret = google.read();
    std::cout << ret;

    if(ret.size() == 0)
        return -1;

    return 0;
}