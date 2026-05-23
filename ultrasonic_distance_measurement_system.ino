#include <TM1637Display.h>
//Display
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
//Sensor-Button
const int trigPin = 9;
const int echoPin = 10;
const int buttonPin = 4;

void setup() { 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  display.setBrightness(0x0f);
  // [----]
  uint8_t dash[] = { 0x40, 0x40, 0x40, 0x40 };
  display.setSegments(dash);
}

void loop() {
  
  if (digitalRead(buttonPin) == HIGH) {
    long duration;
    int distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // distance
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.34 / 2;
    //[err ]
    if (distance > 4000 || distance < 20) {
      uint8_t err[] = { 0x79, 0x50, 0x50, 0x00 };
      display.setSegments(err);
    } else {
      display.showNumberDec(distance, false);
    }
    delay(500); 
  }
}
