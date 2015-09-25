#include <iostream>
#include <unistd.h>

#include "ByteArray.h"
#include "Socket.h"

using namespace std;

int main()
{
    Socket google("google.com", 80);
    std::string snd = "GET / HTTP/1.1\r\nHost: google.com\r\n\r\n";
    google.write(ByteArray((Byte *)snd.c_str(), snd.size()));
    sleep(1);
    ByteArray ret = google.read();
    std::string retText = std::string((char *)&ret[0], ret.size());
    std::cout << retText;

    if(ret.size() == 0)
        return -1;

    return 0;
}