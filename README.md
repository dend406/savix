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
---
## Topic:
savix/room1
---
## 🖥 Raspberry Pi (server.py)
The Raspberry Pi:
Receives MQTT data
Stores room state
Calculates safest evacuation path
Displays real-time building plan
Run server:
pip install flask paho-mqtt
python3 server.py
---

## Open:
http://RASPBERRY_IP:5000
---

## 🧠 Evacuation Logic
Rooms are modeled as a graph
Temperature defines risk cost
Dijkstra algorithm finds safest path
Routes are highlighted dynamically
---

## 🚀 Features
✔ Smoke-resistant human detection
✔ Temperature-based risk evaluation
✔ Real-time web interface
✔ Safe evacuation routing
✔ Fully local system
---
