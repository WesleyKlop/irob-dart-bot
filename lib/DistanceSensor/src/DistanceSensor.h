#ifndef IROB_DART_BOT_DISTANCESENSOR_H
#define IROB_DART_BOT_DISTANCESENSOR_H

#include <Arduino.h>


class DistanceSensor {
private:
    uint8_t triggerPin, echoPin;

public:
    DistanceSensor(uint8_t triggerPin, uint8_t echoPin);

    double measureDistanceCm();
};


#endif //IROB_DART_BOT_DISTANCESENSOR_H
