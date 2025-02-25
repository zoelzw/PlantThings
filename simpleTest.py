import serial
import json
import flask
print(json.__version__)
print(flask.__version__)
ser = serial.Serial("/dev/cu.usbmodem157920201", 115200, timeout=3)
while True:
    line = ser.readline().decode("utf-8", errors="ignore").strip()
    if line:
        print(line)
