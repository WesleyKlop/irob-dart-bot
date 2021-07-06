#ifndef IROB_DART_BOT_ROTATION_H
#define IROB_DART_BOT_ROTATION_H

#include <A4988.h>

#define STEP_SIZE 16
#define MOTOR_STEPS 200

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

    rotator_state() = default;

    unsigned long timeLeft() {
        if(verticalWaitTime == 0) {
            return horizontalWaitTime;
        }
        if(horizontalWaitTime == 0) {
            return verticalWaitTime;
        }
        return min(horizontalWaitTime, verticalWaitTime);
    }

    bool isRunning() const {
        return horizontalWaitTime > 0 || verticalWaitTime > 0;
    }
};

class Rotation {
private:
    A4988 horizontalStepper;
    A4988 verticalStepper;
    bool horizontalRunning = false;
    bool verticalRunning = false;

public:
    Rotation(a4988_config hc, a4988_config vc);

    void up(long degrees);

    void down(long degrees);

    void left(long degrees);

    void right(long degrees);

    void stop();

    rotator_state nextAction();

    void begin(float rpm);

    void handleState(rotator_state state);

    void move(char direction, long degrees);
};


#endif //IROB_DART_BOT_ROTATION_H
