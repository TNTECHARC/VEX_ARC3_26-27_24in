#include "Drive_Controls.H"

Drive::Drive(motor_group front_left_drive, motor_group front_right_drive, motor_group back_left_drive, motor_group back_right_drive, float min_voltage, float max_voltage)
{
    this->drive_min_volt = 3.0;
    this->drive_max_volt = max_voltage;
    this->drive_min_volt = min_voltage;

}

void Drive::set_drive_max_volt(float max_voltage)
{
    drive_max_volt = max_voltage;
}
void Drive::set_drive_min_volt(float min_voltage)
{
    drive_min_volt = min_voltage;
}

void Drive::drive_motors(float front_left, float front_right, float back_left, float back_right)
{
    drive_motors(front_left, front_right, back_left, back_right, VOLTS);
}

void Drive::drive_motors(float front_left, float front_right, float back_left, float back_right, motor_spin_type spinType)
{
    if(spinType == VOLT)
    {
        front_left_drive.spin(forward, front_left, volt);
        front_right_drive.spin(forward, front_right, volt);
        back_right_drive.spin(forward, back_right, volt);
        back_left_drive.spin(forward, back_left, volt);
    }
    else if(spinType == PERCENTAGE)
    {
        front_left_drive.spin(forward, front_left, pct);
        front_right_drive.spin(forward, front_right, pct);
        back_right_drive.spin(forward, back_right, pct);
        back_left_drive.spin(forward, back_left, pct);
    }
    else if(spinType == DPS)
    {
        front_left_drive.spin(forward, front_left, dps);
        front_right_drive.spin(forward, front_right, dps);
        back_right_drive.spin(forward, back_right, dps);
        back_left_drive.spin(forward, back_left, dps);
    }
    else if(spinType == RPM)
    {
        front_left_drive.spin(forward, front_left, rpm);
        front_right_drive.spin(forward, front_right, rpm);
        back_right_drive.spin(forward, back_right, rpm);
        back_left_drive.spin(forward, back_left, rpm);
    }
}

void Drive::brake()
{
    brake(true, true, true, true);
}

void Drive::brake(brakeType type)
{
    brake(true, true, true, true, type);
}

void Drive::brake(bool front_left, bool back_left, bool front_right, bool back_right)
{
    brake(front_left, back_left, front_right, back_right, hold);
}

void Drive::brake(bool front_left, bool back_left, bool front_right, bool back_right, brakeType type)
{
    if(front_left)
        front_left_drive.stop(type);
    if(back_left)
        back_left_drive.stop(type);
    if(front_right)
        front_right_drive.stop(type);
    if(back_right)
        back_right_drive.stop(type);

}

