#include <Arduino.h>
#include <Motion.h>
#include <Rotation.h>

Motion motion;
Rotation rotator = [] {
    a4988_config horizontalConfig = {2, 3, 4};
    a4988_config verticalConfig = {7, 8, 9};

    Rotation rotator(horizontalConfig, verticalConfig);
    return rotator;
}();

void setup() {
    Serial.begin(9600);
    Serial.println("Going to rotate up...");

    rotator.init();
    rotator.up(10 * 360);
    Serial.println("Instructed for up");
}

void loop() {
    // motor control loop - send pulse and return how long to wait until next pulse
    auto state = rotator.nextAction();

    rotator.handleState(state);

    // (optional) execute other code if we have enough time
    if (state.timeLeft() > 100) {

    }
}