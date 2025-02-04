import serial, time

ser = serial.Serial("/dev/tty.usbserial-D30873OK", 115200, timeout=2)
time.sleep(2)

while True:
    line = ser.readline().decode("utf-8", "ignore").strip()
    if line:
        print("Got:", line)
    else:
        print("No data this second")