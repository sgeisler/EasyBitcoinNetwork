//
// Created by sebastian on 24.09.15.
//

#ifndef EASYBITCOINNETWORKING_DEBUG_H
#define EASYBITCOINNETWORKING_DEBUG_H

#include <string>
#include <iostream>

#define DBG_INFO std::string(" (in " + std::string(__FILE__) + " at line " + std::to_string(__LINE__) + ")")
#define DBG(msg) std::cout << msg + DBG_INFO << std::endl;

#endif //EASYBITCOINNETWORKING_DEBUG_H
