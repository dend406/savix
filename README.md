# 🔥 SAVIX – Autonomous Fire Detection & Evacuation System

Autonomous intelligent system for detecting people in smoke-filled environments using mmWave radar sensors and temperature monitoring.

Developed for research and practical implementation in smart building fire safety systems.

---

## 📌 Project Overview

SAVIX is a distributed sensor-based system that:

- Detects human presence using **HLK-LD2410 mmWave radar**
- Monitors temperature via **DS18B20**
- Transmits data via **MQTT**
- Visualizes room state and evacuation routes
- Calculates safest evacuation path using graph algorithms

The system operates fully автономously within a local network.

---

## 🏗 System Architecture
ESP32 + HLK-LD2410 + DS18B20
│
│ MQTT (JSON)
▼
Raspberry Pi (Flask Server)
│
▼
Web Dashboard (SVG plan)


---

## 📁 Repository Structure
SAVIX/
├── server.py # Flask + MQTT server (Raspberry Pi)
├── MQTT.ino # ESP32 firmware
├── requirements.txt # Python dependencies
├── templates/
│ └── index.html # Web interface
└── README.md

---

# 🧠 1️⃣ Raspberry Pi – Server

## Install dependencies

```bash
sudo apt update
sudo apt install python3-pip -y
pip3 install -r requirements.txt

Run server
python3 server.py

Open in browser:
http://RASPBERRY_IP:5000

📦 requirements.txt
flask
paho-mqtt
