//
// Created by xiafei zhao on 2026/6/25.
//

#include "MqttClient.h"

void MqttClient::onConnectSuccess(void *context, MQTTAsync_successData *response) {
  std::cout << "MQTT connected." << std::endl;
  auto *client = static_cast<MqttClient *>(context);
  for(const auto &[topic, info] : client->topicMap) {
    MQTTAsync_responseOptions options = MQTTAsync_responseOptions_initializer;

    int rc = MQTTAsync_subscribe(client->client_, topic.c_str(), info, &options);

    if (rc != MQTTASYNC_SUCCESS) {
      std::cout << "Subscribe failed: " << rc << std::endl;
      //      return false;
    }
    std::cout << "Subscribe success: " << topic << std::endl;
  }
  //return true;
}

void onConnectFailure(void *context, MQTTAsync_failureData *response) {
  std::cout << "MQTT connect failed." << std::endl;
}

void MqttClient::onConnectionLost(void *context, char *cause) {
  std::cout << "MQTT connection lost.";

  if (cause != nullptr) {
    std::cout << " Cause: " << cause;
  }

  std::cout << std::endl;
}
int MqttClient::onMessageArrived(void *context, char *topicName, int topicLen,
                                 MQTTAsync_message *message) {
  std::cout << topicName << std::endl;
  auto *client = static_cast<MqttClient *>(context);

  std::string topic(topicName);
  std::string payload(static_cast<char *>(message->payload),
                      message->payloadlen);
  std::cout << std::boolalpha << (client->messageHandler != nullptr) << std::endl;
  if (client->messageHandler) {
    client->messageHandler(topic, payload);
  }

  MQTTAsync_freeMessage(&message);
  MQTTAsync_free(topicName);
  return 1;
}

void MqttClient::setMessageHandler(MessageHandler handler) {
  this->messageHandler = std::move(handler);
}

void MqttClient::onDeliveryComplete(void *context, MQTTAsync_token token) {
  std::cout << "Publish success." << std::endl;
}

bool MqttClient::init(const std::string &serverURL,
                      const std::string &clientId) {
  this->serverURL = serverURL;
  this->clientId = clientId;

  int rc = MQTTAsync_create(&client_, serverURL.c_str(), clientId.c_str(),
                            MQTTCLIENT_PERSISTENCE_NONE, nullptr);

  if (rc != MQTTASYNC_SUCCESS) {
    return false;
  }

  MQTTAsync_setCallbacks(client_, this, MqttClient::onConnectionLost,
                         onMessageArrived, onDeliveryComplete);

  return true;
}

bool MqttClient::connect() {
  MQTTAsync_connectOptions options = MQTTAsync_connectOptions_initializer;

  options.keepAliveInterval = 20;
  options.cleansession = 1;
  options.onSuccess = onConnectSuccess;
  options.onFailure = onConnectFailure;
  options.context = this;

  int rc = MQTTAsync_connect(client_, &options);

  if (rc != MQTTASYNC_SUCCESS) {
    std::cout << "MQTT connect failed: " << rc << std::endl;
    return false;
  }

  return true;
}

void MqttClient::disconnect() {
  MQTTAsync_disconnectOptions options = MQTTAsync_disconnectOptions_initializer;
  MQTTAsync_disconnect(client_, &options);
}

bool MqttClient::publish(const std::string &topic, const std::string &payload) {
  MQTTAsync_message message = MQTTAsync_message_initializer;
  MQTTAsync_responseOptions options = MQTTAsync_responseOptions_initializer;

  message.payload = (void *)payload.c_str();
  message.payloadlen = (int)payload.size();
  message.qos = 1;
  message.retained = 0;

  int rc = MQTTAsync_sendMessage(client_, topic.c_str(), &message, &options);

  return rc == MQTTASYNC_SUCCESS;
}

bool MqttClient::subscribe(const std::string &topic) {
  //  topicMap[topic] = 1;
  topicMap.try_emplace(topic, 1);
  return true;
}

MqttClient::~MqttClient() {
  disconnect();
  MQTTAsync_destroy(&client_);
}