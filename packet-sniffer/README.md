# Packet Sniffer

## Overview
This is a simple packet sniffer written in C++ using the libtins library. It captures network packets, parses them, serializes the data to JSON format and sends it to "Packet Analysis" using IPC.

Note: PacketSniffing on "en0" is a priveleged task on personal machine — run as sudo to avoid permission errors. 

## Setup
### Prerequisites
- CMake
- libtins (and its associated dependencies)
- JSON for Modern C++
- cpp_redis [here](https://github.com/cpp-redis/cpp_redis/wiki/Mac-&-Linux-Install) and [here](https://github.com/cpp-redis/cpp_redis/issues/105) for installation instructions

### Redis Building
```bash
mkdir external
cd external
git clone https://github.com/cpp-redis/cpp_redis.git
cd cpp_redis
git submodule init && git submodule update
cd tacopie
git fetch origin pull/5/head:cmake-fixes
git checkout cmake-fixes
cd ..
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

### Sniffer Building and Run
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
  "dst_ip":"52.216.56.58"
  "duration":0.000103,
  "flag":"ACK",
  "protocol_type":"tcp",
  "service":"https",
  "src_bytes":1500,
  "src_ip":"192.168.1.221",
  "srv_count":133,
}
```

