#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "MyLD2410.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// ----------- WiFi -----------
const char* ssid = "prol";
const char* password = "korotkov";

// ----------- MQTT -----------
const char* mqtt_server = "192.168.2.145";
const char* topic = "savix/room2";

// ----------- HLK -----------
#define RX_PIN 16
#define TX_PIN 17

// ----------- DS18B20 -----------
#define ONE_WIRE_BUS 22

// ----------- LED -----------
#define LED_PIN 2

WiFiClient espClient;
PubSubClient client(espClient);

MyLD2410 radar(Serial1);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

unsigned long lastSend = 0;
unsigned long interval = 2000;

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("SAVIX_room2")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  Serial1.begin(256000, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // HLK
  if (!radar.begin()) {
    Serial.println("HLK error!");
    while (true) {}
  }
  radar.enhancedMode();

  // Temperature
  tempSensor.begin();

  // WiFi
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  Serial.println("SAVIX sensor node ready");
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - lastSend > interval) {
    lastSend = millis();

    bool humanDetected = false;
    int distance = 0;

    if (radar.check() == MyLD2410::Response::DATA) {
      if (radar.stationaryTargetDetected()) {
        humanDetected = true;
        distance = radar.stationaryTargetDistance();
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    }

    tempSensor.requestTemperatures();
    float temperature = tempSensor.getTempCByIndex(0);

    // ---- Формуємо JSON ----
    StaticJsonDocument<200> doc;
    doc["room"] = "room2";
    doc["human"] = humanDetected;
    doc["distance"] = distance;
    doc["temperature"] = temperature;

    char buffer[256];
    serializeJson(doc, buffer);

    client.publish(topic, buffer);

    Serial.println("Data sent:");
    Serial.println(buffer);
    Serial.println("--------------------");
  }
}