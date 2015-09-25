//
// Created by sebastian on 24.09.15.
//

#ifndef EASYBITCOINNETWORKING_SOCKET_H
#define EASYBITCOINNETWORKING_SOCKET_H

#include <string>

#include "ByteArray.h"

class Socket {

public:
    Socket(std::string addr, uint16_t port);
    Socket(int socketFd);
    ~Socket();

    int bytesAvailable();
    ByteArray read(int maxRead = 0);
    void write(ByteArray data);

    void close();

private:
    std::string addr;
    uint16_t port;
    int socketFd = -1;
};

#endif //EASYBITCOINNETWORKING_SOCKET_H
