#pragma once 

#include "vex.h"

using namespace vex;

enum motor_spin_type {VOLT, PERCENTAGE, DPS, RPM};

class Drive
{
    private:
    motor_group front_left_drive, front_right_drive, back_left_drive, back_right_drive;

    float drive_min_volt;
    float drive_max_volt;

    public:

    Drive(motor_group front_left_drive, motor_group front_right_drive, motor_group back_left_drive, motor_group back_right_drive, float drive_min_volt,float drive_max_volt);

    void set_drive_max_volt(float max_voltage);
    void set_drive_min_volt(float min_voltage);

    void drive_motors(float front_left_volts, float front_right_volts, float back_left_volts, float back_right_volts);
    void drive_motors(float front_left_volts, float front_right_volts, float back_left_volts, float back_right_volts, motor_spin_type spintype);

    void brake();
    void brake(brakeType);
    void brake(bool front_left, bool front_right, bool back_left, bool back_right);
    void brake(bool front_left, bool front_right, bool back_left, bool back_right);


};


