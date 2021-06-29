#include <Arduino.h>
#include <Motion.h>
#include <Rotation.h>
#include <Communication.h>

#define SHOOT_PIN 13
#define POT_PIN 2

Motion motion;
Rotation rotator = [] {
    a4988_config horizontalConfig = {2, 3, 4};
    a4988_config verticalConfig = {5, 6, 7};

    Rotation rotator(horizontalConfig, verticalConfig);
    return rotator;
}();


void handleMessage(String package) {
    command_t command = read_packet(package);

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
        default:
            Serial.print("unknown command: ");
            Serial.println(command.type);
    }
}

void setup() {
    // Init logging
    Serial.begin(9600);

    // Init pi communication
    //Wire.begin(0x8);
    //Wire.onReceive(handleMessage);

    Serial.println("Going to init motion");
    motion.begin();
    Serial.println("Going to init rotator");
    rotator.begin();
    Serial.println("Finished setup");
}

rotator_state prev_state;

void loop() {

    //Check for incoming serial messages
    if (Serial.available() > 0) {
        // read the incoming byte:
        String incomingMessage = Serial.readString();

        Serial.print("Received: ");
        Serial.println(incomingMessage);

        handleMessage(incomingMessage);
    }

    // motor control loop - send pulse and return how long to wait until next pulse
    auto state = rotator.nextAction();

    // If we finished, disable the motors.
    if (prev_state.isRunning() && !state.isRunning()) {
        rotator.handleState(state);
    }

    // (optional) execute other code if we have enough time
    if (state.timeLeft() > 100 || !state.isRunning()) {
        Serial.print("Roll: ");
        Serial.println(motion.getRoll());
        Serial.print("Pitch: ");
        Serial.println(motion.getPitch());

        //Read potpin val
        int potval = analogRead(POT_PIN);
    }

    // Save previous state for diffing
    prev_state = state;
}
