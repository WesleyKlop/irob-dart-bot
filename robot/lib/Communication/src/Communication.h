#ifndef ROBOT_COMMUNICATION_H
#define ROBOT_COMMUNICATION_H

#include <Wire.h>

struct command_t {
    char type;
    char direction;
    double degrees;
};

command_t parse_packet(const String& package);

#endif //ROBOT_COMMUNICATION_H
