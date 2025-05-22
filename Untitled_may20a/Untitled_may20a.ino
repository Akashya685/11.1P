#include "arduino_secrets.h"
#include "thingProperties.h"

#define TRIG_PIN 3
#define ECHO_PIN 2

String lastState = "";
unsigned long lastChangeTime = 0;
const unsigned long holdDuration = 5000; 

void setup() {
  Serial.begin(9600);
  delay(1500);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  Serial.println("Connecting to IoT Cloud.....");
}

void loop() {
  ArduinoCloud.update(); 


  if (!autoMode) {
    Serial.println(" The Auto mode is OFF");
    delay(500);
    return;
  }


  if (millis() - lastChangeTime >= holdDuration) {
    float distance = getDistance();
    String currentState = (distance < 50 && distance > 2) ? "UNLOCK" : "LOCK";

    if (currentState != lastState) {
      Serial.print("Distance: ");
      Serial.println(distance);
      Serial.println(currentState); 

      lastState = currentState;
      lastChangeTime = millis(); 
    }
  }

  delay(50); 
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  return duration * 0.034 / 2;
}


void onAutoModeChange() {
  Serial.print("autoMode changed to ");
  Serial.println(autoMode ? "ON" : "OFF");
}

void onPasswordInputChange() {
  Serial.print("Password entered: ");
  Serial.println(passwordInput);

  if (passwordInput == "0000") {
    autoMode = !autoMode; 
    Serial.print("CORRECT PASS ENTERED. Auto mode is now: ");
    Serial.println(autoMode ? "ENABLED" : "DISABLED");
  } else {
    Serial.println("Incorrect password.");
  }
  passwordInput = "";
}

