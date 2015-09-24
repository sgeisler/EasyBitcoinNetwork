#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stropts.h>
#include <sys/ioctl.h>

#include "Debug.h"
#include "Socket.h"


Socket::Socket(std::string addr, uint16_t port) {
    this->addr = addr;
    this->port = port;

    sockaddr_in serverAddr;
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if(socketFd < 0)
        throw std::runtime_error("Error: can't open socket (req: " + addr + ")" + DBG_INFO);

    struct hostent *server = gethostbyname(addr.c_str());

    if(server == NULL)
        throw std::runtime_error("Error: host not found (req: " + addr + ")" + DBG_INFO);

    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    bcopy(server->h_addr,
          (char *)&serverAddr.sin_addr.s_addr,
          (size_t) server->h_length);
    serverAddr.sin_port = htons(port);

    if (connect(socketFd,(sockaddr *) &serverAddr,sizeof(serverAddr)) < 0)
        throw std::runtime_error("Error: can't connect to server (req: " + addr + ")" + DBG_INFO);
}

Socket::Socket(int socketFd) {
    if(socketFd == -1)
    {
        throw std::runtime_error("Invalid socket file descriptor" + DBG_INFO);
    }
    else
    {
        this->socketFd = socketFd;
    }
}

Socket::~Socket()
{
    this->close();
}

int Socket::bytesAvailable() {
    int bytes;
    if(ioctl(socketFd, FIONREAD, &bytes) < 0)
        throw std::runtime_error("Error: can't get bytes available to read, socket closed?");

    return bytes;
}

std::string Socket::read(int maxRead) {
    char buffer[256];
    std::string ret;
    ssize_t rd = 0;
    size_t buffSize = sizeof(buffer);

    if((maxRead == 0) || (maxRead > bytesAvailable()))
    {
        maxRead = bytesAvailable();
    }

    if(maxRead - ret.size() < sizeof(buffer))
    {
        buffSize = maxRead - ret.size();
    }

    while((rd = ::read(socketFd, buffer, buffSize)))
    {
        ret += std::string(buffer, rd);

        if(maxRead == ret.size())
            return ret;

        if(rd < 0)
            throw std::runtime_error("Error: can't read from socket, maybe closed? (req: " + addr + ")" + DBG_INFO);

        if(maxRead - ret.size() < sizeof(buffer))
        {
            buffSize = maxRead - ret.size();
        }
    }
}

void Socket::write(std::string data) {
    const char* byteArray = data.c_str();
    size_t bytesToWrite = data.size();
    ssize_t wr = 0;
    while(bytesToWrite != 0)
    {
        wr = ::write(socketFd, byteArray, bytesToWrite);

        if(wr < 0)
            throw std::runtime_error("Error: can't write to socket, maybe closed? (req: " + addr + ")" + DBG_INFO);

        bytesToWrite -= wr;
        byteArray += wr;
    }
}

void Socket::close() {
    ::close(socketFd);
}
