#ifndef IROB_DART_BOT_ROTATION_H
#define IROB_DART_BOT_ROTATION_H

#include <A4988.h>

struct a4988_config {
    short stepPin = PIN_UNCONNECTED;
    short dirPin = PIN_UNCONNECTED;
    short enablePin = PIN_UNCONNECTED;
    short ms1Pin = PIN_UNCONNECTED;
    short ms2Pin = PIN_UNCONNECTED;
    short ms3Pin = PIN_UNCONNECTED;

    a4988_config(short stepPin, short dirPin, short enablePin, short ms1Pin, short ms2Pin, short ms3Pin) :
            stepPin(stepPin), dirPin(dirPin), enablePin(enablePin), ms1Pin(ms1Pin), ms2Pin(ms2Pin), ms3Pin(ms3Pin) {
    }

    a4988_config(short stepPin, short dirPin, short enablePin) :
            stepPin(stepPin), dirPin(dirPin), enablePin(enablePin) {}

    a4988_config() = default;
};

struct rotator_state {
    unsigned long horizontalWaitTime = 0;
    unsigned long verticalWaitTime = 0;

    rotator_state(unsigned long horWaitTime, unsigned long verWaitTime) :
            horizontalWaitTime(horWaitTime), verticalWaitTime(verWaitTime) {}

    unsigned long timeLeft() {
        return min(horizontalWaitTime, verticalWaitTime);
    }

    bool isRunning() {
        return horizontalWaitTime > 0 || verticalWaitTime > 0;
    }
};

class Rotation {
private:
    A4988 horizontalStepper;
    A4988 verticalStepper;

public:
    Rotation(a4988_config hc, a4988_config vc);

    void up(int degrees);

    void down(int degrees);

    void left(int degrees);

    void right(int degrees);

    void stop();

    rotator_state nextAction();

    void init();

    void handleState(rotator_state state);
};


#endif //IROB_DART_BOT_ROTATION_H
