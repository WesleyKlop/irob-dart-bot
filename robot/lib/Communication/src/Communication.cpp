#include <Arduino.h>
#include "Communication.h"

command_t read_packet(String package) {
    //String package;
    //while (Wire.available()) {
    //  package += char(Wire.read());
    //}

    command_t command{};
    if (package.charAt(0) != 'c') {
        Serial.print("invalid command received, did not start with c... package:\n  ");
        Serial.println(package);
        return command;
    }

    char *parameters;
    long degrees = strtol(package.substring(2).c_str(), &parameters, 10);

    command.degrees = degrees;
    command.type = package.charAt(1);
    command.direction = parameters[0];

    return command;
}
