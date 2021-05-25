#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(uint8_t triggerPin, uint8_t echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double DistanceSensor::measureDistanceCm() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    const auto duration = (double) pulseIn(echoPin, HIGH);

    return (duration * .0343) / 2;
}