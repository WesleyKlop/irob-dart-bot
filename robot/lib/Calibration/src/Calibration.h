//
// Created by Mike on 21-6-2021.
//

#ifndef IROB_DART_BOT_CALIBRATION_H
#define IROB_DART_BOT_CALIBRATION_H

struct Position {
    float pitch;
    float roll;
};

struct MovingAverage{
    int windowsize;
    float sum, average, index = 0;
    float readings[windowsSize];
    MovingAverage(int size){
        windowsize = size;
    }

    void addValue(float val){
        sum = sum - this->readings[index];
        readings[index] = val;
        sum = sum + motion.getPitch();
        index = (index + 1) % windowsSize;
        average = this->sum / windowsSize;
    }
};

class Calibration{
private:
    //Vertical starting position, all the way at the top.
    void verticalStart();
    //Vertical starting position, all the way left.
    void horizontalStart();
    //Max vertical position, should be at the bottom where the angle is the steepest.
    void verticalMax();
    //Max horizontal position, all the way to the right.
    void horizontalMax();
    //max position.
    Position pos;

    int windowSize = 5;
    Motion motion;
    Rotation rotor;


public:
    void calibrate();
    void reset();
    void center();

};

#endif //IROB_DART_BOT_CALIBRATION_H
