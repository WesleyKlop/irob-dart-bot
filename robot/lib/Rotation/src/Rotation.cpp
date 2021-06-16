#include "Rotation.h"

void Rotation::up(int degrees) {
    verticalStepper.enable();
    verticalStepper.startRotate(degrees);
}

void Rotation::down(int degrees) {
    verticalStepper.enable();
    verticalStepper.startRotate(-degrees);
}

void Rotation::left(int degrees) {
    horizontalStepper.enable();
    horizontalStepper.startRotate(-degrees);
}

void Rotation::right(int degrees) {
    horizontalStepper.enable();
    horizontalStepper.startRotate(degrees);
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

void Rotation::init() {
    horizontalStepper.begin(90, 16);
    horizontalStepper.setEnableActiveState(LOW);
    verticalStepper.begin(45, 16);
    verticalStepper.setEnableActiveState(LOW);
}

void Rotation::handleState(rotator_state state) {
    if (state.horizontalWaitTime == 0)
        horizontalStepper.disable();
    if (state.verticalWaitTime == 0)
        verticalStepper.disable();
}
