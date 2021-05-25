#include <Arduino.h>
#include <DistanceSensor.h>

DistanceSensor distanceSensor(3, 2);

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(distanceSensor.measureDistanceCm());
}