#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(uint8_t triggerPin, uint8_t echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double DistanceSensor::measureDistanceCm() const {
    noInterrupts();
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    const auto distance = (double)pulseIn(echoPin, HIGH) * 0.0343 / 2;

    interrupts();

    return distance;
}