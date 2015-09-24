cmake_minimum_required(VERSION 2.8.1)

project(EasyBitcoinNetworking)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./include)

file(GLOB SOURCE_FILES
        "*.cpp"
)

add_library(EasyBitcoinNetworking ${SOURCE_FILES})
add_executable(EasyBitcoinNetworkingTests ${SOURCE_FILES} ./testing/main.cpp)