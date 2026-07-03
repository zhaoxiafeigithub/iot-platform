//
// Created by xiafei zhao on 2026/7/1.
//

#pragma once

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>

namespace Utils
{
float RandomFloat(float min, float max);

int RandomInt(int min, int max);



std::string GenerateMessageId();

std::int64_t CurrentTimeStamp();


nlohmann::json GenerateMessage(const std::string &deviceId, const nlohmann::json &data);


}



