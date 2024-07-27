import os
import psycopg2
import geoip2.webservice
import ipaddress
from dotenv import load_dotenv
'''
Check if DB has a value for an IP Address and return location. 
Otherwise Query API, write to Database, and return location. 
'''
def get_location():

    ...



def geolite_query(src_ip, dst_ip):
    load_dotenv()
    id_num = os.getenv("GEOLITE_ID")
    api_key = os.getenv("GEOLITE_API_KEY")
    host = "geolite.info"

    with geoip2.webservice.Client(id_num, api_key, host) as client:
        if not ipaddress.ip_address(src_ip).is_private:
            response = client.country(src_ip)
        else:
            response = client.country(dst_ip)

        return response.country.names['en']



