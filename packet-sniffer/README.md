# Packet Sniffer

## Overview
This is a simple packet sniffer written in C++ using the libtins library. It captures network packets, parses them, and serializes the data to JSON format.

## Setup
### Prerequisites
- CMake
- libtins (and its associated dependencies)
- JSON for Modern C++

### Building
```bash
mkdir build
cd build
cmake ../ -DLIBTINS_ENABLE_CXX11=1 
make
