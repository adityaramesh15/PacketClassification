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
  "count": 1,
  "diff_srv_rate": 0,
  "duration": 0,
  "flag": "",
  "land": false,
  "protocol_type": "udp",
  "same_srv_rate": 1,
  "service": "https",
  "src_bytes": 69,
  "srv_count": 1,
  "srv_diff_host_rate": 0,
  "urgent": false,
  "wrong_fragment": false
}
```

