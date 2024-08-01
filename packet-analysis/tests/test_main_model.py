import pytest
from unittest.mock import patch, Mock, MagicMock
import pandas as pd
import redis
import json
from model import AnomalyDetector
import location  

# Sample data for testing
sample_data = {
    "timestamp": ["2024-07-01T00:00!p:00Z"],
    "src_ip": ["192.168.1.1"],
    "dst_ip": ["8.8.8.8"],
    "src_port": [12345],
    "dst_port": [80],
    "protocol": ["TCP"],
    "payload_size": [500],
}

sample_df = pd.DataFrame(sample_data)
mock_redis = Mock()
mock_detector = MagicMock(spec=AnomalyDetector)


@patch('main.r', mock_redis)
@patch('main.detector', mock_detector)
def test_training_and_saving_model():
    mock_detector.train.return_value = None
    mock_detector.save_model.return_value = None

    data = pd.concat([sample_df, sample_df, sample_df], ignore_index=True)
    mock_detector.train(data)
    mock_detector.save_model("./packet-analysis/anomaly_detector.pkl")

    mock_detector.train.assert_called_once_with(data)
    mock_detector.save_model.assert_called_once_with("./packet-analysis/anomaly_detector.pkl")


@patch('main.r', mock_redis)
@patch('main.detector', mock_detector)
def test_loading_model():
    mock_detector.load_model.return_value = None
    mock_detector.load_model("./packet-analysis/anomaly_detector.pkl")

    mock_detector.load_model.assert_called_once_with("./packet-analysis/anomaly_detector.pkl")


@patch('main.r', mock_redis)
@patch('main.detector', mock_detector)
def test_predict():
    mock_detector.predict.return_value = ["Normal"]

    data = pd.DataFrame([sample_data])
    result = mock_detector.predict(data)

    mock_detector.predict.assert_called_once_with(data)
    assert result == ["Normal"]


@patch('main.r', mock_redis)
@patch('main.detector', mock_detector)
def test_redis_packet_processing():
    mock_packet = json.dumps(sample_data)
    mock_redis.blpop.return_value = ('packet_list', mock_packet)

    mock_detector.predict.return_value = ["Normal"]

    raw_packet = mock_redis.blpop('packet_list', 0)[1]
    json_packet = json.loads(raw_packet)
    data = pd.DataFrame([json_packet])
    result = mock_detector.predict(data)

    mock_redis.blpop.assert_called_once_with('packet_list', 0)
    mock_detector.predict.assert_called_once_with(data)
    assert result == ["Normal"]