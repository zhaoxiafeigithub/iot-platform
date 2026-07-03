//
// Created by xiafei zhao on 2026/6/25.
//

#ifndef SIMULATOR_AIRSENSOR_H
#define SIMULATOR_AIRSENSOR_H
#include "../Device.h"
#include "../mqtt/MqttClient.h"
#include "../common/Utils.h"
#include "../common/Topic.h"

class AirSensor : public Device
{
public:
  MqttClient client;

  explicit AirSensor(const std::string & mac) : Device(mac) {
    name = "传感器";
    deviceType = 10;
  }


  void onStart() override {
    client.init("tcp://127.0.0.1:1883", "test_airsensor");
    client.connect();
    client.subscribe(Topics::Command);

  }


  void registerDevice() override
  {
    client.init("tcp://127.0.0.1:1883", "test_airsensor");
    client.connect();
    //订阅
    client.subscribe(Topics::Command);
    client.setMessageHandler([this](const std::string &topic, const std::string &payload) {
      std::cout << topic << std::endl;
      std::cout << payload << std::endl;
    });
  }

  void reportData() override
  {
    nlohmann::json data;
    data["deviceId"] = this->macAddress;
    data["temperature"] = Utils::RandomFloat(17.0f, 35.0f);
    nlohmann::json message = Utils::GenerateMessage(this->macAddress, data);
    this->client.publish(Topics::Report, to_string(message));
  }
  void reportHeartBeat() override
  {

  }




};

#endif // SIMULATOR_AIRSENSOR_H
