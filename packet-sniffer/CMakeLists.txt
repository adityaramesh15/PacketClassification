cmake_minimum_required(VERSION 3.10)
project(PacketSniffer)

set(CMAKE_CXX_STANDARD 11)

# Manually specify PCAP paths
set(PCAP_INCLUDE_DIRS /opt/homebrew/Cellar/libpcap/1.10.4/include)
set(PCAP_LIBRARIES /opt/homebrew/Cellar/libpcap/1.10.4/lib/libpcap.dylib)

include_directories(${PCAP_INCLUDE_DIRS})

set(SOURCES src/main.cpp src/json_serializer.cpp src/packet_sniffer.cpp src/packet_parser.cpp)

add_executable(PacketSniffer ${SOURCES})
target_link_libraries(PacketSniffer ${PCAP_LIBRARIES})
