#include <Arduino.h>
#include <Motion.h>
#include <Rotation.h>
#include <Communication.h>

#define SHOOT_PIN 8

Motion motion;
Rotation rotator = [] {
    a4988_config horizontalConfig = {2, 3, 4};
    a4988_config verticalConfig = {5, 6, 7};

    Rotation rotator(horizontalConfig, verticalConfig);
    return rotator;
}();

void handleMessage(int size) {
    command_t command = read_packet();

    Serial.print("Command: ");
    Serial.print(command.type);
    Serial.print(command.direction);
    Serial.println(command.degrees);

    switch (command.type) {
        case 's':
            digitalWrite(SHOOT_PIN, command.degrees);
            break;
        case 'm':
            rotator.move(command.direction, command.degrees);
            break;
        default:
            Serial.print("unknown command: ");
            Serial.println(command.type);
    }
}

void setup() {
    // Init logging
    Serial.begin(9600);

    // Init pi communication
    Wire.begin(0x8);
    Wire.onReceive(handleMessage);

    Serial.println("started");
    // Init motor drivers
    rotator.begin();
}

rotator_state prev_state;

void loop() {
    // motor control loop - send pulse and return how long to wait until next pulse
    auto state = rotator.nextAction();

    // If we finished, disable the motors.
    if (prev_state.isRunning() && !state.isRunning()) {
        rotator.handleState(state);
    }

    // (optional) execute other code if we have enough time
    if (state.timeLeft() > 100) {

    }

    // Save previous state for diffing
    prev_state = state;
}
