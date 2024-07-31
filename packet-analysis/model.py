import pandas as pd
import numpy as np
import joblib
from location import get_location
from sklearn.ensemble import IsolationForest
from sklearn.preprocessing import OneHotEncoder, StandardScaler

class AnomalyDetector:
    def __init__(self):
        self.encoder = OneHotEncoder(handle_unknown='ignore', sparse_output = False)
        self.scaler = StandardScaler()
        self.iforest = IsolationForest(n_estimators=100, max_samples='auto')
        self.fitted = False

    def preprocess(self, data, fit):
        data['location'] = data.apply(lambda row: get_location(row['src_ip'], row['dst_ip']), axis=1)
        data.drop(columns=['dst_ip', 'src_ip', 'count', 'srv_count'], inplace=True)
        data.dropna(inplace=True)

        if fit:
            data_encoded = self.encoder.fit_transform(data[['flag', 'protocol_type', 'service', 'location']])
            data_scaled = self.scaler.fit_transform(data[['duration', 'src_bytes']])
        else:
            data_encoded = self.encoder.transform(data[['flag', 'protocol_type', 'service', 'location']])
            data_scaled = self.scaler.transform(data[['duration', 'src_bytes']])

        return np.concatenate([data_encoded, data_scaled], axis=1)

    def train(self, data):
        processed_data = self.preprocess(data, fit=True)
        self.iforest.fit(processed_data)
        self.fitted = True

    def save_model(self, filepath):
        joblib.dump((self.encoder, self.scaler, self.iforest), filepath)
        
    def load_model(self, filepath):
        self.encoder, self.scaler, self.iforest = joblib.load(filepath)
        self.fitted = True
    
    def predict(self, data):
        if not self.fitted:
            raise Exception("Model not fitted. Load a trained model or train it first.")
        data_preprocessed = self.preprocess(data, fit=False)
        return self.iforest.predict(data_preprocessed)
