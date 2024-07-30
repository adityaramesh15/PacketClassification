import pandas as pd
from model import AnomalyDetector

detector = AnomalyDetector()

dpi_data = pd.read_json("../data/dpi-data.json")
home_data = pd.read_json("../data/home-data.json")
cafe_data = pd.read_json("../data/cafe-data.json")
data = pd.concat([dpi_data, home_data, cafe_data], ignore_index=True)

detector.train(data)
detector.save_model("anomaly_detector.pkl")


detector.load_model("anomaly_detector.pkl")
new_data = pd.read_json('../data/mixed-anomaly.json')
predictions = detector.predict(new_data)
print(predictions)
