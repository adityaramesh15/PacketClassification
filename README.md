# Real-Time Network Packet Anomaly Detection

## Overview

This project focuses on the real-time detection of anomalous network packets using machine learning (ML). It involves processing and analyzing network packet data to identify deviations from typical patterns, which could indicate potential security threats or network issues.

## Notable Features

- **Real-time Packet Analysis**: Continuously collects and monitors incoming network packets through Loop Sniffing.
- **Unsupervised Anomaly Detection**: Utilizes ensemble machine learning to detect unusual patterns in network traffic with Isolation Forests.
- **API/DB Location Requesting**: Works with external IP to Location Databases and APIs for extended anomaly detection. 
- **JSON Data Handling**: Processes packet data in JSON format, allowing for flexible and structured data representation.

## Getting Started

### Prerequisites

- C++ 11 or later
- Python 3.7 or later
- `libtins` library for packet manipulation

- `JSON for Modern C++` for serialization
- `pandas` for data manipulation and formatting
- `numpy` for data preprocessing and model formulation
- `scikit-learn` for IsolationForest model training and prediction
- `redis` for Redis DB writes and retrieval
- `geoip2` for GeoLite2 API Data requests
- `ipaddress` for IP processing functionality
- `python-dotenv` to load to API environment variables

### Installation





