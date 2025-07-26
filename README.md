# IOTbasedHealthMonitoring
🩺 IoT-Based Health Monitoring System
An IoT-enabled health monitoring system designed to measure and transmit heart rate (BPM) and body temperature in real-time using wireless connectivity. Ideal for remote patient monitoring and health data logging on cloud platforms like ThingSpeak.

📌 Features
  ✅ Real-time monitoring of heart rate and body temperature
  
  ✅ Data transmission to ThingSpeak Cloud via ESP8266
  
  ✅ Microcontroller-based processing (Arduino Uno)
  
  ✅ Visual output using 16x2 LCD
  
  ✅ Compact, low-power, and scalable design

⚙️ Components Used
  Component	Description
    Arduino Uno	Main microcontroller
    PulseSensor (HW-827)	Measures heart rate (BPM)
    LM35	Analog temperature sensor
    ESP8266 (ESP-01)	Wi-Fi module for ThingSpeak updates
    16x2 LCD	Display for local output
    10K Potentiometer	LCD contrast adjustment
    Breadboard & Wires	Circuit prototyping
    Power Source	5V supply (USB or adapter)

🔌 Working Principle
  PulseSensor reads heartbeat pulses and calculates BPM.
  
  LM35 outputs voltage proportional to body temperature.
  
  The Arduino Uno reads both sensor values and displays them on a 16x2 LCD.
  
  Sensor data is sent to ESP8266 via SoftwareSerial.
  
  ESP8266 connects to Wi-Fi and uploads data to ThingSpeak at regular intervals.

🧰 Circuit Connections
  Arduino UNO:
  PulseSensor → A0
  
  LM35 → A1
  
  ESP8266 Rx/Tx → D2/D3 (via SoftwareSerial)
  
  LCD → 8-bit/4-bit mode (D4–D7 + RS/EN)
  
  Potentiometer → LCD Contrast (V0 pin)
  
  ESP8266:
  VCC & CH_PD → 3.3V
  
  GND → GND
  
  TX → Arduino D2
  
  RX → Arduino D3 (with voltage divider)
  
  ☁️ ThingSpeak Configuration
  Create a ThingSpeak account: https://thingspeak.com
  
  Create a new channel with two fields:
  
  Field 1: BPM
  
  Field 2: Temperature
  
  Note your Channel ID and Write API Key
  
  Configure ESP8266 code to send data using HTTP GET requests.

📋 How to Use
  Power up the system via USB or external 5V source.
  
  The LCD displays live BPM and Temperature readings.
  
  Data is uploaded to ThingSpeak every 15–30 seconds.
  
  You can visualize real-time graphs from anywhere on the ThingSpeak dashboard.

📊 Example Output
  Metric	Value
  Heart Rate	78 BPM
  Temperature	36.7 °C
  Wi-Fi	Connected ✅
  Cloud Sync	Successful ✅

🛡️ Notes & Precautions
  Ensure ESP8266 gets a stable 3.3V power supply (NOT 5V).
  
  Use a voltage divider or logic level shifter on Arduino → ESP8266 TX line.
  
  Allow 15 seconds minimum between ThingSpeak updates to avoid API limit.

📚 Future Enhancements
  Add SpO₂ and Blood Pressure sensors
  
  Mobile App integration (Blynk / MIT App Inventor)
  
  Alerts for abnormal readings (SMS/Email/Telegram)
  
  Battery-powered portable version

📄 License
  This project is released under the MIT License.

🙋‍♂️ Author
  Suraj N.
  Feel free to connect via LinkedIn or contact me for questions and collaboration.

