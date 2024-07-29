import os
import redis
import geoip2.webservice
import ipaddress
from dotenv import load_dotenv


load_dotenv()
r = redis.Redis(host='localhost', port=6379, decode_responses=True)

id_num = os.getenv("GEOLITE_ID")
api_key = os.getenv("GEOLITE_API_KEY")
host = "geolite.info"

client = geoip2.webservice.Client(id_num, api_key, host)

def get_location(src_ip, dst_ip):
    try:
        if not ipaddress.ip_address(src_ip).is_private:
            if not r.exists(src_ip):
                r.set(src_ip, geolite_query(src_ip))
            return r.get(src_ip)
        elif not ipaddress.ip_address(dst_ip).is_private:
            if not r.exists(dst_ip):
                r.set(dst_ip, geolite_query(dst_ip))
            return r.get(dst_ip)
        else:
            return "Local"
        
    except redis.exceptions.ConnectionError as e:
        return f"Redis connection error: {e}"


def geolite_query(ip):
    try:
        response = client.country(ip)
        return str(response.country.names.get('en'))
    except geoip2.errors.GeoIP2Error as e:
        return str(e)
