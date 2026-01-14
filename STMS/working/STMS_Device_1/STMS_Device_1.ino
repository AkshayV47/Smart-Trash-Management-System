#define BLYNK_TEMPLATE_ID "TMPL317gysfle"
#define BLYNK_TEMPLATE_NAME "STMS Device 1"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "********************************";
char ssid[] = "*************";
char pass[] = "********";
#define TRIG_PIN D6
#define ECHO_PIN D7
#define LEVEL_GAUGE V0
#define CALL_SWITCH V1
#define CALL_STATUS V2
bool callSent = false;
BlynkTimer timer;
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  
  timer.setInterval(1000L, []() {
    float LevelPercentage = calculateLevelPercentage();
    Blynk.virtualWrite(LEVEL_GAUGE, LevelPercentage); 
  });
}

void loop() {
  Blynk.run();
  timer.run();
}

float calculateLevelPercentage() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  float percentage = map(distance, 0, 25, 100, 0); // depth of 25 cm
  
  return percentage;
}

BLYNK_WRITE(CALL_SWITCH) { 
  int switchState = param.asInt();
  if (switchState == 1) {
    callSent = true;
    Blynk.virtualWrite(CALL_STATUS, "Call has been sent");
  } else {
    callSent = false;
    Blynk.virtualWrite(CALL_STATUS, "Call not sent"); 
  }
}

//
//#define BLYNK_TEMPLATE_ID "TMPL32IXCS_kj"
//#define BLYNK_TEMPLATE_NAME "STMS Device"
//char auth[] = "OdzbACj1PD5fY1lVpmzF6qzMPCIpw2bb"
//

//
//char ssid[] = "HACKSTORM2K25";
//char pass[] = "12345678";

//
