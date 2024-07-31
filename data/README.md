# Datasets

## Overview
This repository contains datasets of network traffic captured using the PacketSniffer tool. The dataset includes 5,000 packets, each represented by the following features:

1. **Count**: The sequential number of the packet.
2. **Destination IP**: The IP address of the packet's destination.
3. **Duration**: The time duration for which the packet was observed.
4. **Flag**: Flags indicating the status or behavior of the packet.
5. **Protocol Type**: The type of protocol used (e.g., TCP, UDP).
6. **Service**: The service associated with the packet (e.g., HTTP, DNS).
7. **Source IP**: The IP address of the packet's origin.
8. **Service Count**: The number of services accessed during the capture period.

## Considerations
To enhance the dataset's accuracy and relevance, consider capturing packet dumps that reflect a more typical representation of your network environment. The data should be formatted as a collection of JSON objects, with each object corresponding to a single packet.
