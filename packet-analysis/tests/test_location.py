import pytest
from unittest.mock import patch, Mock
import redis
import geoip2.errors
import ipaddress
from location import geolite_query, get_location

mock_redis = Mock()
mock_geoip2 = Mock()

@patch('location.r', mock_redis)
@patch('location.client', mock_geoip2)
def test_get_location_valid_ip():
    mock_redis.exists.return_value = False
    mock_redis.get.return_value = None
    mock_redis.set.return_value = None
    
    mock_geoip2.country.return_value.country.names.get.return_value = 'United States'
    
    result = get_location('8.8.8.8', '8.8.4.4')
    assert result == 'United States'
    mock_redis.set.assert_called_with('8.8.8.8', 'United States')

@patch('location.r', mock_redis)
@patch('location.client', mock_geoip2)
def test_get_location_private_ip():
    result = get_location('192.168.1.1', '10.0.0.1')
    assert result == 'Local'


@patch('location.r', mock_redis)
@patch('location.client', mock_geoip2)
def test_get_location_redis_error():
    mock_redis.exists.side_effect = redis.exceptions.ConnectionError('Connection error')
    
    result = get_location('8.8.8.8', '8.8.4.4')
    assert "Redis connection error" in result


@patch('location.r', mock_redis)
@patch('location.client', mock_geoip2)
def test_geolite_query_geoip2_error():
    mock_geoip2.country.side_effect = geoip2.errors.GeoIP2Error('GeoIP2 error')

    result = geolite_query('8.8.8.8')
    assert result == 'GeoIP2 error'

@patch('location.r', mock_redis)
@patch('location.client', mock_geoip2)
def test_get_location_with_cached_value():
    mock_redis.exists.return_value = True
    mock_redis.get.return_value = 'United States'
    
    result = get_location('8.8.8.8', '8.8.4.4')
    assert result == 'United States'
    mock_redis.set.assert_not_called()

