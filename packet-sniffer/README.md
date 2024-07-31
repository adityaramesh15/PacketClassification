# Packet Sniffer

## Overview
The Packet Sniffer is a C++ application that captures network packets using the [libtins](https://libtins.github.io/) library. It parses the captured packets, serializes the data into JSON format, and sends the serialized data to the "Packet Analysis" component using Inter-Process Communication (IPC) with Redis.

**Note**: Packet sniffing on the "en0" interface requires elevated privileges on most personal machines. To avoid permission errors, run the application with `sudo`.

## Setup

### Prerequisites
- **CMake**: For building the project.
- **libtins**: Library for packet sniffing and crafting.
- **JSON for Modern C++**: For JSON serialization.
- **cpp_redis**: A Redis C++ client library.

For installation instructions for cpp_redis, refer to the [official documentation](https://github.com/cpp-redis/cpp_redis/wiki/Mac-&-Linux-Install) and [issue discussion](https://github.com/cpp-redis/cpp_redis/issues/105).

### Building cpp_redis

To build cpp_redis, follow these steps:

```bash
# Create a directory for external dependencies
mkdir external
cd external

# Clone the cpp_redis repository
git clone https://github.com/cpp-redis/cpp_redis.git
cd cpp_redis

# Initialize and update submodules
git submodule init && git submodule update

# Fetch and checkout necessary branches for tacopie
cd tacopie
git fetch origin pull/5/head:cmake-fixes
git checkout cmake-fixes
cd ..

# Build and install cpp_redis
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

### Building and Running the Sniffer

To build and run the Packet Sniffer alone:

```bash
# Create a build directory and navigate into it
mkdir build
cd build

# Generate the build files and compile the project
cmake ../ -DLIBTINS_ENABLE_CXX11=1
make

# Start the Redis server (make sure Redis is installed on your system)
redis-server 

# Run the Packet Sniffer with elevated privileges
sudo ./PacketSniffer
```

## Example Output

The Packet Sniffer outputs JSON-formatted data for each captured packet. An example output is shown below:

```json
{
  "count": 133,
  "dst_ip": "52.216.56.58",
  "duration": 0.000103,
  "flag": "ACK",
  "protocol_type": "tcp",
  "service": "https",
  "src_bytes": 1500,
  "src_ip": "192.168.1.221",
  "srv_count": 133
}
```