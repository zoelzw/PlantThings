# PlantThings
## Nexus 
1. Set up Arduino: download `Adafruit SCD30` and all dependencies 
2. Sensor Wiring: 
    - SCD30: 
        - VIN -- pin 3V (bottom right 2)
        - GND -- GND J4 (bottom right 3)
        - SDA -- pin 17
        - SCL -- pin 16
    - LEDs: 
        - 12V -- PIN 19,20
        - GND -- J4
## Sensything 
this dummy sensor test should work for Teensy as well
1. connect sensything to usb port on pc 
2. open arduinoSerTest/arduinoSerTest.ino in Arduino IDE 
3. go to tools -> boards manager -> choose `ESP32 Dev Module` or download related libraries if this option is not available 
4. select the right port that's connected to Sensything, note it down 
5. upload 
6. open serial monitor and set up baud rate to be 115200, new line 
7. if dummy data is showing up correctlt, quit Arduino (exit the app to release serial port)
##.env
Set up .env in arduino_dashboard top level
Contents should include
```
SERIAL_PORT = "YOUR SERIAL PORT"
```

## Python Server WIP 
1. run appSimple.py in terminal 
2. go to http://127.0.0.1:5001 in browser 
3. Press CTRL+C to quit
4. Debug
    1. test serial communication pipeline: run appVerySimple.py 
    2. TODO: app.py shows unstable serial port connection 
    ```
    * Restarting with stat
    * Debugger is active!
    * Debugger PIN: 398-119-201
    Serial device disconnected. Retrying...
    Reconnected to serial port.
    Serial device disconnected. Retrying...
    127.0.0.1 - - [17/Feb/2025 21:25:48] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:49] "GET /sensor HTTP/1.1" 200 -
    Reconnected to serial port.
    127.0.0.1 - - [17/Feb/2025 21:25:50] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:51] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:52] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:53] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:54] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:55] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:56] "GET /sensor HTTP/1.1" 200 -
    Serial device disconnected. Retrying...
    127.0.0.1 - - [17/Feb/2025 21:25:57] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:25:58] "GET /sensor HTTP/1.1" 200 -
    Reconnected to serial port.
    127.0.0.1 - - [17/Feb/2025 21:25:59] "GET /sensor HTTP/1.1" 200 -
    Serial device disconnected. Retrying...
    127.0.0.1 - - [17/Feb/2025 21:26:00] "GET /sensor HTTP/1.1" 200 -
    127.0.0.1 - - [17/Feb/2025 21:26:01] "GET /sensor HTTP/1.1" 200 -
    Reconnected to serial port.
    ```

## Notes
If you kill the python server with cntrl-c, the web address will not be freed. 
In order to free it, run 
lsof -i :5001 (if using 5001) 
```
COMMAND     PID     USER   FD   TYPE             DEVICE SIZE/OFF NODE NAME
python3.9 28930 aamleshi    9u  IPv4 0xe18216d0d38e1d61      0t0  TCP *:commplex-link (LISTEN)
python3.9 28938 aamleshi    9u  IPv4 0xe18216d0d38e1d61      0t0  TCP *:commplex-link (LISTEN)
python3.9 28938 aamleshi   43u  IPv4 0xe18216d0d38e1d61      0t0  TCP *:commplex-link (LISTEN)
```
kill -9 28930 (in this example PID = 28930) 
    
