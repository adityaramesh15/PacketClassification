# Real-Time Network Packet Anomaly Detection

## Overview

This project is designed to detect anomalous network packets in real-time using machine learning techniques. By analyzing network traffic data, the system identifies deviations from normal patterns, which can signal potential security threats or network anomalies.

## Key Features

- **Real-Time Packet Analysis**: Continuously monitors incoming network packets using Loop Sniffing techniques.
- **Unsupervised Anomaly Detection**: Employs ensemble machine learning methods, specifically Isolation Forests, to identify unusual patterns in network traffic.
- **IP Geolocation Integration**: Interfaces with external IP-to-location databases and APIs to enhance anomaly detection by providing contextual location data.
- **JSON Data Handling**: Manages packet data in JSON format, ensuring flexible and structured data representation.

## Getting Started

### Installation

1. **Clone the Repository**  
   First, clone the repository to your local machine:

   ```bash
   git clone https://github.com/adityaramesh15/packet-anomaly-detection
   ```

2. **Set Up C++ Environment**  
   Ensure you have C++ 11 or later installed. Install the required C++ libraries:
   - **libtins**: Packet crafting and sniffing library.
   - **JSON for Modern C++**: JSON parsing and serialization library.
   - **cpp_redis**: Redis C++ client for caching.

   Ensure these libraries are included in your project's build configuration (CMake is used for this project)

3. **Set Up Python Environment**  
   Install Python 3.7 or later. Create a virtual environment and install the necessary Python libraries:

   ```bash
   # Create a virtual environment
   python3 -m venv .venv

   # Activate the virtual environment
   source .venv/bin/activate

   # Install Python dependencies
   pip3 install -r requirements.txt
   ```

4. **Configuration**  
   Make sure to configure any necessary environment variables or settings, such as API keys for external IP-to-location services. Specific about installation of each portion of the project are located in their respective `README.md` document. 

5. **Start the Program**  
   Make the startup script executable and run it:

   ```bash
   chmod +x start_program.sh
   ./start_program.sh
   ```
