#define BLYNK_TEMPLATE_ID "TMPL3cw5iiiqK"
#define BLYNK_TEMPLATE_NAME "STMS Device 2"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "-3JeUffitSdEzVrbhWyAmeLd1OaXglpW"; 

char ssid[] = "OPPOReno8T5G";
char pass[] = "OPPO8T5G";
#define TRIG_PIN D6
#define ECHO_PIN D7
#define LEVEL_GAUGE V0
#define CALL_SWITCH V3
#define CALL_STATUS V1
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

//#define BLYNK_TEMPLATE_ID "TMPL3I6TXjsMc"
//#define BLYNK_TEMPLATE_NAME "STMS Device 2"
//char auth[] = ""XFhGtL1_8ignLOYHcMmb0zvpIZDu9jUF"";  

//char ssid[] = "HACKSTORM2K25";
//char pass[] = "12345678";
//