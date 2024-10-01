#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>
#include "DHT.h"

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#define MQTT_HOST IPAddress(192, 168, 1, 1)
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "esp8266"

#define LED_PIN 2

#define DHT_PIN 0
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

int mqtt_status_g = 0;
AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void onWifiConnect(const WiFiEventStationModeGotIP& event)
{
  Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

void connectToMqtt()
{
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
    mqtt_status_g = 1;
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);

  uint16_t packetIdSub = mqttClient.subscribe("led", 2);
  Serial.print("Subscribing at QoS 2, packetId: ");
  Serial.println(packetIdSub);

  mqttClient.publish("test/lol", 0, true, "test 1");
  Serial.println("Publishing at QoS 0");

  uint16_t packetIdPub1 = mqttClient.publish("test/lol", 1, true, "test 2");
  Serial.print("Publishing at QoS 1, packetId: ");
  Serial.println(packetIdPub1);

  uint16_t packetIdPub2 = mqttClient.publish("test/lol", 2, true, "test 3");
  Serial.print("Publishing at QoS 2, packetId: ");
  Serial.println(packetIdPub2);
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event)
{
  mqtt_status_g = 0;
  Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
    mqtt_status_g = 0;
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("##MQTT## Sub ##MQTT##");
  Serial.print("packetId: ");
  Serial.print(packetId);
  Serial.print("qos: ");
  Serial.println(qos);
  Serial.println("##MQTT## Sub ##MQTT##");
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("##MQTT## Un_Sub ##MQTT##");
  Serial.print("packetId: ");
  Serial.println(packetId);
  Serial.println("##MQTT## Un_Sub ##MQTT##");
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("##MQTT### Pub ##MQTT");
  Serial.print("packetId: ");
  Serial.println(packetId);
  Serial.println("##MQTT## Pub ##MQTT##");
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("##MQTT## Rec ##MQTT##");
  Serial.println("Publish received.");
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain: ");
  Serial.println(properties.retain);
  Serial.println("##MQTT## Rec ##MQTT##");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  len: ");
  Serial.println(len);
  Serial.print("  index: ");
  Serial.println(index);
  Serial.print("  total: ");
  Serial.println(total);
  if (*payload == '1')
  {
    digitalWrite(LED_PIN, LOW);
    mqttClient.publish("ledstatus", 0, true, "1");
  }

  if (*payload == '0')
  {
    digitalWrite(LED_PIN, HIGH);
    mqttClient.publish("ledstatus", 0, true, "0");
  } 
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);

  mqttClient.onPublish(onMqttPublish);
  mqttClient.onMessage(onMqttMessage);

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setClientId(MQTT_CLIENT_ID);
  // mqttClient.

    connectToWifi();
    dht.begin();

    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
}

void loop()
{
    float temp;
    float hum;
    char buf[32];
    
    if (mqtt_status_g)
    {
        hum = dht.readHumidity();
        temp = dht.readTemperature();

        mqttClient.publish("dht/tem", 0, true, String(temp).c_str());
        mqttClient.publish("dht/hum", 0, true, String(hum).c_str());

        Serial.printf("tem: %.2f \r\n", temp);
        Serial.printf("hum: %.2f \r\n", hum);
        delay(5000);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
        delay(100);
        digitalWrite(LED_PIN, HIGH);
        delay(100);
    }

}
