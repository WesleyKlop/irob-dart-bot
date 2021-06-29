#include <Arduino.h>
#include <Motion.h>
#include <Rotation.h>
#include <Communication.h>

#define SHOOT_PIN 13
#define POT_PIN A2

Motion motion;
Rotation rotator = [] {
    a4988_config horizontalConfig = {2, 3, 4};
    a4988_config verticalConfig = {5, 6, 7};

    Rotation rotator(horizontalConfig, verticalConfig);
    return rotator;
}();

void serialEvent() {
    const String package = Serial.readStringUntil('\n');
    Serial.print("Arduino recv: ");
    Serial.println(package);

    Serial.print("Executing: ");
    Serial.println(package);
    command_t command = parse_packet(package);

    if (!command.type) {
        return;
    }

    switch (command.type) {
        case 's':
            digitalWrite(SHOOT_PIN, command.degrees);
            break;
        case 'm':
            rotator.move(command.direction, command.degrees);
            break;
        case 'c' :
            auto calibrationValues = String(analogRead(POT_PIN));
            calibrationValues.concat(',');
            calibrationValues.concat(motion.getRoll());

            Serial.write(calibrationValues.c_str());
            break;
    }
}

void setup() {
    // Init logging
    Serial.begin(115200);

    Serial.println("Going to init rotator");
    rotator.begin();
    Serial.println("Finished setup");
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
    if (state.timeLeft() > 5 || !state.isRunning()) {
        //Read potpin val
//        auto potval = analogRead(POT_PIN);
//        Serial.println(potval);
    }

    // Save previous state for diffing
    prev_state = state;
}
