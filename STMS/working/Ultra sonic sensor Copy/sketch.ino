#include <LiquidCrystal.h>
LiquidCrystal lcd(18, 5, 17, 16, 4, 0);
const int triggerPin = 12;
const int echoPin = 14;
void setup() {
Serial.begin(115200);
pinMode(triggerPin, OUTPUT);
pinMode(echoPin, INPUT_PULLUP);
lcd.begin(20, 4);
lcd.print("Distance Example");
delay(1000);
}
void loop() {
// Trigger the ultrasonic sensor
digitalWrite(triggerPin, LOW);
delayMicroseconds(2);
digitalWrite(triggerPin, HIGH);
delayMicroseconds(10);

digitalWrite(triggerPin, LOW);
// Measure the echo time
float duration = pulseIn(echoPin, HIGH);
// Calculate the distance in centimeters
// distance=duration×0.034cm/μs/2
// 0.034 speed of sound in air
float distance = duration * 0.034 / 2;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance is");
lcd.setCursor(0,1);
lcd.print("Duration: " + String(duration)); //(char)223 = degree symbol
lcd.setCursor(0,2);
lcd.print("Distance: " + String(distance,0) + " cm");
lcd.setCursor(0,3);
lcd.print("Distance: " + String(distance/30.48) + " feet");
delay(1000);
}