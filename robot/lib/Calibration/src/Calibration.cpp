//
// Created by Mike on 21-6-2021.
//
#include "Calibration.h"
#include "../../Motion/src/Motion.h"



void Calibration::calibrate() {
    this->verticalStart();
    this->horizontalStart();

    //Reset the accelerometer, this ensures our zero values are always the same
    this->motion.calibrate();

    //Find the max values and save these into our position variable.
    this->verticalMax();
    this->horizontalMax();
}

//Center our dartbot so the arrow shoots straight.
void Calibration::center() {
    this->verticalStart();

    MovingAverage movingAverage = MovingAverage(this->windowSize);

    while (movingAverage.average != round((pos.pitch / 2)) ){
        if(this->motion.getPitch > round((pos.pitch / 2)) ){
            //Move left
            this->rotor.left(360);
        }
        //Move right
        this->rotor.right(360);

        movingAverage.addValue(this->motion.getPitch);
    }
}

//Resets the dartbot to our 0 values.
void Calibration::reset() {
    this->verticalStart();
    this->horizontalStart();
}

void Calibration::verticalStart() {
    MovingAverage movingAverage = MovingAverage(this->windowSize);

    while(movingAverage.average != this->motion.getRoll()){
        movingAverage.addValue(this->motion.getRoll());
        this->rotor.up(360);
    }
}

void Calibration::horizontalStart(){
    MovingAverage movingAverage = MovingAverage(this->windowSize);

    while(movingAverage.average != this->motion.getPitch()){
        movingAverage.addValue(this->motion.getPitch());
        this->rotor.left(360);
    }
}

void Calibration::verticalMax() {
    MovingAverage movingAverage = MovingAverage(this->windowSize);

    while(movingAverage.average != this->motion.getRoll()){
        movingAverage.addValue(this->motion.getRoll());
        this->rotor.down(360);
    }

    this->pos.roll = movingAverage.average;
}

void Calibration::horizontalMax() {
    MovingAverage movingAverage = MovingAverage(this->windowSize);

    while(movingAverage.average != this->motion.getPitch()){
        movingAverage.addValue(this->motion.getPitch());
        this->rotor.right(360);
    }

    this->pos.pitch = movingAverage.average;
}