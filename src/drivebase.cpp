#include "vex.h"
class DriveBase {
    private:
        motor_group mGroupFR;
        motor_group mGroupFL;
        motor_group mGroupBL;
        motor_group mGroupBR;
        double WHEEL_DIAMETER = 2.75;
    public:
        DriveBase(motor_group mGroupFR, motor_group mGroupFL, motor_group mGroupBR, motor_group mGroupBL, motor driveMotor){
            this->mGroupFR = mGroupFR;
            this->mGroupFL = mGroupFL;
            this->mGroupBR = mGroupBR;
            this->mGroupBL = mGroupBL;
        }

        void driveDistance(motor_group mGroup, double distance, double kP=0, double kI=0, double kD=0) {
            double distanceInDegrees = (distance / (M_PI * WHEEL_DIAMETER)) * 360;
            double error = distanceInDegrees - mGroup.position(deg);
            PIDController pid_controller(kP, kI, kD);
            while (!PIDController.isSettled(error)) {
                error = distanceInDegrees - mGroup.position(deg);
                mGroup.spin(pid_controller.getPID(error));
            }

        }

        void rotateAngle(double angle, double kP=0, double kI=0, double kD=0) {
            double error = angle - mGroup.position(deg);
            PIDController pid_controller(kP, kI, kD);
            while (!PIDController.isSettled(error)) {
                if (error < 0) {
                    mGroupFR.spin(pid_controller.getPID(error));
                    mGroupBL.spin(-(pid_controller.getPID(error)));
                }
                else {
                    mGroupFL.spin(pid_controller.getPID(error));
                    mGroupBR.spin(-(pid_controller.getPID(error)));
                }
            }
        }
}
