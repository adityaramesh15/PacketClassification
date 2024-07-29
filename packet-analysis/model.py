import pandas as pd
import numpy as np
from location import get_location
from sklearn.ensemble import IsolationForest


dpi_data = pd.read_json("../data/dpi-data.json")
home_data = pd.read_json("../data/home-data.json")
cafe_data = pd.read_json("../data/cafe-data.json")

dpi_data['location'] = dpi_data.apply(lambda row: get_location(row['src_ip'], row['dst_ip']), axis = 1)
home_data['location'] = home_data.apply(lambda row: get_location(row['src_ip'], row['dst_ip']), axis = 1)
cafe_data['location'] = cafe_data.apply(lambda row: get_location(row['src_ip'], row['dst_ip']), axis = 1)

