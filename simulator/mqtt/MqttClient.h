//
// Created by xiafei zhao on 2026/6/25.
//

#ifndef SIMULATOR_MQTTCLIENT_H
#define SIMULATOR_MQTTCLIENT_H
#include "iostream"
#include <MQTTAsync.h>

class MqttClient {
public:
  using MessageHandler = std::function<void(const std::string &topic, const std::string &payload)>;

  MessageHandler messageHandler;


  std::unordered_map<std::string, int> topicMap;


public:
  bool init(const std::string &serverURL, const std::string &clientId);

  bool connect();
  void disconnect();

  bool publish(const std::string& topic, const std::string & payload);

  bool subscribe(const std::string& topic);
  ~MqttClient();


  void setMessageHandler(MessageHandler handler);


  static void onConnectSuccess(void *context, MQTTAsync_successData *response);


private:

  static void onConnectionLost(void* context, char* cause);

  static int onMessageArrived(void* context, char* topicName,int topicLen, MQTTAsync_message* message);

  static void onDeliveryComplete(void* context,  MQTTAsync_token token);


private:
  MQTTAsync client_;
  std::string serverURL;
  std::string clientId;
};

#endif // SIMULATOR_MQTTCLIENT_H
