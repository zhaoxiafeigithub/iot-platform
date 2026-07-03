cmake_minimum_required(VERSION 3.31)
project(simulator)

set(CMAKE_CXX_STANDARD 20)

# Homebrew安装路径
set(PAHO_ROOT "/usr/local/opt/libpaho-mqtt")

include_directories(${PAHO_ROOT}/include)

link_directories(${PAHO_ROOT}/lib)

find_package(nlohmann_json REQUIRED)

add_executable(simulator main.cpp
        Device.cpp
        Device.h
        Sensor/AirSensor.cpp
        Sensor/AirSensor.h
        mqtt/MqttClient.cpp
        mqtt/MqttClient.h
        common/Topic.h
        common/Utils.cpp
        common/Utils.h
)

target_link_libraries(simulator
        paho-mqtt3as
        nlohmann_json::nlohmann_json
)
