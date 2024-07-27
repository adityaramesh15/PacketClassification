# Packet Analysis

## Overview
This portion of the project features machine-learning for anamolous packet detection using Isolation Forests from scikit-learn written in Python. Additionally, it involves API and database queries/writes to retrieve location data from received IP addresses using GeoLite2 and PostgreSQL.

## Setup
To set up the project, ensure you use a virtual environment (venv) to manage dependencies. Follow the steps below:

```bash
cd packet-analysis
python3 -m venv .venv 
source .venv/bin/activate
pip3 install -r requirements.txt
```

## Usage
1. **Activate the virtual environment**:
    ```bash
    source .venv/bin/activate
    ```

2. **Run the packet analysis script**:
    ```bash
    python3 packet_analysis.py
    ```

3. **Deactivate the virtual environment after use**:
    ```bash
    deactivate
    ```

## Dependencies
All necessary dependencies are listed in the `requirements.txt` file. They will be installed when you run `pip install -r requirements.txt`. Also Setup GeoLite2 API Key and ID as environment variables. They can be generated [here](https://dev.maxmind.com/geoip/geolite2-free-geolocation-data).

## Key Components
- **GeoLite2**: Used for retrieving geographical location data of IP addresses.
- **PostgreSQL**: Database for storing and querying IP address location data.
- **scikit-learn**: Machine learning library for implementing the Isolation Forest model.