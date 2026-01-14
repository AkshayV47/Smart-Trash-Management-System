#include <ArduinoIoTCloud.h>
#include <WiFi.h>

// WiFi and device credentials
const char SSID[] = "OPPOReno8T5G";          // Network SSID
const char PASS[] = "OPPO8T5G";              // Network password
const char DEVICE_ID[] = "78ab9386-28ad-4fe7-90f0-530f0b3df8d5";  // Device ID
const char SECRET_KEY[] = "XR2eMUIGk5IECQ@mH#x7s5cws";           // Secret Key

// Ultrasonic sensor pins
const int trigPin = D6;  // Trigger pin
const int echoPin = D7;  // Echo pin

// Distance constants for percentage calculation (assumed values)
const float max_distance = 50.0;  // Maximum distance (empty, 0%)
const float min_distance = 5.0;   // Minimum distance (full, 100%)

// Cloud variables
CloudFloat percentage;    // For percentage widget
CloudLocation mAP;        // For map widget
CloudBool call;           // For call button widget

// WiFi connection handler
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Configure ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Seed random number generator (ESP8266 has one analog pin, A0)
  randomSeed(analogRead(A0));
  
  // Set up Arduino Cloud
  ArduinoCloud.setBoardId(DEVICE_ID);
  ArduinoCloud.setSecretDeviceKey(SECRET_KEY);
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  // Register cloud properties
  ArduinoCloud.addProperty(percentage, READWRITE, ON_CHANGE);
  ArduinoCloud.addProperty(mAP, READWRITE, ON_CHANGE);
  ArduinoCloud.addProperty(call, READWRITE, ON_CHANGE);
}

void loop() {
  // Update cloud connection
  ArduinoCloud.update();
  
  // Read ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;  // Distance in cm
  
  // Calculate percentage based on distance
  if (distance > max_distance) {
    percentage = 0;  // Tank empty
  } else if (distance < min_distance) {
    percentage = 100;  // Tank full
  } else {
    percentage = ((max_distance - distance) / (max_distance - min_distance)) * 100;
  }
  
  // Handle call button press
  if (call) {
    Serial.println("call has been placed");
    
    // Generate random latitude (-90 to 90) and longitude (-180 to 180)
    float lat = random(-90000, 90001) / 1000.0;    // -90.000 to 90.000
    float lon = random(-180000, 180001) / 1000.0;  // -180.000 to 180.000
    
    // Update map location
    mAP = Location(lat, lon);
    
    // Reset call button (assumes toggle behavior)
    call = false;
  }
}


#include <ArduinoIoTCloud.h>
#include <WiFi.h>

// WiFi and device credentials
const char SSID[] = "OPPOReno8T5G";         // Replace with your WiFi name
const char PASS[] = "YOUR_WIFI_PASSWORD";     // Replace with your WiFi password
const char DEVICE_ID[] = "YOUR_DEVICE_ID";    // Replace with your Device ID
const char SECRET_KEY[] = "YOUR_SECRET_KEY";  // Replace with your Secret Key

// Ultrasonic sensor pins
const int trigPin = D6;  // Trigger pin (GPIO12)
const int echoPin = D7;  // Echo pin (GPIO13)

// Distance constants for percentage calculation
const float max_distance = 50.0;  // Max distance in cm (empty, 0%)
const float min_distance = 5.0;   // Min distance in cm (full, 100%)

// Cloud variable for percentage
CloudFloat percentage;

// WiFi connection handler
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  
  // Configure ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set up Arduino Cloud
  ArduinoCloud.setBoardId(DEVICE_ID);
  ArduinoCloud.setSecretDeviceKey(SECRET_KEY);
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  // Register cloud property
  ArduinoCloud.addProperty(percentage, READWRITE, ON_CHANGE);
}

void loop() {
  // Update cloud connection
  ArduinoCloud.update();
  
  // Read ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;  // Convert time to distance in cm
  
  // Calculate percentage based on distance
  if (distance > max_distance) {
    percentage = 0;  // Empty (0%)
  } else if (distance < min_distance) {
    percentage = 100;  // Full (100%)
  } else {
    // Linear interpolation between min and max distance
    percentage = ((max_distance - distance) / (max_distance - min_distance)) * 100;
  }
  
  // Print to Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Percentage: ");
  Serial.print(percentage);
  Serial.println("%");
  
  // Delay to avoid flooding the cloud (1 second)
  delay(1000);
}