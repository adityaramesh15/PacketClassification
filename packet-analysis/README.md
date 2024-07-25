# Packet Analysis

## Overview
This project involves API and database queries/writes to retrieve location data from received IP addresses using GeoLite2 and PostgreSQL. Additionally, it features a machine learning model written in Python using the scikit-learn library. The model analyzes network packets and detects anomalies using ensemble Isolation Forests.

## Setup
To set up the project, ensure you use a virtual environment (venv) to manage dependencies. Follow the steps below:

```bash
python3 -m venv venv 
source venv/bin/activate
pip install -r requirements.txt
```

## Usage
1. **Activate the virtual environment**:
    ```bash
    source venv/bin/activate
    ```

2. **Run the packet analysis script**:
    ```bash
    python packet_analysis.py
    ```

3. **Deactivate the virtual environment after use**:
    ```bash
    deactivate
    ```

## Dependencies
All necessary dependencies are listed in the `requirements.txt` file. They will be installed when you run `pip install -r requirements.txt`.

## Key Components
- **GeoLite2**: Used for retrieving geographical location data of IP addresses.
- **PostgreSQL**: Database for storing and querying IP address location data.
- **scikit-learn**: Machine learning library for implementing the Isolation Forest model.