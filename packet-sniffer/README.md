# Packet Sniffer

## Overview
This is a simple packet sniffer written in C++ using the libtins library. It captures network packets, parses them, serializes the data to JSON format and sends it to "Packet Analysis" using IPC.

Note: PacketSniffing on "eth0" is a priveleged task on personal machine — run as sudo to avoid permission errors. 

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
```

## Example Ouput
```bash
{
  "count":133,
  "duration":0.000103,
  "flag":"ACK",
  "land":false,
  "protocol_type":"tcp",
  "service":"https",
  "src_bytes":1500,
  "srv_count":133,
  "urgent":false,
  "wrong_fragment":false
}
```

