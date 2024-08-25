# Packet Analysis

## Overview
This portion of the project features machine learning for anomalous packet detection using Isolation Forests from scikit-learn written in Python. Additionally, it involves a hybridized caching solution for retrieving location data for IP addresses using the GeoLite2 API and database queries/writes from Redis.

## Setup
To set up the project as a *standalone* portion, ensure you use a virtual environment (venv) to manage dependencies. This is assuming you are using this project without the packet-sniffer portion. Follow the steps below:

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

2. **Start the Redis server**:
    ```bash
    redis-server
    ```

3. **Run the packet analysis script**:
    ```bash
    python3 main.py
    ```

4. **Stop the Redis server** (after you are done using it):
    ```bash
    redis-cli shutdown
    ```

5. **Deactivate the virtual environment after use**:
    ```bash
    deactivate
    ```

## Dependencies
All necessary dependencies are listed in the `requirements.txt` file. They will be installed when you run `pip install -r requirements.txt`. In addition, Redis must be installed, as well as GeoLite2 API Key and ID as environment variables, which can be generated [here](https://dev.maxmind.com/geoip/geolite2-free-geolocation-data).

## Key Components

- **GeoLite2**: Used for retrieving geographical location data of IP addresses.
- **Redis**: In-memory data structure store, used for caching IP address location data for fast retrieval.
- **scikit-learn**: Machine learning library for implementing the Isolation Forest model.

## Interpretation

The model's prediction can be used to return a decision score, which indicates how isolated a data point is. The output of this function generally ranges from -1 to 1:

- **Positive values (close to 1)**: These indicate that the data point is less likely to be an anomaly. The closer the score is to 1, the more "normal" the data point is considered, as it is well-integrated with other data points in the training set.
- **Negative values (close to -1)**: These indicate that the data point is more likely to be an anomaly. The closer the score is to -1, the more "anomalous" the data point is considered, as it is isolated from other data points in the training set.

## Tests

You can run these tests with the following commands:

```bash
export PYTHONPATH="${PYTHONPATH}:/Users/adityaramesh/Desktop/CS/Projects/packet-anomaly-detection/packet-analysis"
python3 -m pytest packet-analysis/tests
```

Make sure to replace `test_name.py` with the filename of the specific test case you want to run. 

## Environment Variables

To run the packet analysis portion effectively, you will need to set up environment variables for the GeoLite2 API. Create a `.env` file in the packet-analysis directory of the project with the following variables:

```plaintext
# GeoLite2 API Configuration
GEOLITE_ID=your_geolite_id
GEOLITE_API_KEY=your_geolite_api_key
OLD_GEOLITE_API_KEY=your_old_geolite_api_key
```

Replace the placeholders (`your_geolite_id`, `your_geolite_api_key`, `your_old_geolite_api_key`) with your actual GeoLite2 credentials.

**Note:** Ensure that your `.env` file is included in your `.gitignore` file to prevent sensitive information from being committed to your version control system.