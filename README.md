# SAVIX 🔥

Autonomous system for detecting people in smoke-filled environments using mmWave radar (HLK-LD2410) and temperature monitoring (DS18B20).

The system works locally via MQTT and displays evacuation routes on a web interface.

---

## 🔧 Hardware

- ESP32
- HLK-LD2410 radar sensor
- DS18B20 temperature sensor
- Raspberry Pi
- Mosquitto MQTT broker

---

## 📡 ESP32 (MQTT.ino)

The ESP32:
- Detects human presence
- Measures temperature
- Sends JSON data via MQTT

Example message:

```json
{
  "room": "room1",
  "human": true,
  "distance": 140,
  "temperature": 27.5
}
