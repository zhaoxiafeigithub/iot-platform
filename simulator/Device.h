//
// Created by xiafei zhao on 2026/6/25.
//

#ifndef SIMULATOR_DEVICE_H
#define SIMULATOR_DEVICE_H
#include <iostream>
#include <nlohmann/json.hpp>

struct HeartBeatData {
  int battery;
//  int rssi;
//  int temperature;
};


struct DeviceData {
  int battery;
  //  int rssi;
  //  int temperature;
};

class Device {

public:
  std::string name;
  std::string macAddress;
  int deviceType;
  int heartTime = 60;

protected:
  virtual void onStart() = 0;
  virtual void onStop() {}

protected:
  bool running = false;


  explicit Device(const std::string& macAddress) : macAddress(macAddress) {

  }


  virtual void registerDevice() = 0;
  virtual void reportHeartBeat() = 0;
  virtual void reportData() = 0;



  virtual ~Device()=default;




};

#endif // SIMULATOR_DEVICE_H
