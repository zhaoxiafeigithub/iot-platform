import json
import paho.mqtt.client as mqtt


class MQTTClient:
    def __init__(self):
        self.client = mqtt.Client(mqtt.CallbackAPIVersion)
        self.client.on_message = self.on_message
        self.client.on_connect = self.on_connect

    def on_connect(self, client, userdata, flags, rc):
        print("Connected with result code "+str(rc))
        client.subscribe("device/report")

    def on_message(self, client, userdata, msg):
        print(msg.topic+" "+str(msg.payload))

