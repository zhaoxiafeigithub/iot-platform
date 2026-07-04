#include <iostream>
#include "mqtt/MqttClient.h"
#include "Sensor/AirSensor.h"
#include <thread>
int main() {

    AirSensor sensor("AA:BB:CC:DD");
    sensor.registerDevice();

    while (true)
    {
      sensor.reportData();
      std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    return 0;
}









