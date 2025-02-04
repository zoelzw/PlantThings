from flask import Flask, render_template, jsonify
import serial
import json
import threading
import time

# Set up Flask app
app = Flask(__name__)

# Configure Serial (change based on your system)

SERIAL_PORT = "/dev/cu.usbmodem157920201"   # On Windows: "COM3", Linux/Mac: "/dev/ttyUSB0" or "/dev/cu.usbmodem..."
BAUD_RATE = 9600


# Connect to Arduino
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=3)
time.sleep(8)
ser.flush()

# Sensor data storage (for visualization)
sensor_history = {"timestamps": [], "temp": [], "humidity": [], "co2": []}
MAX_HISTORY = 1  # Number of historical points to keep

# Background thread to continuously read sensor data
sensor_data = {"temp": "--", "humidity": "--", "co2": "--"}

def read_sensor_data():
    global sensor_data
    while True:
        try:
            if ser.in_waiting > 0: 
                line = ser.readline().decode("utf-8").strip()
                if line:  # Ensure data is not empty
                    new_data = json.loads(line)
                    print(new_data)
                    sensor_data.update(new_data)

                    # Store historical data
                    timestamp = time.strftime("%H:%M:%S")
                    sensor_history["timestamps"].append(timestamp)
                    sensor_history["temp"].append(new_data["temp"])
                    sensor_history["humidity"].append(new_data["humidity"])
                    sensor_history["co2"].append(new_data["co2"])

                    # Limit history size
                    if len(sensor_history["timestamps"]) > MAX_HISTORY:
                        for key in sensor_history:
                            sensor_history[key].pop(0)
        except json.JSONDecodeError:
            print("json wrong")
            # Ignore malformed data
            pass

def reconnect_serial():
    global ser
    while True:
        try:
            ser.close()
            ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=3)
            time.sleep(2)
            print("Reconnected to serial port.")
            return
        except serial.SerialException:
            print("Retrying serial connection...")
            time.sleep(5)

# Start background thread
threading.Thread(target=read_sensor_data, daemon=True).start()

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/sensor")
def get_sensor_data():
    return jsonify(sensor_data)

@app.route("/history")
def get_sensor_history():
    return jsonify(sensor_history)

if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=5001)
