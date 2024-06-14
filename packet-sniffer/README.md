# Packet Sniffer

## Overview
This is a simple packet sniffer written in C++ using the libpcap library. It captures network packets, parses them, and serializes the data to JSON format.

## Setup
### Prerequisites
- CMake
- libpcap
- JSON library (e.g., JSON for Modern C++ or JsonCpp)

### Building
```bash
mkdir build
cd build
cmake ..
make
