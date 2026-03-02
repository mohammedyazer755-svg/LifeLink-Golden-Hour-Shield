1. Microcontroller
ESP32 Development Board
Dual-core processor
Built-in WiFi & Bluetooth
Handles sensor data processing
Sends accident data to cloud server
(Alternative: Arduino Uno + GSM module)
📊 2. Accelerometer & Gyroscope Sensor
MPU6050 (6-Axis IMU)
Measures acceleration (X, Y, Z axis)
Detects sudden impact force
Used for severity classification (Minor / Moderate / Major)
📍 3. GPS Module
NEO-6M GPS Module
Provides real-time latitude & longitude
Sends accident location to emergency server
Accuracy: ~2.5 meters
📡 4. Communication Module
If using ESP32:
Built-in WiFi for cloud communication
If using Arduino:
SIM800L GSM Module (for SMS / mobile data transmission)
🔔 5. Alert System
Active Buzzer
Sounds immediately after impact detection
Can serve as 10-second cancellation window alert
Optional:
LED Indicator for status (Green = Normal, Red = Emergency)
🔋 6. Power Supply
7.4V Li-ion Battery Pack
OR
5V regulated power supply (vehicle powered)
Optional:
Voltage regulator (LM7805)
🧩 7. Optional Advanced Sensors (Future Expansion)
Pulse sensor (driver heart monitoring)
Airbag deployment sensor
Vehicle speed sensor (OBD-II integration)
Tilt sensor (rollover detection)
