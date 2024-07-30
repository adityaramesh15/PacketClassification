cmake_minimum_required(VERSION 3.10)
project(PacketSniffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories("/opt/homebrew/opt/libtins/include" "include" "/opt/homebrew/Cellar/nlohmann-json/3.11.3/include")

find_library(TINS_LIBRARY tins)

set(SOURCES src/main.cpp src/packet_sniffer.cpp src/packet_parser.cpp)
add_executable(PacketSniffer ${SOURCES})

target_link_libraries(PacketSniffer ${TINS_LIBRARY})

add_subdirectory(external/cpp_redis)
target_link_libraries(PacketSniffer SYSTEM cpp_redis tacopie)