#include <Arduino.h>
#include <TimerOne.h>
#include <Motion.h>
#include <Rotation.h>
#include <Communication.h>

#define SHOOT_PIN 13
#define POT_PIN A2
#define MOTOR_RPM 150
#define rpmToMicroSeconds(rpm) (1000000 / ((rpm) / 60 * (200 * 16)))
#define MEASURE_BOUNDS 0.1

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
double targetYAxis = 3;
double targetXAxis = 512;
int yMovingDirection = 0;
int xMovingDirection = 0;
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
            rotator.move(command.direction, (long) command.degrees);
            break;
        case 'p':
            Serial.print("Setting ");
            Serial.print(command.direction);
            Serial.print(" target from ");
            Serial.print(command.direction == 'x' ? targetXAxis : targetYAxis);
            Serial.print(" to ");
            Serial.println(command.degrees);
            if (command.direction == 'x') {
                targetXAxis = command.degrees;
                xMovingDirection = 0;
            }
            if (command.direction == 'y') {
                targetYAxis = command.degrees;
                yMovingDirection = 0;
            }
            currentState = CALIBRATING;
            break;
        case 'z':
            Serial.println("--- STATS ---");
            Serial.print("Roll:          ");
            Serial.println(motion.getRoll());
            Serial.print("Pot meter:     ");
            Serial.println(analogRead(POT_PIN));
            Serial.print("Electro state: ");
            Serial.println(digitalRead(SHOOT_PIN));

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
    if (yMovingDirection != 2) {
        const float currentYAxis = round(motion.getRoll());
        const auto upperYBound = (double) targetYAxis + MEASURE_BOUNDS;
        const auto lowerYBound = (double) targetYAxis - MEASURE_BOUNDS;

        if (currentYAxis < lowerYBound && yMovingDirection != 1) {
            rotator.down(5 * 28800l);
            yMovingDirection = 1;
        } else if (currentYAxis > upperYBound && yMovingDirection != -1) {
            rotator.up(5 * 28800l);
            yMovingDirection = -1;
        } else if (currentYAxis > lowerYBound && currentYAxis < upperYBound && yMovingDirection != 0) {
            rotator.up(0);
            yMovingDirection = 2;
            Serial.println("Calibrated Y!");
        }
    }

    if (xMovingDirection != 2) {
        const int currentXAxis = analogRead(POT_PIN);
        const auto upperXBound = (double) targetXAxis + MEASURE_BOUNDS;
        const auto lowerXBound = (double) targetXAxis - MEASURE_BOUNDS;
        if (currentXAxis < lowerXBound && xMovingDirection != 1) {
            rotator.right(5 * 28800l);
            xMovingDirection = 1;
        } else if (currentXAxis > upperXBound && xMovingDirection != -1) {
            rotator.left(5 * 28800l);
            xMovingDirection = -1;
        } else if (currentXAxis > lowerXBound && currentXAxis < upperXBound && xMovingDirection != 0) {
            rotator.left(0);
            xMovingDirection = 2;
            Serial.println("Calibrated X!");
        }
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
