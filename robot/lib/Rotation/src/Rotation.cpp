#include "Rotation.h"

void Rotation::up(long degrees) {
    if (degrees == 0) {
        verticalStepper.stop();
        verticalStepper.disable();
        verticalRunning = false;
        return;
    }
    if (!verticalRunning) {
        verticalStepper.enable();
        verticalRunning = true;
    }
    verticalStepper.startRotate(-degrees);
}

void Rotation::down(long degrees) {
    if (degrees == 0) {
        verticalStepper.stop();
        verticalStepper.disable();
        verticalRunning = false;
        return;
    }
    if (!verticalRunning) {
        verticalStepper.enable();
        verticalRunning = true;
    }
    verticalStepper.startRotate(degrees);
}

void Rotation::left(long degrees) {
    if (degrees == 0) {
        horizontalStepper.stop();
        horizontalStepper.disable();
        horizontalRunning = false;
        return;
    }
    if (!horizontalRunning) {
        horizontalStepper.enable();
        horizontalRunning = true;
    }
    horizontalStepper.startRotate(degrees);
}

void Rotation::right(long degrees) {
    if (degrees == 0) {
        horizontalStepper.stop();
        horizontalStepper.disable();
        horizontalRunning = false;
        return;
    }
    if (!horizontalRunning) {
        horizontalStepper.enable();
        horizontalRunning = true;
    }
    horizontalStepper.startRotate(-degrees);
}

void Rotation::stop() {
    horizontalStepper.stop();
    verticalStepper.stop();
}

Rotation::Rotation(a4988_config hc, a4988_config vc) :
        horizontalStepper(200, hc.dirPin, hc.stepPin, hc.enablePin, hc.ms1Pin, hc.ms2Pin, hc.ms3Pin),
        verticalStepper(200, vc.dirPin, vc.stepPin, vc.enablePin, vc.ms1Pin, vc.ms2Pin, vc.ms3Pin) {
}

rotator_state Rotation::nextAction() {
    rotator_state state(horizontalStepper.nextAction(), verticalStepper.nextAction());
    return state;
}

void Rotation::begin(float rpm) {
    horizontalStepper.begin(rpm, 16);
    horizontalStepper.setEnableActiveState(LOW);
//    horizontalStepper.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED, 2000, 1000);
    verticalStepper.begin(rpm, 16);
    verticalStepper.setEnableActiveState(LOW);
//    verticalStepper.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED, 2000, 1000);
}

void Rotation::handleState(rotator_state state) {
    if (state.horizontalWaitTime == 0) {
        horizontalStepper.disable();
        horizontalRunning = false;
    }
    if (state.verticalWaitTime == 0) {
        verticalStepper.disable();
        verticalRunning = false;
    }
}

void Rotation::move(char direction, long degrees) {
    switch (direction) {
        case 'u':
            return up(degrees);
        case 'l':
            return left(degrees);
        case 'd':
            return down(degrees);
        case 'r':
            return right(degrees);
        default:
            // Nothing to do
            return;
    }
}
