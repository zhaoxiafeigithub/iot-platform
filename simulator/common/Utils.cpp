//
// Created by xiafei zhao on 2026/7/1.
//


#include "Utils.h"

#include <chrono>
#include <random>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

float Utils::RandomFloat(float min, float max)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen);
}

int Utils::RandomInt(int min, int max)
{
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<int> dist(min, max);
  return dist(gen);
}

std::int64_t Utils::CurrentTimeStamp()
{
  using namespace std::chrono;

  return duration_cast<milliseconds>(
             system_clock::now().time_since_epoch())
      .count();
}

std::string Utils::GenerateMessageId() {
  static boost::uuids::random_generator gen;
  return boost::uuids::to_string(gen());
}

nlohmann::json Utils::GenerateMessage(const std::string &deviceId, const nlohmann::json &data){
  nlohmann::json payload;
  payload["data"] = data;
  payload["deviceId"] = deviceId;
  payload["timeStamp"] = CurrentTimeStamp();
  payload["messageId"] = GenerateMessageId();
  return payload;
}

