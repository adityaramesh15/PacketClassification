cmake_minimum_required(VERSION 3.10)
project(PacketSniffer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories("/opt/homebrew/opt/libtins/include" "include")

find_library(TINS_LIBRARY tins)

set(SOURCES src/main.cpp src/json_serializer.cpp src/packet_sniffer.cpp)
add_executable(PacketSniffer ${SOURCES})

target_link_libraries(PacketSniffer ${TINS_LIBRARY})
