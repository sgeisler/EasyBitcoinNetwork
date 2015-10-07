//
// Created by sebastian on 26.09.15.
//

#ifndef EASYBITCOINNETWORKING_MESSAGE_H
#define EASYBITCOINNETWORKING_MESSAGE_H

#include "Networks.h"

class Message
{
public:
    Message(Networks network, std::string command)
            : magic((uint32_t) network), command(command) {};

    ByteArray serialize() const;

private:
    uint32_t magic; //to identify the network (main/test)
    std::string command;
    virtual ByteArray getPayload() const = 0;
};


#endif //EASYBITCOINNETWORKING_MESSAGE_H
