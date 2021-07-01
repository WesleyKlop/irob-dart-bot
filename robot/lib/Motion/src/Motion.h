#ifndef BALANCINGROBOT_MOTION_H
#define BALANCINGROBOT_MOTION_H

#include <MPU9250_WE.h>

class Motion {
private:
    MPU9250_WE mpu9250;

    void calibrate();

public:
    explicit Motion(int address);

    Motion();

    void begin() {
        begin(false);
    }

    void begin(bool calibrate);

    float getPitch();

    float getTemperature();

    float getRoll();
};

#endif //BALANCINGROBOT_MOTION_H
