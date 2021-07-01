#include <Arduino.h>
#include <TimerOne.h>
#include <Motion.h>
#include <Rotation.h>
#include <Communication.h>

#define SHOOT_PIN 13
#define POT_PIN A2
#define MOTOR_RPM 150
#define rpmToMicroSeconds(rpm) (1000000 / ((rpm) / 60 * (200 * 16)))

enum app_state {
    CALIBRATING,
    ARMED,
};

Motion motion;
Rotation rotator = [] {
    a4988_config horizontalConfig = {2, 3, 4};
    a4988_config verticalConfig = {5, 6, 7};

    Rotation rotator(horizontalConfig, verticalConfig);
    return rotator;
}();

rotator_state prevRotatorState;
long targetYAxis = 3;
long targetXAxis = 20;
int verMovingDirection = 0;
int horMovingDirection = 0;
app_state currentState = CALIBRATING;

void serialEvent() {
    const String package = Serial.readStringUntil('\n');

    Serial.print("Arduino executing: ");
    Serial.println(package);
    command_t command = parse_packet(package);

    if (!command.type) {
        return;
    }

    switch (command.type) {
        case 's':
            digitalWrite(SHOOT_PIN, command.degrees != 0);
            currentState = command.degrees != 0 ? CALIBRATING : ARMED;
            break;
        case 'm':
            currentState = CALIBRATING;
            rotator.move(command.direction, command.degrees);
            break;
        case 'p':
            currentState = CALIBRATING;
            if (command.direction == 'x') {
                targetXAxis = command.degrees;
            }
            if (command.direction == 'y') {
                targetYAxis = command.degrees;
            }
            break;
    }
}

void updateMotorState() {
    // motor control loop - send pulse and return how long to wait until next pulse
    auto state = rotator.nextAction();
    if (currentState != CALIBRATING && state.isRunning()) {
        rotator.stop();
    }

    // If we finished, disable the motors.
    if (prevRotatorState.isRunning() && !state.isRunning()) {
        rotator.handleState(state);
    }

    // Save previous state for diffing
    prevRotatorState = state;
}

void setup() {
    Wire.begin();
    Serial.begin(115200);

    Serial.println("Going to init motion");
    motion.begin();
    Serial.println("Going to init rotator");
    rotator.begin(MOTOR_RPM);
    Serial.println("Going to init timer");
    Timer1.initialize(rpmToMicroSeconds(MOTOR_RPM));
    Timer1.attachInterrupt(updateMotorState);
    Serial.println("Finished setup");
}

void loopCalibrating() {
    const float currentYAxis = round(motion.getRoll());
    const auto upperYBound = (double) targetYAxis + 1;
    const auto lowerYBound = (double) targetYAxis - 1;
    if (currentYAxis < lowerYBound && verMovingDirection != 1) {
        rotator.down(2 * 28800);
        verMovingDirection = 1;
    } else if (currentYAxis > upperYBound && verMovingDirection != -1) {
        rotator.up(2 * 28800);
        verMovingDirection = -1;
    } else if (currentYAxis > lowerYBound && currentYAxis < upperYBound && verMovingDirection != 0) {
        rotator.up(0);
        verMovingDirection = 0;
        Serial.println("Calibrated Y!");
    }

    const int currentXAxis = analogRead(POT_PIN);
    const auto upperXBound = (double) targetXAxis + 1;
    const auto lowerXBound = (double) targetXAxis - 1;
    if (currentXAxis < lowerXBound && horMovingDirection != 1) {
        rotator.right(2 * 28800);
        horMovingDirection = 1;
    } else if (currentXAxis > upperXBound && horMovingDirection != -1) {
        rotator.left(2 * 28800);
        horMovingDirection = -1;
    } else if (currentXAxis > lowerXBound && currentXAxis < upperXBound && horMovingDirection != 0) {
        rotator.left(0);
        horMovingDirection = 0;
        Serial.println("Calibrated X!");
    }
}

void loopArmed() {
    // Nothing really
}

void loop() {
    switch (currentState) {
        case CALIBRATING:
            loopCalibrating();
        case ARMED:
            loopArmed();
    }
    delay(100);
}
