#include "vex.h"
class DriveBase {
    private:
        motor_group mGroup;
        motor driveMotor;
        double WHEEL_DIAMETER = 2.75;
    public:
        DriveBase(motor_group mGroupFR, motor_group mGroupFL, motor_group mGroupBR, motor_group mGroupBL, motor driveMotor){
            this->mGroupFR = mGroupFR;
            this->mGroupFL = mGroupFL;
            this->mGroupBR = mGroupBR;
            this->mGroupBL = mGroupBL;
            this->driveMotor = driveMotor;
        }

        void driveDistance(double distance, double kP=0, double kI=0, double kD=0) {
            double distanceInDegrees = (distance / (M_PI * WHEEL_DIAMETER)) * 360;
            double error = distanceInDegrees - driveMotor.position(deg);
            PIDController pid_controller = (kP, kI, kD);
            while (!PIDController.isSettled(error)) {
                error = distanceInDegrees - driveMotor.position(deg);
                driveMotor.spin(pid_controller.getPID(error));
            }

        }

        void rotateAngle(double angle, double kP=0, double kI=0, double kD=0) {

        }
}
