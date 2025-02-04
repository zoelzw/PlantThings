import serial, time

ser = serial.Serial("/dev/cu.usbmodem157920201", 115200, timeout=2)
time.sleep(2)

while True:
    line = ser.readline().decode("utf-8", "ignore").strip()
    if line:
        print("Got:", line)
    else:
        print("No data this second")