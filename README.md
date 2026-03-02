SAVIX 🔥SAVIX is an autonomous system designed for detecting human presence in smoke-filled environments using mmWave radar technology and real-time temperature monitoring. The system operates entirely on a local network via MQTT and dynamically calculates safe evacuation routes.🚀 Key FeaturesSmoke-Resistant Detection: High-precision human detection through thick smoke using mmWave technology.Risk Evaluation: Real-time hazard assessment based on ambient temperature.Dynamic Routing: Calculates the safest path (not just the shortest) using live sensor data.Privacy-Focused: Fully local system; no cloud dependency or external data sharing.Real-Time Dashboard: Web-based interface showing the building plan and evacuation paths.🔧 Hardware StackComponentRoleESP32Edge controller for sensor data collectionHLK-LD2410mmWave radar (presence & motion detection)DS18B20High-precision temperature sensorRaspberry PiCentral server, MQTT broker, and Web hostMosquittoMQTT Broker for lightweight messaging📡 Edge Device: ESP32 (MQTT.ino)The ESP32 units act as nodes in each room, detecting presence and temperature before publishing a JSON payload to the MQTT topic: savix/room1.Data Schema:JSON{
  "room": "room1",
  "human": true,
  "distance": 140,
  "temperature": 27.5
}
🖥 Central Server: Raspberry Pi (server.py)The server processes incoming MQTT messages, updates the building's state, and serves the evacuation dashboard.Installation & Launch:Bash# Install dependencies
pip install flask paho-mqtt

# Run the server
python3 server.py
Accessing the Interface:Open your browser and navigate to:http://<RASPBERRY_IP>:5000🧠 Evacuation LogicThe building is modeled as a weighted graph where rooms are nodes and doorways are edges.Risk Cost: Each edge's "weight" is dynamically calculated based on temperature ($T$).Algorithm: The system employs Dijkstra’s Algorithm to find the path with the lowest cumulative risk.Visualization: Routes are highlighted in real-time on the building map.$$\text{Edge Weight} = \text{Distance} \times \text{Risk Factor}(T)$$🚀 Roadmap[ ] Multi-floor support and 3D map rendering.[ ] Integrated audio alerts via ESP32 buzzers.[ ] Mobile application for first responders.
