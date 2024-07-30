import pandas as pd
from model import AnomalyDetector
import redis
import json

detector = AnomalyDetector()

dpi_data = pd.read_json("../data/dpi-data.json")
home_data = pd.read_json("../data/home-data.json")
cafe_data = pd.read_json("../data/cafe-data.json")
data = pd.concat([dpi_data, home_data, cafe_data], ignore_index=True)

detector.train(data)
detector.save_model("anomaly_detector.pkl")


detector.load_model("anomaly_detector.pkl")

r = redis.Redis(host='localhost', port=6379, decode_responses=True)
while True:
    raw_packet = r.blpop('packet_list', 0)[1]
    if raw_packet != '{}':
        json_packet = json.loads(raw_packet)
        data = pd.DataFrame([json_packet])
        print(detector.predict(data))
    