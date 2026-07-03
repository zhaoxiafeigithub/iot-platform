import json
import random
import time
import requests

SERVER_URL = "http://127.0.0.1:8000/api/"

DEVICEID = "0000000000000000"


def generate_temperature():
    return round(random.uniform(20, 35), 1)


def report_temperature():
    temp = generate_temperature()
    payload = {
        'deviceId': DEVICEID,
        'temperature': temp
    }
    try:
        response = requests.post(SERVER_URL + 'report/temperature/', json=payload)
        print(response.text)
    except Exception as e:
        print(f"[ERROR] {e}")


def register_device(deviceId):
    payload = {
        'deviceId': deviceId,
    }
    try:
        response = requests.post(SERVER_URL + 'register/device/', json=payload)
        print(response.text)
    except Exception as e:
        print(f"[ERROR] {e}")



def upload_simulator():
    while True:
        report_temperature()
        time.sleep(5)





if __name__ == "__main__":
    # register_device(DEVICEID)
    upload_simulator()
    exit(0)