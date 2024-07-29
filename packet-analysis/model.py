import pandas as pd
import numpy as np
import joblib
from location import get_location
from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.pipeline import Pipeline

class AnomalyDetector:
    def __init__(self):
        self.encoder = OneHotEncoder(handle_unknown='ignore')
        self.scaler = StandardScaler()
        self.iforest = IsolationForest(n_estimators=100, max_samples='auto')
        self.model = None

    def preprocess(self, data):
        data['location'] = data.apply(lambda row: get_location(row['src_ip'], row['dst_ip']), axis=1)

        data.drop(columns=['dst_ip', 'src_ip', 'count', 'srv_count'], inplace=True)
        data.dropna(inplace=True)

        encoded_data = self.encoder.fit_transform(data[['flag', 'protocol_type', 'service', 'location']]).toarray()
        scaled_data = self.scaler.fit_transform(data[['duration', 'src_bytes']])

        return np.concatenate([encoded_data, scaled_data], axis=1)
    
    def train(self, dpi_data, home_data, cafe_data):
        data = pd.concat([dpi_data, home_data, cafe_data], ignore_index=True)
        processed_data = self.preprocess(data)
        self.iforest.fit(processed_data)
        self.model = Pipeline([('encoder', self.encoder),('scaler', self.scaler),('iforest', self.iforest)])

    def save_model(self, filepath):
        joblib.dump(self.model, filepath)
        
    def load_model(self, filepath):
        self.model = joblib.load(filepath)
    
    def predict(self, data):
        data_preprocessed = self.preprocess(data)
        return self.iforest.predict(data_preprocessed)