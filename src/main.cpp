#include <Arduino.h>
#include <Motion.h>

Motion motion;

void setup() {
    Serial.begin(9600);
    motion.init();
}

void loop() {
    Serial.print(motion.getPitch());
    Serial.println(" degrees pitch");
    Serial.print(motion.getRoll());
    Serial.println(" degrees roll");
}