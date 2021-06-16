#include <Arduino.h>
#include "Communication.h"

command_t read_packet() {
    String package;
    while (Wire.available()) {
        package += char(Wire.read());
    }

    command_t command{};
    if (package.charAt(0) != 'c') {
        Serial.print("invalid command received, did not start with c... package:\n  ");
        Serial.println(package);
        return command;
    }

    char *parameters;
    long degrees = strtol(package.substring(1).c_str(), &parameters, 10);

    Serial.println(degrees);
    Serial.println(parameters);

    command.degrees = degrees;
    command.type = parameters[0];
    command.direction = parameters[1];

    return command;
}
