# SAVIX 🔥

**SAVIX** is an autonomous system designed for high-reliability human detection in smoke-filled environments. By combining **mmWave radar technology** with real-time temperature monitoring, the system provides a life-saving solution for emergency evacuation when traditional optical sensors (cameras) fail.

The system operates entirely on a local network via **MQTT** and dynamically calculates the safest evacuation routes through a web interface.

---

## 🚀 Key Features
* **Smoke-Resistant Detection:** High-precision presence sensing using 24GHz mmWave radar (HLK-LD2410).
* **Thermal Risk Assessment:** Real-time temperature monitoring (DS18B20) to identify fire hotspots.
* **Dynamic Pathfinding:** Uses Dijkstra’s algorithm to calculate the *safest* route, not just the shortest.
* **Privacy-First:** No cameras or cloud dependencies—data stays on your local Raspberry Pi.
* **Real-Time Dashboard:** Live building map with dynamic route highlighting.

---

## 🔧 Hardware Stack

| Component | Role |
| :--- | :--- |
| **ESP32** | Edge microcontroller for data collection |
| **HLK-LD2410** | mmWave Radar (Presence & Distance detection) |
| **DS18B20** | Temperature sensor for fire risk evaluation |
| **Raspberry Pi** | Central server (MQTT Broker & Flask Web Server) |
| **Mosquitto** | MQTT Broker for lightweight messaging |

---

## 📡 Edge Device: ESP32 (`MQTT.ino`)

The ESP32 nodes are installed in each room. They detect human presence, measure distance to the target, and monitor temperature, publishing a JSON payload to the MQTT topic: `savix/room1`.

### Sample MQTT Payload:
```json
{
  "room": "room1",
  "human": true,
  "distance": 140,
  "temperature": 27.5
}
