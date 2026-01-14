#define BLYNK_TEMPLATE_ID "TMPL3cw5iiiqK"
#define BLYNK_TEMPLATE_NAME "STMS Device 2"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "*********************"; 
char ssid[] = "*********";
char pass[] = "*************";
#define TRIG_PIN D6
#define ECHO_PIN D7
#define WATER_LEVEL_GAUGE V0
#define CALL_SWITCH V3
#define CALL_STATUS V1
bool callSent = false;
BlynkTimer timer;
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  timer.setInterval(1000L, []() { // Update every 5 seconds
    float waterLevelPercentage = calculateWaterLevelPercentage();
    Blynk.virtualWrite(WATER_LEVEL_GAUGE, waterLevelPercentage); // Send water level percentage to Gauge widget
  });
}

void loop() {
  Blynk.run();
  timer.run();
}

float calculateWaterLevelPercentage() {
  // Read distance from ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;  // Convert distance to centimeters
  
  // Assuming a max depth of the container is 20 cm and a min depth of 0 cm
  // Convert depth to percentage (0% to 100%)
  float percentage = map(distance, 0, 15, 100, 0); // Adjusted for max depth of 20 cm
  
  return percentage;
}

BLYNK_WRITE(CALL_SWITCH) { // Call switch handler
  int switchState = param.asInt();
  if (switchState == 1) {
    // Call your function here to initiate clean action
    callSent = true;
    Blynk.virtualWrite(CALL_STATUS, "Call has been sent"); // Update status to indicate call has been sent
  } else {
    callSent = false;
    Blynk.virtualWrite(CALL_STATUS, "Call not sent"); // Update status to indicate call has not been sent
  }

}
