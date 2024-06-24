# Packet Sniffer

## Overview
This is a simple packet sniffer written in C++ using the libtins library. It captures network packets, parses them, serializes the data to JSON format and writes the data to a Redis DB instance.

Note: PacketSniffing on "eth0" is a priveleged task — run as sudo to avoid permission errors. 

## Setup
### Prerequisites
- CMake
- libtins (and its associated dependencies)
- JSON for Modern C++

### Building and Run
```bash
mkdir build
cd build
cmake ../ -DLIBTINS_ENABLE_CXX11=1 
make
sudo ./PacketSniffer