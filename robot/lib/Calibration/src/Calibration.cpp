//
// Created by Mike on 21-6-2021.
//
#include "Calibration.h"
#include "../../Motion/src/Motion.h"



Calibration::CalibrateVertically(){
    Motion motion = Motion();
    float readings[windowsSize];
    float sum, average, index = 0;

    while(this->average != motion.getPitch()){
        sum = sum - this->readings[index];

        readings[index] = motion.getPitch();
        sum = sum + motion.getPitch();
        index = (index + 1) % windowsSize;
        average = this->sum / windowsSize;

        //TODO:: Move up until no more movement is detected.

    }
}

Calibration::calibrateHorizontally(bool dir){
    Motion motion = Motion();
    float readings[windowsSize];
    float sum, average, index = 0;

    while(this->average != motion.getPitch()){
        sum = sum - this->readings[index];

        readings[index] = motion.getPitch();
        sum = sum + motion.getPitch();
        index = (index + 1) % windowsSize;
        average = this->sum / windowsSize;

        //TODO:: Move left, reset, moveright, save rom.
        if(dir){
            //TODO:: Move left

        }
    }
    if(dir){
        //RESET values
        motion.calibrate();
        this->calibrateHorizontally(false);
    }

    //Half of the average value should correspond to half of the rail.
    this->horizontalROM = average;

}