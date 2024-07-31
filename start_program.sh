#!/bin/bash

echo "Starting Redis server..."
redis-server --daemonize yes
REDIS_PID=$(pgrep redis-server)

echo "Starting C++ program..."
sudo ./packet-sniffer/build/PacketSniffer &
CPP_PID=$!

echo "Starting Python program..."
python3 ./packet-analysis/main.py &
PYTHON_ID=$!

function cleanup {
    echo "Shutting down..."
    kill $CPP_PID
    kill $PYTHON_PID
    redis-cli shutdown
    exit
}

trap cleanup SIGINT SIGTERM

wait $PYTHON_PID

cleanup