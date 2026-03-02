from flask import Flask, render_template, jsonify
import paho.mqtt.client as mqtt
import json
from datetime import datetime
import heapq

app = Flask(__name__)

# ==========================
# Зони
# ==========================
zone_names = ["room1","room2","room3","room4","corridor","exit"]

rooms = {
    name: {
        "presence": False,
        "distance": 0,
        "temperature": 25
    }
    for name in zone_names
}

# ==========================
# Граф квартири
# ==========================
graph = {
    "room1": ["corridor"],
    "room2": ["corridor"],
    "room3": ["corridor"],
    "room4": ["corridor"],
    "corridor": ["room1","room2","room3","room4","exit"],
    "exit": []
}

# ==========================
# Температурна модель ризику
# ==========================
def zone_cost(temp):
    if temp < 35:
        return 1
    elif temp < 50:
        return 3
    elif temp < 70:
        return 10
    else:
        return 999  # критична зона

# ==========================
# Алгоритм Дейкстри
# ==========================
def find_safest_path(start):

    queue = [(0, start, [])]
    visited = set()

    while queue:
        cost, node, path = heapq.heappop(queue)

        if node in visited:
            continue

        visited.add(node)
        path = path + [node]

        if node == "exit":
            return path

        for neighbor in graph[node]:

            if neighbor == "exit":
                heapq.heappush(queue, (cost, neighbor, path))
            else:
                temp = rooms[neighbor]["temperature"]
                heapq.heappush(
                    queue,
                    (cost + zone_cost(temp), neighbor, path)
                )

    return []

# ==========================
# MQTT
# ==========================
def on_connect(client, userdata, flags, rc):
    print("MQTT connected")
    client.subscribe("savix/#")

def on_message(client, userdata, msg):
    try:
        data = json.loads(msg.payload.decode())
        room = data.get("room")

        if room in rooms:
            rooms[room]["presence"] = data.get("human", False)
            rooms[room]["distance"] = data.get("distance", 0)
            rooms[room]["temperature"] = data.get("temperature", 25)

            print("Updated:", room, rooms[room])

    except Exception as e:
        print("MQTT error:", e)

mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message
mqtt_client.connect("localhost", 1883, 60)
mqtt_client.loop_start()

# ==========================
# Flask
# ==========================
@app.route("/")
def index():
    return render_template("index.html")

@app.route("/data")
def data():

    # Визначення маршрутів
    evac_routes = {}

    for room in rooms:
        if rooms[room]["presence"]:
            evac_routes[room] = find_safest_path(room)

    fire_mode = any(
        rooms[r]["presence"] or rooms[r]["temperature"] > 50
        for r in rooms
    )

    return jsonify({
        "rooms": rooms,
        "routes": evac_routes,
        "fire_mode": fire_mode,
        "time": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    })

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
