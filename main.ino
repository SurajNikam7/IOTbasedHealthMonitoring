#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <PulseSensorPlayground.h>  // Include PulseSensor library

// LCD and SoftwareSerial setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial mySerial(9, 10);  // RX, TX (Arduino communicates with ESP32)

// Pin and variable declarations
int tempPin = A1;
float temp = 0;
int Threshold = 550;  // Threshold for pulse detection
const int PulseWire = A0;  // PulseSensor connected to analog pin A0
const int LED = LED_BUILTIN;

// Create PulseSensor object
PulseSensorPlayground pulseSensor;

void setup() {
  lcd.begin(16, 2);        // Initialize LCD
  pinMode(tempPin, INPUT); // Set temperature sensor pin as input
  Serial.begin(9600);      // For debugging
  mySerial.begin(9600);    // Communication with ESP32

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IOT based Health Monitoring System");
  delay(2000);
  lcd.clear();

  // Configure PulseSensor
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);   // Blink built-in LED with pulse
  pulseSensor.setThreshold(Threshold);

  // Check if PulseSensor object starts correctly
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor initialized successfully!");
  }
}

void loop() {
  // Clear the display once at the start of each loop
  lcd.clear();

  // Read and display pulse
  int myBPM = calculateBPM();

  // Read and display temperature
  readAndDisplayTemperature();

  // Send structured data to ESP32 in JSON-like format
  sendDataToESP(myBPM, temp);

  delay(15000);  // Delay for 15 seconds
}

// Function to read and calculate BPM
int calculateBPM() {
  int myBPM = 0;  // Initialize BPM variable
  if (pulseSensor.sawStartOfBeat()) {  // Check if a beat is detected
    myBPM = pulseSensor.getBeatsPerMinute();  // Get BPM value
    Serial.println("♥ A HeartBeat Happened! ");
    Serial.print("BPM: ");
    Serial.println(myBPM);
  }

  // Display BPM on LCD (row 0)
  lcd.setCursor(0, 0);
  lcd.print("BPM: ");
  lcd.print(myBPM);

  return myBPM;
}

// Function to read and display temperature
void readAndDisplayTemperature() {
  int tempValue = analogRead(tempPin);
  float temperatureC = (tempValue * 5.0 / 1024.0) * 100;  // Convert to Celsius
  float temperatureF = temperatureC * 1.8 + 32;  // Convert to Fahrenheit
  temp = temperatureF;

  // Print temperature on LCD (row 1)
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureF);
  lcd.print(" F");

  // Print to Serial for debugging
  Serial.print("Temp: ");
  Serial.print(temperatureF);
  Serial.println(" F");
}

// Function to send data to ESP32
void sendDataToESP(int bpm, float temp) {
  // Send the data in a structured format (JSON-like)
  String dataToSend = "{\"BPM\": " + String(bpm) + ", \"TEMP\": " + String(temp) + "}";
  
  // Print to Serial Monitor (for debugging)
  Serial.println("Sending data to ESP32: " + dataToSend);
  
  // Send the data to ESP32 via SoftwareSerial
  mySerial.println(dataToSend);
}
