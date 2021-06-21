//
// Created by Mike on 21-6-2021.
//

#ifndef IROB_DART_BOT_CALIBRATION_H
#define IROB_DART_BOT_CALIBRATION_H

class Calibration{
private:
    Motion acceleroMeter;
    int windowsSize = 5;

    float horizontalROM;

public:
    void CalibrateVertically();
    void calibrateHorizontally(bool dir);
};

#endif //IROB_DART_BOT_CALIBRATION_H
