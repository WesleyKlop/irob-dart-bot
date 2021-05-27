#include <Arduino.h>
#include <DistanceSensor.h>
#include <Motion.h>

DistanceSensor distanceSensor(3, 2);
Motion motion;

void setup() {
    Serial.begin(9600);
    motion.init();
}

void loop() {
    Serial.println(distanceSensor.measureDistanceCm());
    Serial.print(motion.getPitch());
    Serial.println(" degrees pitch");
    Serial.print(motion.getRoll());
    Serial.println(" degrees roll");
}