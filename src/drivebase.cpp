#include "vex.h"
/// @brief This class is used for drivebase movement
class DriveBase {
    private:
        motor_group mGroupFR;
        motor_group mGroupFL;
        motor_group mGroupBL;
        motor_group mGroupBR;
        double WHEEL_DIAMETER = 2.75;
    public:
        /// @brief Constructor for the DriveBase class
        /// @param mGroupFR Represents the front-right motor group
        /// @param mGroupFL Represents the front-left motor group
        /// @param mGroupBR Represents the back-right motor group
        /// @param mGroupBL Represents the back-left motor group
        DriveBase(motor_group mGroupFR, motor_group mGroupFL, motor_group mGroupBR, motor_group mGroupBL){
            this->mGroupFR = mGroupFR;
            this->mGroupFL = mGroupFL;
            this->mGroupBR = mGroupBR;
            this->mGroupBL = mGroupBL;
        }
        
        /// @brief This function drives a distance forward
        /// @param mGroup Represents the motorgroup that needs to spin
        /// @param distance Represents the distance needed to spin
        /// @param kP Represents tuning value for P
        /// @param kI Represents tuning value for I
        /// @param kD Represents tuning value for D
        void driveDistance(motor_group mGroup, double distance, double kP=0, double kI=0, double kD=0) {
            double distanceInDegrees = (distance / (M_PI * WHEEL_DIAMETER)) * 360;
            double error = distanceInDegrees - mGroup.position(deg);
            PIDController pid_controller(kP, kI, kD);
            while (!PIDController.isSettled(error)) {
                error = distanceInDegrees - mGroup.position(deg);
                mGroup.spin(pid_controller.getPID(error));
            }

        }

        /// @brief Rotates the drivebase a certain specified angle
        /// @param angle Angle to be rotated
        /// @param kP Represents tuning value for P
        /// @param kI Represents tuning value for I
        /// @param kD Represents tuning value for D
        void rotateAngle(motor_group mGroup, double angle, double kP=0, double kI=0, double kD=0) {
            double error = angle - mGroup.position(deg);
            PIDController pid_controller(kP, kI, kD);
            while (!PIDController.isSettled(error)) {
                if (error < 0) {
                    mGroupFR.spin(forward, pid_controller.getPID(error), volt);
                    mGroupBL.spin(forward, -(pid_controller.getPID(error)), volt);
                }
                else {
                    mGroupFL.spin(forward, pid_controller.getPID(error), volt);
                    mGroupBR.spin(forward, -(pid_controller.getPID(error)), volt);
                }
            }
        }

        void driveJoystick(Controller controller, double kP=0, double kI=0, double kD=0)
        {   
            double voltsH;
            double voltsV;
            //right (FL forward BR forward, FR backward, BL backward) left opposite
            //this is the volts for the horizontal position
            voltsH = (controller.Axis3.position() / 100) * 12;
            if (voltsH > 0) {
                mGroupFR.spin(backward, voltsH, volt);
                mGroupFL.spin(forward, voltsH, volt);
                mGroupBR.spin(forward, voltsH, volt);
                mGroupBL.spin(backward, voltsH, volt);
            }
            else {
                mGroupFR.spin(forward, voltsH, volt);
                mGroupFL.spin(backward, voltsH, volt);
                mGroupBR.spin(backward, voltsH, volt);
                mGroupBL.spin(forward, voltsH, volt);
            }
            
            //forward (FR FL forward, BR BL backward), backwards opposite
            //This is the volts for the vertical direction
            voltsV = (controller.Axis4.position() / 100) * 12;
            if (voltsV > 0) {
                mGroupFR.spin(forward, voltsV, volt);
                mGroupFL.spin(forward, voltsV, volt);
                mGroupBR.spin(backward, voltsV, volt);
                mGroupBL.spin(backward, voltsV, volt);
            }
            else {
                mGroupFR.spin(backward, voltsV, volt);
                mGroupFL.spin(backward, voltsV, volt);
                mGroupBR.spin(forward, voltsV, volt);
                mGroupBL.spin(forward, voltsV, volt);
            }
        }
}
