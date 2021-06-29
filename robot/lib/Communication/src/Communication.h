#ifndef ROBOT_COMMUNICATION_H
#define ROBOT_COMMUNICATION_H

#include <Wire.h>

struct command_t {
    char type;
    char direction;
    long degrees;
};

command_t read_packet(String package);

#endif //ROBOT_COMMUNICATION_H
